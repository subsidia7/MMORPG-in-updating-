#include "Scene.h"
Scene::Scene(string filename, string tilesFilename, const int WIDTH, const int HEIGHT)
{
	this->filename = filename;
	this->tilesFilename = tilesFilename;
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
}

void Scene::drawItems()
{
	ifstream file(this->tilesFilename);//open items file
	if (file.is_open())
	{
		this->sceneItems = new Item[this->items_count];//init items array
		Item tempItem;//create temp item
		while (file >> tempItem.ID 
					>> tempItem.name 
					>> tempItem.x 
					>> tempItem.y 
					>> tempItem.cost 
					>> tempItem.weight)
		{
			//while reading thead is not false
			this->map[tempItem.y][tempItem.x].hasItem = true;
			this->map[tempItem.y][tempItem.x].item = tempItem;
			push_back(this->sceneItems, this->items_count, tempItem);
		}
		for (int i = 0; i < this->items_count; i++)
		{
			this->sceneItems[i].draw();//draw all items
		}
	}
	else
	{
		cout << "Can't open file";
	}
	file.close();
}

void Scene::drawScene()
{
	ifstream file(this->filename);
	if (file.is_open())
	{
		this->map = new Tile*[this->HEIGHT];
		string line;
		const int tile_count = 20;
		char tile_app[tile_count] = { 'g','x','b','w',' ','p','y','c','n','e','i','z','o','d','v', 'u','a','r','j','X' };
		int tile_color[tile_count] = { 119,256, 51,102,255, 85,170,187, 68,34, 238,238,221, 17, 79, 139,107,136,256,234 };
		bool tile_comf[tile_count] = { 0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0 , 0,  0,  0,  0,  0,  0 };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (short int i = 0; i < this->HEIGHT; ++i)
		{
			this->map[i] = new Tile[this->WIDTH];
			getline(file, line);
			for (short int j = 0; j < this->WIDTH; j++)
			{
				for (int k = 0; k < tile_count; k++)
				{
					if (line[j] == tile_app[k])
					{
						this->map[i][j].app = tile_app[k];
						this->map[i][j].color = tile_color[k];
						this->map[i][j].is_comf = tile_comf[k];
						this->map[i][j].draw(hConsole, j, i);
						break;
					}
				}
			}
		}
		this->drawItems();
	}
	else
	{
		cout << "Can't open file";
	}
	file.close();
}

void Scene::deleteItem(int iter, Item item)
{
	pop_from(this->sceneItems, this->items_count, iter);
	this->map[item.y][item.x].hasItem = false;
}

Scene::~Scene()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		delete[] map[i];
	}
	delete[] map;
	delete[] sceneItems;
}
