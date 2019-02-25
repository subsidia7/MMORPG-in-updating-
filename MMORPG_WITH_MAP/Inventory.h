#pragma once
#include "main.h"
#include "Scene.h"
class Inventory
{
public:
	Inventory();
	short int x0 = 66, y0 = 16, width = 40, height = 10;
	double space = 100, cost = 0, weight = 0;
	int item_count = 0;
	Item* items = new Item[item_count];
	void show(HANDLE, int page); // show inventory on screen
	void remove(HANDLE, Scene*);// delete inventory from screen
	void addItem(Item);// add item to the inventory
	void deleteItem(int iter);// delete item from inventory
	bool isEmpty();//return true if inventory is empty
	void calculateFromTo(int &from, int &to, int page);
	~Inventory();
};

