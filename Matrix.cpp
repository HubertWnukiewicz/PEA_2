#include "Matrix.h"
#include <fstream>
#include "Timer.h"
using namespace std;

void Matrix::ReadFromFile(std::string filename)
{
	std::fstream file;
	file.open(filename, std::ios::in);
	if (file.good() == true)
	{
		file >> vertex;
		//minimumRoute = new int[vertex + 1];
		//visited = new bool[vertex];
		data = new int*[vertex];

		for (int i = 0; i < vertex; i++)
			data[i] = new int[vertex];

		for (int i = 0; i < vertex; i++)
		{
			for (int j = 0; j < vertex; j++)
			{
				data[i][j] = 0; //inicjalizacja macierzy
			}
		}

		int CurrentValue;

		for (int i = 0; i < vertex; i++)
		{
			for (int j = 0; j < vertex; j++)
			{
				file >> CurrentValue;
				data[i][j] = CurrentValue;
			}

		}

		file.close();
	}
	else
		std::cout << "Error while opening file!" << std::endl;
}
void Matrix::printMatrix()
{
	if (vertex > 0)
	{
		for (int i = 0; i < vertex; i++)
		{
			for (int j = 0; j < vertex; j++)
			{
				std::cout << data[i][j] << " ";
				if (j == vertex - 1)
					std::cout << std::endl;
			}
		}
	}
}
std::vector<int> Matrix::getTransformation(std::vector<int> vector)
{
	int ind1 = rand() % (vector.size()-1)+1;
	int ind2 = rand() % (vector.size()-1)+1;
	while (ind1 == ind2)
		ind2 = rand() % (vector.size()-1)+1;
	//SWAP
	//cout << "ind1= " << ind1 << " ,ind2= " << ind2 << endl; 4289
	std::swap(vector[ind1], vector[ind2]);
	return vector;
}
void Matrix::simulatedAnnealing(std::vector<int> cycle, std::vector<int>& minimumRoute, double tempStart, double tempMin, double stoptime, float a)
{
	Timer timer;
	minimumRoute = cycle;
	const int tempLength = cycle.size()*(cycle.size() - 1) / 2;
	double temperature=tempStart;
	this->minSolution = distance(cycle);
	timer.start();

	while (timer.stop() < stoptime /*&& temperature>tempMin*/)
	{
		std::cout <<"czas: "<< timer.stop() << std::endl;
		for (int i = 0; i < tempLength; i++)
		{
			vector<int> cycleNeighbour = getTransformation(cycle);
			int tmpDistance = distance(cycle);
			int tmpDistanceNeighbour = distance(cycleNeighbour);

			if (tmpDistanceNeighbour - tmpDistance <= 0 || tmpDistanceNeighbour - tmpDistance > 0 && (double)rand() / RAND_MAX < exp(-(tmpDistanceNeighbour - tmpDistance) / temperature))
			{
				cycle = cycleNeighbour;
				if (tmpDistanceNeighbour < minSolution)
				{
					found = timer.stop();
					minimumRoute = cycle;
					minSolution = tmpDistanceNeighbour;
				}
			}
		}
		temperature *= a;
	}
	
}
int Matrix::distance(std::vector<int> vector)
{
	if (vector.empty())
		return -1;
	int distance = 0;
	for (int i = 0; i < vector.size() - 1; i++)
	{
		distance += data[vector[i]][vector[i + 1]];
	}
	distance += data[vector[vector.size() - 1]][vector[0]];
	return distance;
}
std::vector<int> Matrix::InitSA(double time, Timer & timer, float a)
{
	std::vector<int> cycle(vertex, 0);
	for (int i = 0; i <vertex ; i++)
	{
		cycle[i] = i;
	}
	double temp = calcTemperature(1000);
	cout << "Temperatura: " << temp << endl;
	timer.reset();
	timer.start();
	this->simulatedAnnealing(cycle, minimumRoute, temp, 0.000001, time , a);
	timer.stop();
	return minimumRoute;
}

double Matrix::calcTemperature(int size)
{
	double temp=0.0;
	std:vector<int> route = randomRoute();
	for (int i = 0; i < size; i++)
	{
		temp += abs(distance(route) - distance(getTransformation(route)));
		route = randomRoute();
	}
	//return (temp/size);
	return temp;
}

std::vector<int> Matrix::randomRoute()
{
	std::vector<int> route(vertex, 0);
	for (int i = 0; i < vertex; i++)
		route[i] = i;
	for (int i = 1; i < vertex; i++)
		std::swap(route[i], route[rand() % (vertex-1)+1]);
	return route;
}

std::vector<int> Matrix::initTS(double time, Timer & timer, int type)
{
	std::vector<int> route(vertex, 0);
	for (int i = 0; i < vertex; i++)
	{
		route[i] = i;
	}
	timer.reset();
	timer.start();
	tabuSearch(route, this->minimumRoute,time,type);
	timer.stop();
	minimumRoute.at(0) = 0;
	return minimumRoute;
}

void Matrix::tabuSearch(std::vector<int> cycle, std::vector<int>& minimumRoute, float stoptime, int type)
{
	Timer timer;
	int tabuListSize = vertex * 3;
	int iterationThreshold = tabuListSize * 3;

	std::vector<int> s0 = getTransformation(cycle);
	std::vector<int> sBest = s0;
	std::vector<int> bestCandidate = s0;

	std::vector<int> sCandidate;
	std::vector<int> moveToCandidate;

	std::vector<std::vector<int>> sNeighbourhood;
	std::vector<std::vector<int>> tabuList;
	std::vector<int> moveToBePutOnTabuList;
	timer.start();

	while (timer.stop() < stoptime)
	{
		bool noAcceptedCandidates = true;
		std::cout << "Timer: " << timer.stop() << endl;
		sNeighbourhood = getNeighbourhood(bestCandidate);
		for (int i = 0; i < sNeighbourhood.size(); i++)
		{
			sCandidate = sNeighbourhood.at(i);
			moveToCandidate = moves.at(i);

			if (std::find(tabuList.begin(), tabuList.end(), moveToCandidate) != tabuList.end())
			{
				if (distance(sCandidate) < distance(sBest))
				{
					bestCandidate = sCandidate;
					moveToBePutOnTabuList = moveToCandidate;
					noAcceptedCandidates = false;
				}
			}
			else
			{
				if (distance(sCandidate)< distance(bestCandidate))
				{
					noAcceptedCandidates = false;
					bestCandidate = sCandidate;
					moveToBePutOnTabuList = moveToCandidate;
				}
			}
		}

		if (noAcceptedCandidates) {
			iterationThreshold--;
		}

		if (iterationThreshold <= 0)
		{
			moves.clear();
			tabuList.clear();
			sNeighbourhood.clear();
			iterationThreshold = tabuListSize * 3;
			bestCandidate=getTransformation(cycle);
			//bestCandidate = setNeighboorType(bestCandidate, type);
		}
		else
		{
			if (distance(bestCandidate) < distance(sBest))
			{
				sBest = bestCandidate;
				found = timer.stop();
			}

			tabuList.push_back(moveToBePutOnTabuList);
			if (tabuList.size() > tabuListSize) 
				tabuList.erase(tabuList.begin());

			
		}

		moves.clear();
	}
	minimumRoute = sBest;

}

void Matrix::resetAtributes()
{
	minSolution = INT_MAX;
	for (int i = 0; i < vertex; i++)
		minimumRoute[i] = 0;
	found = 0;
}

void Matrix::printRoute(std::vector<int> route)
{
	for (int i = 0; i < vertex; i++)
		std::cout << route[i] << "->";
	cout << "0" << endl;
	cout << endl;
	std::cout <<"Wielkosc: "<< route.size();
}

std::vector<int> Matrix::setNeighboorType(std::vector<int> route, int type)
{
	int ind1 = rand() % route.size();
	int ind2 = rand() % route.size();
	while (ind1 == ind2)
		ind2 = rand() % route.size();
	if (ind1 > ind2)
	{
		std::swap(ind1, ind2);
	}
	if (type == 1)//SWAP
	{
		std::swap(route[ind1], route[ind2]);
	}
	else if (type == 2)//INSERT
	{
		int value = route[ind2];
		for (int i = ind2; i > ind1; i--)
		{
			route[i] = route[i - 1];
		}
		route[ind1] = value;
	}
	else if (type == 3)//INVERT
	{
		while (ind1 < ind2)
		{
			std::swap(route[ind1++], route[ind2--]);
		}
	}
	return route;
}

std::vector<int> Matrix::getInitialSolution()
{
	int startNode = 0;
	
	std::vector<int> initialSolution;
	initialSolution.push_back(startNode);
	for (int i = 0; i < vertex - 1; i++)
	{
		int bestNeighbourIndex = -1;
		int bestNeighbourCost = INT_MAX;

		for (int i = 0; i < vertex; i++)
		{
			if (i != startNode && data[startNode][i] < bestNeighbourCost &&
				std::find(initialSolution.begin(), initialSolution.end(), i) == initialSolution.end())
			{
				bestNeighbourIndex = i;
				bestNeighbourCost = data[startNode][i];
			}
		}
		initialSolution.push_back(bestNeighbourIndex);
		startNode = bestNeighbourIndex;
	}

	//for (int i = 0; i < vertex; i++) 
		//initialSolution.at(i) += 1;

	return initialSolution;
}

std::vector<int> Matrix::getRandomPermutationTabu()
{
	std::vector<int> randomPermutation;
	for (int i = 0; i < vertex; ++i) 
		randomPermutation.push_back(i);
	std::random_shuffle(randomPermutation.begin(), randomPermutation.end());

	//for (int i = 0; i < vertex; i++) 
		//randomPermutation.at(i) += 1;
	return randomPermutation;
}

std::vector<std::vector<int>> Matrix::getNeighbourhood(std::vector<int> currentPermutation)
{
	std::vector<std::vector<int>> neighbourhood;
	for (int i = 0 ; i < vertex - 1; i++)
	{
		for (int currentSwap = i + 1; currentSwap < vertex; currentSwap++)
		{
			std::vector<int> move;
			move.push_back(i);
			move.push_back(currentSwap);

			std::vector<int> nextNeighbour = currentPermutation;
			std::swap(nextNeighbour.at(i), nextNeighbour.at(currentSwap));

			neighbourhood.push_back(nextNeighbour);
			moves.push_back(move);
		}
	}

	return neighbourhood;
}

int Matrix::pathCostTabu(std::vector<int> permutation)
{
	int totalCost = 0;
	int startingCityIndex = permutation.at(0);
	int lastCityIndex = permutation.at(permutation.size() - 1);

	for (int i = 0; i < permutation.size() -1; i++)
	{
		int currentCity = permutation.at(i);
		int nextOnRoute = permutation.at(i + 1);

		totalCost += data[currentCity][nextOnRoute];
	}
	totalCost += data[lastCityIndex][startingCityIndex];

	return totalCost;
}

