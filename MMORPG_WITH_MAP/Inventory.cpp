#include "Inventory.h"

Inventory::Inventory()
{
}

void Inventory::calculateFromTo(int &from, int &to, int page)
{
	from = page * (this->height - 2);
	if (this->item_count >= from)
	{
		if (this->item_count - from > this->height - 2)
		{
			to = from + (this->height - 2);
		}
		else
		{
			to = this->item_count;
		}
		if (this->isEmpty())
		{
			to = 0;
		}
	}
}

void Inventory::show(HANDLE hConsole, int page)
{
	for (short int i = this->y0; i < this->height + this->y0; i++)
	{
		for (short int j = this->x0; j < this->x0 + this->width; j++)
		{
			SetConsoleCursorPosition(hConsole, { j,i });
			cout << " ";
		}
	}
	SetConsoleTextAttribute(hConsole, 120);
	SetConsoleCursorPosition(hConsole, { this->x0,this->y0 });
	for (int i = 0; i < this->width; i++)
	{
		cout << " ";
	}
	SetConsoleCursorPosition(hConsole, { this->x0,this->y0 });
	cout << "Name" << "\t\tcost" << "\tweight";
	SetConsoleCursorPosition(hConsole, { this->x0,this->y0 + 1 });
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << "All" << "\t\t" << this->cost << "\t" << this->weight << "/" << this->space;	
	
	int from, to;
	this->calculateFromTo(from, to, page);
	for (short int i = this->y0 + 2, j = from, x = this->x0; j < to; i++, j++)
	{
		SetConsoleCursorPosition(hConsole, { x, i });
		cout <<  j + 1 << ". " << this->items[j].name << "\t" << this->items[j].cost 
			<< "\t" << this->items[j].weight;
	}
}

void Inventory::remove(HANDLE hConsole, Scene* scene)
{
	for (short int i = this->y0; i < this->height + this->y0; i++)
	{
		for (short int j = this->x0; j < this->x0 + this->width; j++)
		{
			scene->map[i][j].draw(hConsole, j, i);
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
}

void Inventory::addItem(Item item)
{
	this->cost += item.cost;
	this->weight += item.weight;
	push_back(this->items, this->item_count, item);
}

void Inventory::deleteItem(int iter)
{
	this->cost -= this->items[iter].cost;
	this->weight -= this->items[iter].weight;
	pop_from(this->items, this->item_count, iter);
}

bool Inventory::isEmpty()
{
	if (this->item_count == 0)
	{
		return 1;
	}
	return 0;
}

Inventory::~Inventory()
{
	delete[] items;
}
