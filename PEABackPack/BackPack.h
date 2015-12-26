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
#include <fstream>
#include <string>
#include "Item.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <math.h>
#include <time.h>
using namespace std;

	class BackPack {
		int capacity;
		int N; //ilosc elementow

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
	};



#endif /* SRC_BACKPACKPROBLEM_H_ */
