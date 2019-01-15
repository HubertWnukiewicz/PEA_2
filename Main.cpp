#include <iostream>
#include "Matrix.h"
#include <windows.h>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <fstream>
#include <String>
Matrix matrix;
double temptime = 30;
float a = 0.95;
int nazwa=1;
using namespace std;
void Opcja1();

string plik(int nazwa)
{
	string nazwapliku= "ftv47.atsp";
	if (nazwa == 1)
		nazwapliku = "ftv47.atsp";
	else if (nazwa == 2)
		nazwapliku = "ftv170.atsp";
	else if (nazwa == 3)
		nazwapliku = "rbg403.atsp";
	return nazwapliku;
}
void Mainmenu()
{
	Timer timer;
	int value;
	double found = 0;
	double tempA=0.95;
	vector<int> route;
	system("CLS");
	int i = 0;
	cout << "---------------------------------" << endl;
	cout << "Hubert Wnukiewicz projekt PEA 2" << endl;
	cout << "---------------------------------" << endl;
	cout << "Obecne wartoœci: (czas: " <<temptime<<"s, wspolczynnik temperatury: "<<a<<",obecny plik: "<<plik(nazwa) <<"  )." <<endl;
	cout << "---------------------------------" << endl;
	cout << "1.Wczytaj graf z pliku" << endl;
	cout << "2.Ustaw kryterium stopu" << endl;
	cout << "3. Uruchom algorytm TS" << endl;
	cout << "4. Ustaw wspolczynnik temperatury" << endl;
	cout << "5. Uruchom algorytm SW" << endl;
	cout << "Twoj wybor: ";
	cin >> i;
	switch (i)
	{
	case 1:
		Opcja1();
		break;
	case 2:
		cout << "Podaj kryterium stopu " << endl;
		cin >> found;
		if (found >0)
		{
			temptime = found;
		}
		else
			cout << "Niepoprawna wartosc" << endl;
		cin.ignore(2);
		Mainmenu();
		break;
	case 3:
		route=matrix.initTS(temptime, timer, 1);
		cout << "Dystans: " << matrix.distance(route) << endl;
		cout << "Czas znalezienia najlepszego rozwiazania: " << matrix.getFound() << endl;
		cout << "Trasa: " << endl;
		matrix.printRoute(route);
		matrix.resetAtributes();
		cin.ignore(2);
		Mainmenu();
		break;
	case 4:
		cout << "Podaj wspolczynnik temperatury " << endl;
		cin >> tempA;
		if (tempA < 1 && tempA > 0)
		{
			a = tempA;
		}
		else
			cout << "Niepoprawna wartosc" << endl;
		cin.ignore(2);
		Mainmenu();
		break;
	case 5:
		route = matrix.InitSA(temptime, timer, a);
		cout << "Dystans: " << matrix.distance(route) << endl;
		cout << "Czas znalezienia najlepszego rozwiazania: " << matrix.getFound() << endl;
		cout << "Trasa: " << endl;
		matrix.printRoute(route);
		matrix.resetAtributes();
		cin.ignore(2);
		Mainmenu();
		break;
	default:
		cout << "Niepoprawny wybor, sprobuj ponownie" << endl;
		cin.ignore(2);
		system("CLS");
		Mainmenu();
		break;
	}
}
void Opcja1()
{
	system("CLS");
	int i = 0;
	cout << "---------------------------------" << endl;
	cout << "WCZYTANIE PLIKU " << endl;
	cout << "---------------------------------" << endl;
	cout << "1.ftv47.atsp" << endl;
	cout << "2.ftv170.atsp" << endl;
	cout << "3.rbg403.atsp" << endl;
	cin >> i;
	switch (i)
	{
	case 1:
		matrix.ReadFromFile("ftv47.atsp"); //120
		nazwa = 1;
		Mainmenu();
		break;
	case 2:
		matrix.ReadFromFile("ftv170.atsp");
		nazwa = 2;
		Mainmenu();
		break;
	case 3:
		matrix.ReadFromFile("rbg403.atsp");
		nazwa = 3;
		Mainmenu();
		break;
	default:
		cout << "Niepoprawny wybor, sprobuj ponownie" << endl;
		cin.ignore(2);
		system("CLS");
		Opcja1();
		break;
	}
}
int main()
{
	srand(time(nullptr));
	//Timer timer;
	//PEA 2
	matrix.ReadFromFile("ftv47.atsp"); //120
	Mainmenu();
	/*
	int tab1[10],tab2[10],tab3[10];
	vector<int> w1[10], w2[10],w3[10];

	for (int i = 0; i < 10; i++)
	{
		w1[i]=matrix.InitSA(15, timer, 0.99);
		tab1[i] = matrix.distance(w1[i]);
		matrix.resetAtributes();
	}
	for (int i = 0; i < 10; i++)
	{
		w2[i] = matrix.initTS(15, timer, 0.99);
		tab2[i] = matrix.distance(w2[i]);
		matrix.resetAtributes();
	}
	for (int i = 0; i < 10; i++)
	{
		w3[i] = matrix.initGeneticAlgorithm(500, 200, 0.8, 0.01, 30, timer);
		tab3[i] = matrix.distance(w3[i]);
		matrix.resetAtributes();
	}
	for (int i = 0; i < 10; i++)
	{
		cout << "SA[" << i << "] = "<<tab1[i] << endl;
		matrix.printRoute(w1[i]);
		cout << endl;
		cout << "TS[" << i << "] = " << tab2[i] << endl;
		matrix.printRoute(w2[i]);
		cout << endl;
		cout << "GA[" << i << "] = " << tab3[i] << endl;
		matrix.printRoute(w3[i]);
		cout << endl;
	}*/
	cin.ignore(2);
}