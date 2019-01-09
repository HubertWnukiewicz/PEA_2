#include <iostream>
#include "Matrix.h"
#include <windows.h>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <fstream>

using namespace std;


int main()
{
	srand(time(nullptr));

	Matrix matrix1,matrix3, matrix2;
	matrix1.ReadFromFile("ftv47.atsp"); //120
	matrix2.ReadFromFile("ftv170.atsp");  //240
	matrix3.ReadFromFile("rbg403.atsp"); //360
	//matrix.printMatrix();
	Timer timer;
	int w1, w2, w3, w4;
	vector<int> r1, r2, r3, r4;
	//matrix.resetAtributes();
	/*
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
	
	r1=matrix.initTS(10, timer, 1);
	matrix.printRoute(r1);
	int value = matrix.distance(r1);
	int value2 = matrix.pathCostTabu(r1);
	cout << endl;
	cout <<"distance: "<< value << endl;
	cout << "pathCostTabu: " << value2 << endl;
	*/
	//r1 = matrix.InitSA(60, timer, 0.99);
	//w1 = matrix.getMinSolution();
	//matrix.resetAtributes();
	int value1[10];
	double timetable1[10];
	int value3[10];
	double timetable3[10];
	int value2[10];
	double timetable2[10];
	float a1 = 0.99;
	float a2 = 0.98;
	float a3 = 0.95;
	float a4 = 0.90;
	for (int i = 0; i < 10 ; i++)
	{
		r2 = matrix3.InitSA(360, timer, a1);
		value3[i] = matrix3.distance(r2);
		timetable3[i] = matrix3.getFound();
		matrix3.resetAtributes();
	}
	for (int i = 0; i < 10; i++)
	{
		r2 = matrix2.InitSA(240, timer, a1);
		value2[i] = matrix2.distance(r2);
		timetable2[i] = matrix2.getFound();
		matrix2.resetAtributes();
	}
	for (int i = 0; i < 10; i++)
	{
		r2 = matrix1.InitSA(120, timer, a1);
		value2[i] = matrix1.distance(r2);
		timetable2[i] = matrix1.getFound();
		matrix1.resetAtributes();
	}
	/*
	r1 = matrix.initTS(30, timer, 1);
	matrix.printRoute(r1);
	cout << endl;
	cout << endl;
	int value = matrix.distance(r1);
	cout << "distance: " << value <<",czas "<<matrix.getFound()<< endl;
	matrix.resetAtributes();
	r2 = matrix.InitSA(30, timer, 0.95);
	matrix.printRoute(r2);
	cout << endl;
	cout << endl;
	int value2 = matrix.distance(r2);
	cout << "distance: " << value2 << ",czas " << matrix.getFound() << endl;
	matrix.resetAtributes();
	*/

	fstream plik;
	plik.open("wynikiSA.txt", std::ios::out);
	if (plik.good() == true)
	{
		plik << "SA - rbg403.atsp" << endl;;
		plik << "a= " << a1 << endl;
		for (int i = 0; i < 10; i++)
		{
			plik << "dystans: "<< value3[i]<< ", czas: " <<timetable3[i]<< endl;
		}

		plik << "SA - ftv170.atsp" << endl;;
		plik << "a= " << a1 << endl;
		for (int i = 0; i < 10; i++)
		{
			plik << "dystans: " << value2[i] << ", czas: " << timetable2[i] << endl;
		}
		plik << "SA - ftv47.atsp" << endl;;
		plik << "a= " << a1 << endl;
		for (int i = 0; i < 10; i++)
		{
			plik << "dystans: " << value1[i] << ", czas: " << timetable1[i] << endl;
		}

	}
	plik.close();
	cin.ignore(2);
}