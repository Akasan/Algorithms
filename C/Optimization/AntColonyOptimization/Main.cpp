#include <iostream>
#include "AntColonyOptimization.h"
#include "Agent.h"


int main(void){
	ACOParams params = ACOParams();
	// MaxMinAntSystem aco = MaxMinAntSystem(100, 20, "./data/kroA100.csv", params);
	ACOBase aco = ACOBase(100, 100, "./data/kroA100.csv", params);
	aco.Search(3000);
}
