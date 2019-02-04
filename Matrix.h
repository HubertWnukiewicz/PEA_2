#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <random>
#include "Timer.h"
class Matrix 
{
	int** data;
	int vertex;
	int* visited;
	double found = 0;
	std::vector<int> minimumRoute;
	std::vector<std::vector<int>> moves;
	int minSolution = INT_MAX;

public:
	void ReadFromFile(std::string filename);
	void printMatrix();
	std::vector<int> getTransformation(std::vector<int> vector);
	void simulatedAnnealing(std::vector<int> cycle, std::vector<int>& minimumRoute, double tempStart, double tempMin, double stoptime, float a);
	int distance(std::vector<int> vector);
	std::vector<int> InitSA(double time, Timer& timer,float a);
	double getFound() { return found; }
	int getMinSolution() { return minSolution; }
	double calcTemperature(int size);
	std::vector<int> randomRoute();
	std::vector<int> initTS(double time, Timer& timer, int type);
	void tabuSearch(std::vector<int> cycle, std::vector<int>& minimumRoute, float time,int type);
	void resetAtributes();
	void printRoute(std::vector<int> route);
	std::vector<int> setNeighboorType(std::vector<int> route, int type);

	std::vector<std::vector<int>> getNeighbourhood(std::vector<int> currentPermutation );
	int pathCostTabu(std::vector<int> permutation);



	std::vector<int>initGeneticAlgorithm(int populationSize, int generations, double crossingProbability, double mutationProbability, double stopTime, Timer& counter); 
	std::vector<int> geneticAlgorithm(int populationSize, int generations, double crossingProbability, double mutationProbability, double stopTime); 
	std::vector<int> crossingHalfes(std::vector<int> parent1, std::vector<int> parent2);
	std::vector<int> mutationRandom(std::vector<int> parent, int levelsOfMutation);

};