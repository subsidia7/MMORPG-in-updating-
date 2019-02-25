#include "push_back.h"
void push_back(Item* &items, int &length, Item temp)
{
	Item* cpy = new Item[length + 1];
	for (int i = 0; i < length; i++)
	{
		cpy[i].ID = items[i].ID;
		cpy[i].name = items[i].name;
		cpy[i].x = items[i].x;
		cpy[i].y = items[i].y;
		cpy[i].cost = items[i].cost;
		cpy[i].weight = items[i].weight;
	}
	cpy[length].ID = temp.ID;
	cpy[length].name = temp.name;
	cpy[length].x = temp.x;
	cpy[length].y = temp.y;
	cpy[length].cost = temp.cost;
	cpy[length].weight = temp.weight;
	length++;
	delete[] items;
	items = cpy;
}
