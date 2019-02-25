#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(char app, int color)
{
	this->app = app;
	this->color = color;
}

void Tile::draw(HANDLE hConsole, short int x, short int y)
{
	if (this->hasItem)
	{
		this->item.draw();
		return;
	}
	SetConsoleCursorPosition(hConsole, { x,y });
	SetConsoleTextAttribute(hConsole, this->color);
	cout << this->app;
}

Tile::~Tile()
{
}
