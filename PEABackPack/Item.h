/*
* Item.h
*
*  Created on: 22 maj 2015
*      Author: Rafal
*/

#ifndef SRC_ITEM_H_
#define SRC_ITEM_H_

namespace std {

	class Item {
		int weight;
		int price;
	public:
		Item();
		Item(int weight, int price);

		int getWeight()const;
		int getPrice()const;
		void setPrice(int price);
		bool operator < (const Item& str) const;
		virtual ~Item();
	};


} /* namespace std */

#endif /* SRC_ITEM_H_ */
