#pragma once
#include "main.h"
class Item
{
public:
	Item();
	string ID;
	string name;
	char app = 'o';
	short int x,y;
	double weight;
	double cost;
	void draw();
	~Item();
	Item& operator=(const Item& right) {
		//проверка на самоприсваивание
		if (this == &right) {
			return *this;
		}
		this->ID = right.ID;
		this->app = right.app;
		this->name = right.name;
		this->x = right.x;
		this->y = right.y;
		this->weight = right.weight;
		this->cost = right.cost;
		return *this;
	}
};