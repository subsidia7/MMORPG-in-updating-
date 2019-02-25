#pragma once
#include "main.h"
#include "Item.h"
class Tile
{
public:
	Tile();
	Tile(char, int);
	void draw(HANDLE, short int, short int);// draw tile
	int color;
	char app;
	bool hasItem = false;
	bool is_comf;
	Item item;
	~Tile();
};

