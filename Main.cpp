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
void Opcja2();
void Mainmenu2();
//pea3
int populationSize = 100;
float cross = 0.8;
float mutation = 0.01;

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
void Opcja2()
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
		Mainmenu2();
		break;
	case 2:
		matrix.ReadFromFile("ftv170.atsp");
		nazwa = 2;
		Mainmenu2();
		break;
	case 3:
		matrix.ReadFromFile("rbg403.atsp");
		nazwa = 3;
		Mainmenu2();
		break;
	default:
		cout << "Niepoprawny wybor, sprobuj ponownie" << endl;
		cin.ignore(2);
		system("CLS");
		Opcja2();
		break;
	}
}
void Mainmenu2()
{
	Timer timer;
	int value;
	double tempA = 0.01;
	float found;
	vector<int> route;
	system("CLS");
	int i = 0;
	cout << "---------------------------------" << endl;
	cout << "Hubert Wnukiewicz projekt PEA 3" << endl;
	cout << "---------------------------------" << endl;
	cout << "Obecne wartosci: (czas: " << temptime << "s, wielkosc populacji: " << populationSize << ", wspolczynnik mutacji: " << mutation << ", wspolczynnik krzyzowania" << cross << ",obecny plik: " << plik(nazwa) << "  )." << endl;
	cout << "---------------------------------" << endl;
	cout << "1.Wczytaj graf z pliku" << endl;
	cout << "2.Ustaw kryterium stopu" << endl;
	cout << "3. Ustaw wielkosc populacji poczatkowej" << endl;
	cout << "4. Ustaw wspolczynnik mutacji" << endl;
	cout << "5. Ustaw wspolczynnik krzyzowania" << endl;
	cout << "6. Uruchom algorytm genetyczny" << endl;
	cout << "Twoj wybor: ";
	cin >> i;
	switch (i)
	{
	case 1:
		Opcja2();
		break;
	case 2:
		cout << "Podaj kryterium stopu " << endl;
		cin >> found;
		if (found > 0)
		{
			temptime = found;
		}
		else
			cout << "Niepoprawna wartosc" << endl;
		cin.ignore(2);
		Mainmenu2();
		break;
	case 3:
		cout << "Nowa wartosc to: " << endl;
		cin >> populationSize;
		cin.ignore(2);
		Mainmenu2();
		break;
	case 4:
		cout << "Podaj wspolczynnik mutacji " << endl;
		cin >> tempA;
		if (tempA < 1 && tempA > 0)
		{
			mutation = tempA;
		}
		else
			cout << "Niepoprawna wartosc" << endl;
		cin.ignore(2);
		Mainmenu2();
		break;
	case 5:
		cout << "Podaj wspolczynnik krzyzowania " << endl;
		cin >> tempA;
		if (tempA < 1 && tempA > 0)
		{
			cross = tempA;
		}
		else
			cout << "Niepoprawna wartosc" << endl;
		cin.ignore(2);
		Mainmenu2();
		break;
	case 6:
		route = matrix.initGeneticAlgorithm(populationSize, 200, cross, a, temptime, timer);
		value = matrix.distance(route);
		cout << "Dystans: " << value << endl;
		matrix.printRoute(route);
		cin.ignore(2);
		Mainmenu2();
	default:
		cout << "Niepoprawny wybor, sprobuj ponownie" << endl;
		cin.ignore(2);
		system("CLS");
		Mainmenu2();
		break;
	}
}
int main()
{
	//Matrix matrix;
	srand(time(nullptr));
	//Timer timer;
	//PEA 2
	int x = 1;
	matrix.ReadFromFile("ftv47.atsp"); //120
	cout << "Hubert Wnukiewicz PEA projekt 2 & 3" << endl;
	cout << "-------------------------------------" << endl;
	cout << "1. Projekt 2" << endl;
	cout << "2. Projetk 3" << endl;
	cout << "-------------------------------------" << endl;
	cin >> x;
	switch (x)
	{
	case 1:
		Mainmenu();
		break;
	case 2:
		Mainmenu2();
		break;
	default:
		cout << "Niepoprawny wybor, sprobuj ponownie" << endl;
		cin.ignore(2);
	}

	//Mainmenu();
	
	cin.ignore(2);
}