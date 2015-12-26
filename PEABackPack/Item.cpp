/*
* Item.cpp
*
*  Created on: 22 maj 2015
*      Author: Rafal
*/

#include "Item.h"

namespace std {

	Item::Item() {
		weight = 0;
		price = 0;

	}
	Item::Item(int w, int p) {
		weight = w;
		price = p;

	}
	int Item::getWeight() const {
		return weight;
	}
	int Item::getPrice() const {
		return price;
	}

	bool Item::operator < (const Item& str) const
	{
		return (1.0*price / weight > 1.0*str.getPrice() / str.getWeight());
	}

	Item::~Item() {
		// TODO Auto-generated destructor stub

	}

} /* namespace std */
