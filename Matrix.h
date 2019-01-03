#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "Timer.h"
class Matrix 
{
	int** data;
	int vertex;
	int* visited;
	std::vector<int> minimumRoute;
	//int* minimumRoute;
	std::map<int, int> tabu_list;
	int minSolution = INT_MAX;

public:
	void ReadFromFile(std::string filename);
	void printMatrix();
	std::vector<int> getTransformation(std::vector<int> vector);
	void simulatedAnnealing(std::vector<int> cycle, std::vector<int>& minimumRoute, double tempStart, double tempMin, double stoptime, float a);
	int distance(std::vector<int> vector);
	std::vector<int> InitSA(double time, Timer& timer,float a);
	int getValue(int* route);
	int getMinSolution() { return minSolution; }
	double calcTemperature(int size);
	std::vector<int> randomRoute();
	std::vector<int> initTS(double time, Timer& timer, int type);
	void tabuSearch(std::vector<int> cycle, std::vector<int>& minimumRoute, float time,int type);
	void resetAtributes();
	void printRoute(std::vector<int> route);
	std::vector<int> setNeighboorType(std::vector<int> route, int type);
};