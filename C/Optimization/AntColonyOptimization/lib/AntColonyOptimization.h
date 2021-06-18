#pragma once
#include <vector>
#include "Agent.h"
#include <string>

struct ACOParams{
public:
	float alpha = 1.0;
	float beta = 3.0;
	float rho = 0.9;
	float initial_pheromone = 1.0;
};

class ACOBase{
public:
	int city_num;
	int agent_num;
	float iteration_best, all_best;
	std::vector< std::vector<float> > distance_array;
	std::vector< std::vector<float> > pheromone_array;
	std::vector<Agent> agents;
	ACOParams params;

	ACOBase(int, int, std::string);
	ACOBase(int, int, std::string, ACOParams);
	void Search(int);
	void Search(int, int);

protected:
	void initialize();
	void initialize_distance_array(std::vector< std::vector<int> >);
	void initialize_pheromone_array();
	void generate_route(int);
	void generate_route(int, int);
	void calculate_length(int);
	virtual void update_pheromone();
	void reduce_pheromone();
	std::vector< std::vector<int> > read_csv(std::string);
};

class MaxMinAntSystem : public ACOBase{
public:
	MaxMinAntSystem(int, int, std::string);
	MaxMinAntSystem(int, int, std::string, ACOParams);
	void Search(int);

private:
	void update_pheromone();
};