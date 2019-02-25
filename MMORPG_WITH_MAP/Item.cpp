#include "Item.h"



Item::Item()
{
}

void Item::draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, { this->x, this->y });
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << this->app;
}

Item::~Item()
{
}
