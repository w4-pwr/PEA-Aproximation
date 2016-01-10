#include <iostream>
#include<string>
#include <windows.h>
#include "BackPack.h"
#include <ctime>

using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;


void StartCounter(){
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}


void solveExampleData()
{
	BackPack backpackProblem("dane.txt");
}

void solveFileData()
{
	string name;
	cout << "Podaj nazwe pliku z danymi:";
	cin >> name;
	BackPack backpackProblem(name);
	backpackProblem.solveApproximatly(0.1);
}

void solveRandomData()
{
	BackPack backpackProblem(10,5);
	backpackProblem.displayPossible();
	backpackProblem.solveApproximatly(0.1);
}

void showMenu()
{
	int choose;
	bool condition = true;
	do
	{
		cout << "*************************************\n";
		cout << "Rozwiazanie problemu plecakowego, podejscie aproksymacyjne:\n";
		cout << " 1 - Dane przykladowe\n";
		cout << " 2 - Dane z pliku\n";
		cout << " 3 - Dane wygenerowane \n";
		cout << " 0 - Powrót do poprzedniego menu\n";
		cout << " Twój wybór: ";

		cin >> choose;

		switch (choose)
		{
		case 1:
			solveExampleData();
			break;
		case 2:
			solveFileData();
			break;
		case 3:
			solveRandomData();
			break;

		case 0:
			cout << "Koñczenie pracy programu";
			condition = false;
			break;
		default:
			cout << "Niepoprawny wybór \n";
			cout << "Spróbuj ponownie.\n";
			cin >> choose;
			break;
		}
	}while (condition != false);
}


int main()
{
	//showMenu();
	srand(time(NULL));
	int ns[] = {200,250,300,500,750,1000,2000,3000,3500,4000,5000,6000,7500,8000,10000};

	for (int i = 0; i <10; i++)
	{
		
			BackPack backpackProblem(ns[i], ns[i]/100);
			//backpackProblem.displayPossible();
			cout << ns[i];
			StartCounter();
			backpackProblem.solveDynamically();
			double time = GetCounter();
			//cout <<"dyn: " <<	time;
			StartCounter();
			backpackProblem.solveApproximatly(0.8);
			time = GetCounter();
			//cout << "apr: " << time;
			cout << endl;

	}

//	BackPack backpackProblem(200, 5);
//	BackPack backpackProblem("dane.txt");
//	backpackProblem.solveDynamically();
//
//	BackPack backpackProblem2("dane.txt");


//	backpackProblem2.solveApproximatly(0.1);

	int rafal;
	cin >> rafal;
	

	return 0;
}
