#pragma once
#include "main.h"
#include "Tile.h"
#pragma once
#include "Item.h"
#include "push_back.h"
#include "pop_from.h"
class Scene
{
public:
	Scene(string filename, string tilesFilename, const int WIDTH, const int HEIGHT);
	void drawScene();
	void drawItems();
	void deleteItem(int, Item);
	string filename, tilesFilename;
	int HEIGHT, WIDTH, items_count = 0;
	Item* sceneItems;
	Tile** map;
	~Scene();
};

