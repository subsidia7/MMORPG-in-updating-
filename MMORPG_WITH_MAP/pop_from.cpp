#include "pop_from.h"
void pop_from(Item* &items, int &length, int iter)
{
	Item* cpy = new Item[length - 1];
	for (int i = 0; i < iter; i++)
	{
		cpy[i].ID = items[i].ID;
		cpy[i].name = items[i].name;
		cpy[i].x = items[i].x;
		cpy[i].y = items[i].y;
		cpy[i].cost = items[i].cost;
		cpy[i].weight = items[i].weight;
	}
	for (int j = iter + 1, i = iter; i < length - 1; j++, i++)
	{
		cpy[i].ID = items[j].ID;
		cpy[i].name = items[j].name;
		cpy[i].x = items[j].x;
		cpy[i].y = items[j].y;
		cpy[i].cost = items[j].cost;
		cpy[i].weight = items[j].weight;
	}
	length--;
	delete[] items;
	items = cpy;
}