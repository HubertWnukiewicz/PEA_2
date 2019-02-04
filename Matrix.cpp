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
	int ind1 = rand() % (vector.size() - 1) + 1;
	int ind2 = rand() % (vector.size() - 1) + 1;
	while (ind1 == ind2)
		ind2 = rand() % (vector.size() - 1) + 1;
	//SWAP
	//cout << "ind1= " << ind1 << " ,ind2= " << ind2 << endl; 4289
	std::swap(vector[ind1], vector[ind2]);
	return vector;
}
void Matrix::simulatedAnnealing(std::vector<int> cycle, std::vector<int>& minimumRoute, double tempStart, double tempMin, double stoptime, float a)
{
	Timer timer;
	minimumRoute = cycle;
	const int tempLength = 100*cycle.size()*(cycle.size() - 1) / 2;
	double temperature = tempStart;
	this->minSolution = distance(cycle);
	timer.start();

	while (timer.stop() < stoptime && temperature>tempMin)
	{
		std::cout << "czas: " << timer.stop() << std::endl;
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
	for (int i = 0; i < vertex; i++)
	{
		cycle[i] = i;
	}
	double minTemp = 0.00000000000000001;
	double temp = calcTemperature(1000);
	cout << "Temperatura: " << temp << endl;
	timer.reset();
	timer.start();
	this->simulatedAnnealing(cycle, minimumRoute, temp, minTemp, time, a);
	timer.stop();
	return minimumRoute;
}

double Matrix::calcTemperature(int size)
{
	double temp = 0.0;
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
		std::swap(route[i], route[rand() % (vertex - 1) + 1]);
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
	tabuSearch(route, this->minimumRoute, time, type);
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
				if (distance(sCandidate) < distance(bestCandidate))
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
			bestCandidate = getTransformation(cycle);
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

std::vector<std::vector<int>> Matrix::getNeighbourhood(std::vector<int> currentPermutation)
{
	std::vector<std::vector<int>> neighbourhood;
	for (int i = 1; i < vertex - 2; i++) 
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

std::vector<int> Matrix::initGeneticAlgorithm(int populationSize, int generations, double crossingProbability, double mutationProbability, double stopTime, Timer & counter)
{
	std::vector<int> minCycle(populationSize);
	counter.start();
	minCycle = geneticAlgorithm(populationSize, generations, crossingProbability, mutationProbability, stopTime);
	counter.stop();
	minimumRoute = minCycle;
	return minimumRoute;
}

std::vector<int> Matrix::geneticAlgorithm(int populationSize, int generations, double crossingProbability, double mutationProbability, double stopTime)
{
	//generation number indicatior
	int generation = 0;

	//timer to count time of algorithm
	Timer timer;
	timer.start();

	//init and fill population
	std::vector<std::vector<int>> population(populationSize);
	for (int i = 0; i < populationSize; i++)
	{
		population[i] = randomRoute();
	}

	//set minCycle
	std::vector<int> minCycle = population[0];

	//sort population by cycle distance 
	//std::sort has nlog(n) complexity
	std::sort(population.begin(), population.begin() + populationSize, [&](std::vector<int> vec1, std::vector<int> vec2) {
		return (distance(vec1) < distance(vec2));
	});

	//repeat 'generations' times or finish after stopTime
	while (timer.stop() < stopTime  /* && generation < generations*/)
	{
		std::cout << "Timer: " << timer.stop() << endl;
		{
			//every cycle in population has some probability to cross and some to mutate
			for (int i = 0; i < populationSize; i++)
			{
				//get random probability from [0;1] range
				const int probability = (double)rand() / INT_MAX;

				//if probability is in [0;crossingProbability] range then cross this parent
				if (probability < crossingProbability)
				{
					//random second parent
					int parent = rand() % populationSize;
					while (parent == i)
					{
						parent = rand() % populationSize;
					}

					//cross and add child to population
					//todo - add switching methods of crossing if more than 1
					population.push_back(crossingHalfes(population[i], population[parent]));
				}

				//if probability is in [0;mutateProbability] range then mutate this cycle
				if (probability < crossingProbability)
				{
					//mutate and add child to population
					//mutate up to ~0 - 10% of vertices (5% might be swaped with another 5% so 10% will change place)
					population.push_back(mutationRandom(population[i], population[i].size()*0.05));
				}
			}
		}

		//sort again but this time whole population vector
		//( in TOP selection method ! ) so better results from mutation and crossing will move to first (100%) part of population 
		//and will be considered in further generations during mutations and crossing
		//therefore the worst results will move from first part to next and will be totaly replaced in next generation
		std::sort(population.begin(), population.end(), [&](std::vector<int> vec1, std::vector<int> vec2) {
			return (distance(vec1) < distance(vec2));
		});

		population.resize(populationSize);

		if (distance(minCycle) > distance(population[0]))
		{
			minCycle = population[0];
		}
		//go to next generation
		generation++;
	}
	return minCycle;
}

std::vector<int> Matrix::crossingHalfes(std::vector<int> parent1, std::vector<int> parent2)
{
	//child of parents will be:
	// -first half of vertices in cycle will be the same as first half of parent1's
	// -second half of child's vertices will be filled in the same order of missing vertices as in parent2

	int inserted = parent1.size() / 2;
	bool found = false;

	//copy first half from parent1
	std::vector<int> child(parent1.size(), -1);
	for (int i = 0; i < child.size() / 2; i++)
	{
		child[i] = parent1[i];
	}

	//add elements from parent2 to child
	for (int element : parent2)
	{
		found = false;
		//check if element exist in child
		for (int i = 0; i < inserted; i++)
		{
			if (element == child[i])
			{
				found = true;
				break;
			}
		}

		//if not insert element
		if (!found)
		{
			child[inserted++] = element;
		}
	}

	return child;
}
std::vector<int> Matrix::mutationRandom(std::vector<int> parent, int levelsOfMutation)
{
	for (int i = 0; i < levelsOfMutation; i++)
	{
		//rand elements
		int idx1 = rand() % (parent.size() - 1) + 1;
		int idx2 = rand() % (parent.size() - 1) + 1;

		while (idx1 == idx2)
		{
			idx2 = rand() % (parent.size() - 1) + 1;
		}

		std::swap(parent[idx1], parent[idx2]);
	}

	return parent;
}