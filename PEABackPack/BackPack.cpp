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
int INF = 1000000007;


BackPack::BackPack(int cap, int numberOfObjects) {
	capacity = cap;
	N = numberOfObjects;
	K = 0;
	int weight, prize;
	for (int i = 0; i < N; i++) {
		weight = (rand() % cap) / 2 + 1; // zeby minimalnie miec wszystkie przedmioty w plecaku
		prize = rand() % N*100 + N*10 + 1;; //empirycznie :D
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

void BackPack::setCapacity(int cap)
{
	capacity = cap;
}







void BackPack::solveApproximatly(float epsilon)
{
	int pmax = findMaxPrice();
	

	K = 1.0*(epsilon*pmax) / getN();
	K = max(K, 1);
	

	//cout << "przed skalowaniem\n";
	//displayPossible();
	cout << endl;
	scaleWeights();
	setCapacity((double)capacity / K);
	//cout << "po skalowaniu\n";
	//displayPossible();

	double** P;
	P = new double*[getN() + 1];
	for (int i = 0; i < getN() + 1; i++)
	{
		P[i] = new double[getN()*pmax + 1];
	}

	for (int p = 0; p <= getN()*pmax; ++p)
		P[0][p] = INF;

	P[0][0] = 0;
	for (int i = 1; i <= getN(); ++i)
		for (int p = 0; p <= getN()*pmax; ++p)
		{
			P[i][p] = P[i - 1][p];
			if (p - possible[i - 1].getPrice() >= 0)
				P[i][p] = min(P[i][p], P[i - 1][p - possible[i - 1].getPrice()] + possible[i - 1].getWeight());
		}


	int res = 0;
	for (int p = 0; p <= getN()*pmax; ++p)
		if (P[getN()][p] <= capacity)
			res = max(res, p);
	cout << "APRO:" << res;

}
void BackPack::solveDynamically() {
	//inicjalizacja tablicy danych dynamicznych
	int i, j; //j to kolumny i to wiersze
	double** P;
	P = new double*[getN() + 1];
	for (int i = 0; i < getN() + 1; i++)
	{
		P[i] = new double[getCapacity() + 1];
	}

	//wyzerowanie tablicy
	for (int i = 0; i <= getN(); i++) {
		for (int j = 0; j <= getCapacity(); j++) {
			P[i][j] = 0;
		}
	}

	for (i = 1; i <= getN(); i++) {
		for (j = 1; j <= getCapacity(); j++) {
			if (j >= possible[i - 1].getWeight()) {
				P[i][j] = max(P[i - 1][j],
					P[i - 1][j - (int)possible[i - 1].getWeight()]
					+ possible[i - 1].getPrice());
			}
			else {
				P[i][j] = P[i - 1][j];
			}
		}
	}
	
	cout <<"DYN" << P[getN()][getCapacity()];
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
	for (iterator = possible.begin(); iterator != possible.end(); iterator++)
	{
		int currentPrice = iterator->getPrice();
		if (max < currentPrice)
			max = currentPrice;
	}
	return max;
}

void BackPack::scaleWeights()
{
	vector<Item>::iterator iterator;
	for (iterator = possible.begin(); iterator != possible.end(); iterator++)
	{
		iterator->setWeight(iterator->getWeight() / K);

	}
}


