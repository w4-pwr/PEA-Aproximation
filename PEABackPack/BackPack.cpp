/*
* BackPackProblem.cpp
*
*  Created on: 22 maj 2015
*      Author: Rafal
*/

#include "BackPack.h"
#include "Item.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;



	BackPack::BackPack(int cap, int numberOfObjects) {
		srand(time(0));
		capacity = cap;
		N = numberOfObjects;
		K = 0;
		int weight, prize;
		for (int i = 0; i < N; i++) {
			weight = (rand() % cap) + (cap / N) + 1; // zeby minimalnie miec wszystkie przedmioty w plecaku
			prize = rand() % 10 + 10;
			possible.push_back(Item(weight, prize));
		}
	}
	BackPack::BackPack(string file) {

		ifstream fin;
		fin.open(file.c_str());
		if (!fin.is_open()) {
			cout << "Brak pliku z danymi";
			capacity = 0;
			N = 0;
			K = 0;
		}
		else {
			int weight, prize;
			fin >> capacity;
			fin >> N;
			K = 0;
			for (int i = 0; i < N; i++) {
				fin >> weight >> prize;
				possible.push_back(Item(weight, prize));
			}
		}
	}

	BackPack::~BackPack() {
		
	}
	int BackPack::getN() {
		return N;
	}
	int BackPack::getCapacity() {
		return capacity;
	}

int BackPack::getPrimCapacity()
{
	if(K!=0)
	{
		return capacity/K;
	}
	return capacity;
	
}




void BackPack::solveApproximatly(float epsilon)
	{
		float pmax = findMaxPrice();
		K = (epsilon*pmax) / getN();
		scalePrices();
		solveDynamically();

	}
	void BackPack::solveDynamically() {
		//inicjalizacja tablicy danych dynamicznych
		int i, j; //j to kolumny i to wiersze
		int** P;
		P = new int*[getN() + 1];
		for (int i = 0; i < getN() + 1;i++)
		{
			P[i] = new int[getPrimCapacity() + 1];
		}

		//wyzerowanie tablicy
		for (int i = 0; i <= getN(); i++) {
			for (int j = 0; j <= getPrimCapacity(); j++) {
				P[i][j] = 0;
			}
		}

		for (i = 1; i <= getN(); i++) {
			for (j = 1; j <= getPrimCapacity(); j++) {
				if (j >= possible[i - 1].getWeight()) {
					P[i][j] = max(P[i - 1][j],
						P[i - 1][j - possible[i - 1].getWeight()]
						+ possible[i - 1].getPrice());
				}
				else {
					P[i][j] = P[i - 1][j];
				}
			}
		}

		cout << endl << P[getN()][getPrimCapacity()] << endl;

		for (int i = 0; i <= getN(); i++) {
			for (int j = 0; j <= getPrimCapacity(); j++) {
				cout.width(5);
				cout << P[i][j] << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < getN() + 1; i++)
		{
			delete[] P[i];
		}
		delete P;
	}
	

	void BackPack::displayPossible() {
		for (int i = 0; i < N; i++) {
			cout << possible[i].getWeight() << "  "
				<< possible[i].getPrice() << endl;
		}
	}

	float BackPack::findMaxPrice()
	{
		vector<Item>::iterator iterator;
		int max = 0;
		for (iterator = possible.begin();iterator != possible.end();iterator++)
		{
			int currentPrice = iterator->getPrice();
			if (max < currentPrice)
				max = currentPrice;
		}
		return max;
	}

	void BackPack::scalePrices()
	{
		vector<Item>::iterator iterator;
		for (iterator = possible.begin(); iterator != possible.end(); iterator++)
		{
			iterator->setPrice(iterator->getPrice()/K);
		}
	}


