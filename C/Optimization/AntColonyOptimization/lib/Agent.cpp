#include "Agent.h"
#include <vector>
#include <iostream>


Agent::Agent(){
	route = std::vector<int>();
	reset_length();
}

Agent::~Agent(){
	std::vector<int>().swap(route);	
}

void Agent::register_route(int city){         
	route.push_back(city);	
}

void Agent::reset_route(){
	std::vector<int>().swap(route);	
	route = std::vector<int>();
}

void Agent::reset_length(){
	length = 0.0;
}

bool Agent::is_city_include(int city){
	if(route.size() == 0){
		return false;
	}

	for(int i=0; i<route.size(); i++){
		if(route[i] == city){
			return true;
		}
	}
	return false;
}

int Agent::get_last_city(){
	if(route.size() > 0){
		return route[route.size()-1];
	}
}

void Agent::discribe_route(){
	for(int i=0; i<route.size(); i++){
		std::cout << route[i] << " -> ";
	}
}