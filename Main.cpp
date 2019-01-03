#include <iostream>
#include "Matrix.h"
#include <windows.h>
#include <math.h>
#include <fstream>
#include <iomanip>

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

long long int read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}
int main()
{
	srand(time(nullptr));
	//long long int frequency, start, elapsed,timer;
	//QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	Matrix matrix;
	matrix.ReadFromFile("ftv47.atsp");
	
	//start = read_QPC();
	//do
	//{
	//	elapsed = read_QPC() - start;
	//	cout << fixed << setprecision(3) << (float)elapsed / frequency << endl;
	//	cout << "timer " << (float)timer << endl;
	//} while ((float)elapsed / frequency <(float)timer); //((float)timer == (float)elapsed);
	cout << "Macierz:" << endl;
	//matrix.printMatrix();
	Timer timer;
	int w1, w2, w3, w4;
	vector<int> r1, r2, r3, r4;
	//matrix.resetAtributes();
	
	r1=matrix.InitSA(120, timer,0.99);
	w1 = matrix.getMinSolution();
	matrix.resetAtributes();
	r2=matrix.InitSA(120, timer, 0.98);
	w2 = matrix.getMinSolution();
	matrix.resetAtributes();
	r3=matrix.InitSA(120, timer, 0.95);
	w3 = matrix.getMinSolution();
	matrix.resetAtributes();
	r4=matrix.InitSA(120, timer, 0.90);
	w4 = matrix.getMinSolution();
	matrix.resetAtributes();
	cout << "--------------------------------------------------wynik a=0.99: " << w1 << endl;
	matrix.printRoute(r1);
	cout << "--------------------------------------------------wynik a=0.98: " << w2 << endl;
	matrix.printRoute(r2);
	cout << "--------------------------------------------------wynik a=0.95: " << w3 << endl;
	matrix.printRoute(r3);
	cout << "--------------------------------------------------wynik a=0.90: " << w4 << endl;
	matrix.printRoute(r4);

	/*
	for (int i = 0; i < 10; i++)
	{
		r1[i] = i;
		r2[i] = i;
		r3[i] = i;
	}
	r1 = matrix.setNeighboorType(r1, 1);
	r2 = matrix.setNeighboorType(r2, 2);
	r3 = matrix.setNeighboorType(r3, 3);
	for (int i = 0; i < 10; i++)
	{
		cout << r1[i] << "->";
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << r2[i] << "->";
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << r3[i] << "->";
	}
	cout << endl;
	*/
	cin.ignore(2);
}