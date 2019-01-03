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
	int lastChange = 0;
	this->minSolution = distance(cycle);
	timer.start();

	while (timer.stop() < stoptime /*&& lastChange<1000 */&& temperature>tempMin)
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
				lastChange = 0;
				//cout << "wyliczona trasa: " << tmpDistanceNeighbour <<", a minimum= "<<minSolution<< endl;
				if (tmpDistanceNeighbour < minSolution)
				{
					minimumRoute = cycle;
					minSolution = tmpDistanceNeighbour;
				}
			}
			lastChange++;
			//if (lastChange >= 1000)
			{
			//	break;
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
	this->simulatedAnnealing(cycle, minimumRoute, temp, 0.0001, time , a);
	timer.stop();
	this->minimumRoute.push_back(minimumRoute[0]);
	return minimumRoute;
}
int Matrix::getValue(int * route)
{
	int sum = 0;
	for (int i = 0; i < vertex - 1; i++)
	{
		sum += data[route[i]][route[i + 1]];
	}
	sum += data[route[vertex - 1]][route[0]];
	return sum;
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
	return minimumRoute;
}

void Matrix::tabuSearch(std::vector<int> cycle, std::vector<int>& minimumRoute, float stoptime, int type)
{
	Timer timer;
	minimumRoute = cycle;
	int lastChange = 0;
	const int tempLength = cycle.size()*(cycle.size() - 1) / 2;
	this->minSolution = distance(cycle);
	timer.start();

	while (timer.stop() < stoptime)
	{
		cout << "czas: "<<timer.stop() << endl;
		for (int i = 0; i < tempLength; i++)
		{
			vector<int> cycleNeighbour = this->setNeighboorType(cycle, type);
			int tmpDistance = distance(cycle);
			int tmpDistanceNeighbour = distance(cycleNeighbour);
			if (tmpDistanceNeighbour - tmpDistance > 0)
			{
				this->minimumRoute = cycleNeighbour;
				minSolution = tmpDistanceNeighbour;
			}
		}
	}
}

void Matrix::resetAtributes()
{
	minSolution = INT_MAX;
	for (int i = 0; i < vertex; i++)
		minimumRoute[i] = 0;
}

void Matrix::printRoute(std::vector<int> route)
{
	for (int i = 0; i < vertex; i++)
		std::cout << route[i] << "->";
	std::cout << route[vertex];
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
