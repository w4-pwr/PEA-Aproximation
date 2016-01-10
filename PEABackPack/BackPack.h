/*
* BackPackProblem.h
*
*  Created on: 22 maj 2015
*      Author: Rafal
*/

#ifndef SRC_BACKPACKPROBLEM_H_
#define SRC_BACKPACKPROBLEM_H_
#include <set>
#include <vector>
#include "Item.h"

using namespace std;

	class BackPack {
		int capacity;
		int N; //ilosc elementow
		int K;// wspolczynnik skalowania
		
		float findMaxPrice();

	public:
		
		vector< Item> possible;

		BackPack();
		BackPack(string file);
		BackPack(int capacity, int N);
		
		virtual ~BackPack();

		void solveDynamically();
		void displayPossible();

		int getN();
		int getCapacity();
		void setCapacity(int cap);
		

		void scaleWeights();
		void solveApproximatly(float epsilon);
		
	};



#endif /* SRC_BACKPACKPROBLEM_H_ */
