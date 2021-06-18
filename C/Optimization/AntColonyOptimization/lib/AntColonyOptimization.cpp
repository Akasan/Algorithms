#include "AntColonyOptimization.h"
#include "Agent.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>


ACOBase::ACOBase(int city_num, int agent_num, std::string tsp_filename){
	this->city_num = city_num;
	this->agent_num = agent_num;
	all_best = -1;
	std::vector< std::vector<int> > city_info = read_csv(tsp_filename);
	agents = std::vector<Agent>(agent_num);
	params = ACOParams();	
	initialize();
	initialize_distance_array(city_info);
	initialize_pheromone_array();
}

ACOBase::ACOBase(int city_num, int agent_num, std::string tsp_filename, ACOParams params){
	this->city_num = city_num;
	this->agent_num = agent_num;
	this->params = params;
	agents = std::vector<Agent>(agent_num);
	all_best = -1;
	std::vector< std::vector<int> > city_info = read_csv(tsp_filename);
	initialize();
	initialize_distance_array(city_info);
	initialize_pheromone_array();
}

std::vector< std::vector<int> > ACOBase::read_csv(std::string tsp_filename){
	std::vector< std::vector<int> > city_info(city_num, std::vector<int>(2));
	int cnt = 0, col = 0;
	std::string str_buf;
	std::string str_conma_buf;
	std::ifstream ifs_csv_file(tsp_filename);

  	while (getline(ifs_csv_file, str_buf)) {
        if(cnt == city_num) break;
  		std::istringstream i_stream(str_buf);
		col = 0;

  		while (getline(i_stream, str_conma_buf, ',')) {
            city_info[cnt][col] = std::atoi(str_conma_buf.c_str());
			col += 1;
  		}
        cnt += 1;
  	}
	return city_info;
}

void ACOBase::Search(int iteration){
	float pre_best = -1;
	for(int iter=0; iter<iteration; iter++){
		iteration_best = -1;
		for(int a=0; a<agent_num; a++){
			agents[a].reset_length();
			agents[a].reset_route();
			generate_route(a);
			// agents[a].discribe_route();
			calculate_length(a);
		}

		if(pre_best == -1 || iteration_best < pre_best){
			pre_best = iteration_best;
			std::cout << pre_best << std::endl;
		}
		update_pheromone();
	}
}

// void ACOBase::Search(int iteration, int process_num){
// 	float pre_best = -1;
// 	int step = agent_num / process_num;
// 	for(int iter=0; iter<iteration; iter++){
// 		std::vector<std::thread> threads = std::vector<std::thread>(step);
// 		iteration_best = -1;
// 		for(int s=0; s<step; s++){
// 			std::thread th(generate_route, s*step, (s*1)*step);
// 			threads.push_back(th);
// 		}

// 		for(int s=0; s<step; s++){
// 			threads[s].join();
// 		}
// 	}
// }

void ACOBase::initialize(){
	srand((unsigned)time(NULL));
	for(int i=0; i<agent_num; i++){
		agents.push_back(Agent());
	}
}

void ACOBase::initialize_distance_array(std::vector< std::vector<int> > city_info){
	int i, j;
	distance_array = std::vector< std::vector<float> >(city_num, std::vector<float>(city_num));
	for(i=0; i<city_num; i++){
		for(j=i+1; j<city_num; j++){
			distance_array[i][j] = pow(pow(city_info[i][0] - city_info[j][0], 2.0) + pow(city_info[i][1] - city_info[j][1], 2.0), 0.5);
			distance_array[j][i] = distance_array[i][j];
		}
	}
}

void ACOBase::initialize_pheromone_array(){
	int i, j;
	pheromone_array = std::vector< std::vector<float> >(city_num, std::vector<float>(city_num));
	for(i=0; i<city_num; i++){
		for(j=i+1; j<city_num; j++){
			pheromone_array[i][j] = params.initial_pheromone;
			pheromone_array[j][i] = params.initial_pheromone;
		}
	}
}


void ACOBase::generate_route(int agent_index){
	Agent agent = agents[agent_index];
	int pre_city = rand() % city_num;
	int i;
	float prob_sum, thresh;
	std::vector<float> prob(city_num, 0);
	float prob_accumulate;
	agent.register_route(pre_city);

	for(int city_idx=1; city_idx<city_num; city_idx++){
		prob = std::vector<float>(city_num, 0);
		prob_sum = 0.0;

		for(i=0; i<city_num; i++){
			if(agent.is_city_include(i) || i == pre_city){
				prob[i] = 0.0;
				continue;
			}
			prob[i] = pow(pheromone_array[i][pre_city], params.alpha) * pow(1.0 / distance_array[i][pre_city], params.beta);
			prob_sum += prob[i];
		}

		prob_accumulate = 0.0;
		thresh = (double)rand()/RAND_MAX;
		bool is_registers = false;
		for(i=0; i<city_num; i++){
			prob_accumulate += prob[i] / prob_sum;
			if(prob_accumulate >= thresh && !agent.is_city_include(i)){
				agent.register_route(i);
				is_registers = true;
				pre_city = i;
				break;
			}
		}
	}
	agents[agent_index] = agent;
}

void ACOBase::generate_route(int agent_index_start, int agent_index_end){
	for(int agent_index=agent_index_start; agent_index<agent_index_end; agent_index++){
		agents[agent_index].reset_length();
		agents[agent_index].reset_route();
		generate_route(agent_index);
		calculate_length(agent_index);
	}
}

void ACOBase::calculate_length(int agent_index){
	float length = 0.0;
	Agent agent = agents[agent_index];
	for(int i=0; i<city_num-1; i++){
		length += distance_array[agent.route[i]][agent.route[i+1]];
	}
	length += distance_array[agent.route[0]][agent.get_last_city()];

	if(iteration_best == -1 || length < iteration_best){
		iteration_best = length;
	}
	agents[agent_index].length = length;
}

void ACOBase::update_pheromone(){
	int i, j;
	float increase;
	reduce_pheromone();
	for(int agent_idx=0; agent_idx<agent_num; agent_idx++){
		increase = 1.0 / agents[agent_idx].length;
		for(i=0; i<city_num-1; i++){
			pheromone_array[agents[agent_idx].route[i]][agents[agent_idx].route[i+1]] += increase;
			pheromone_array[agents[agent_idx].route[i+1]][agents[agent_idx].route[i]] += increase;
		}
		pheromone_array[agents[agent_idx].route[city_num-1]][agents[agent_idx].route[0]] += increase;
		pheromone_array[agents[agent_idx].route[0]][agents[agent_idx].route[city_num-1]] += increase;
	}
}

void ACOBase::reduce_pheromone(){
	int i, j;
	for(i=0; i<city_num; i++){
		for(j=i+1; j<city_num; j++){
			pheromone_array[i][j] *= params.rho;
			pheromone_array[j][i] = pheromone_array[i][j];
		}
	}
}

MaxMinAntSystem::MaxMinAntSystem(int city_num, int agent_num, std::string tsp_filename) : ACOBase(city_num, agent_num, tsp_filename){
}

MaxMinAntSystem::MaxMinAntSystem(int city_num, int agent_num, std::string tsp_filename, ACOParams params) : ACOBase(city_num, agent_num, tsp_filename, params){
}

void MaxMinAntSystem::Search(int iteration){
	ACOBase::Search(iteration);
}


void MaxMinAntSystem::update_pheromone(){
	float tau_max = 1.0 / (params.rho * all_best);
	float tau_min = (tau_max * (1 - pow(0.05, 1.0 / city_num))) / ((city_num/2-1) * pow(0.05, 1.0 / city_num));
	int i, j;
	ACOBase::update_pheromone();
	for(i=0; i<city_num; i++){
		for(j=i+1; j<city_num; j++){
			if(pheromone_array[i][j] > tau_max){
				pheromone_array[i][j] = tau_max;
				pheromone_array[j][i] = tau_max;
			}
			else if(pheromone_array[i][j] < tau_min){
				pheromone_array[i][j] = tau_min;
				pheromone_array[j][i] = tau_min;
			}
		}
	}
}