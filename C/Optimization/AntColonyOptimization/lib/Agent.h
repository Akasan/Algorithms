#pragma once
#include <vector>


class Agent{
public:
	std::vector<int> route;
	float length;

	Agent();
	~Agent();
	void register_route(int);
	void calculate_length();
	void reset_route();
	void reset_length();
	bool is_city_include(int);
	int get_last_city();
	void discribe_route();

private:
};
