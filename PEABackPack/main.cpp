#include <iostream>
#include<string>
#include <windows.h>
#include "BackPack.h"

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
	BackPack backpackProblem();
	//backpackProblem.solveBrute();
}

void solveFileData()
{
	string name;
	cout << "Podaj nazwe pliku z danymi:";
	cin >> name;
	BackPack backpackProblem(name);
	backpackProblem.solveDynamically();
}

void solveRandomData()
{
	BackPack backpackProblem(10,5);
	backpackProblem.displayPossible();
	backpackProblem.solveDynamically();
}

void showMenu()
{
	int choose;
	bool condition = true;
	do
	{
		cout << "*************************************\n";
		cout << "Rozwiazanie problemu plecakowego, podejscie dynamiczne:\n";
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
	showMenu();
	return 0;
}
