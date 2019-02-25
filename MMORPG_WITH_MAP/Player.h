#pragma once
#include "main.h"
#include "Scene.h"
#include "Inventory.h"
class Player
{
public:
	Player(short int x, short int y);
	char app = 'O';
	int current_health = HEALTH, HEALTH = 20, exp = 0, color = 14;
	double damage = 5;
	short int x, y;
	Inventory inventory;
	void draw(COORD position, HANDLE hConsole);//draw player
	void moveTo(int xEnd, int yEnd, COORD &position, Scene*);//move player to {xEnd, yEnd}
	void equip(Item item);//equip item
	void remove(int x, int y, HANDLE hConsole, COORD position);//clear player from screen
	~Player();
};

