#include "main.h"
#include "Scene.h"
#include "InventoryMoving.h"
#include "Player.h"
#include "ProcessEvents.h"
#include <conio.h>
HANDLE hConsole;
COORD position;
const int SCENE_HEIGHT = 43, SCENE_WIDTH = 172;

void Setup(Player*& hero, Scene*& scene )//init all main things
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//init handle
	position = {hero->x, hero->y};//init main position
	system("mode con:cols=172 lines=43");//set scren height width
	scene->drawScene();//draw current scene
	hero->moveTo(hero->x, hero->y, position, scene);//set player on start point
}

void gameLoop(Player*& hero, Scene* scene)//input data
{
	while (true)
	{
		switch (_getch())
		{
		case 77:
		{// нажата клавиша вправо
				if (position.X < SCENE_WIDTH - 1)
					SetConsoleCursorPosition(hConsole, { ++position.X, position.Y });
				break;
		}
		case 75:
		{// нажата клавиша влево
				if (position.X > 0)
					SetConsoleCursorPosition(hConsole, { --position.X, position.Y });
				break;
		}
		case 80:
		{// нажата клавиша вниз
				if (position.Y < SCENE_HEIGHT - 1)
					SetConsoleCursorPosition(hConsole, { position.X, ++position.Y });
				break;
		}
		case 72:
		{// нажата клавиша вверх
				if (position.Y > 0)
					SetConsoleCursorPosition(hConsole, { position.X, --position.Y });
				break;
		}
		case 13:
		{// нажат enter
			hero->moveTo(position.X, position.Y, position, scene);
			processEvents(scene, hero);
			break;
		}
		case 'i':
		{//открывает инвентарь
			int page = 0;
			hero->inventory.show(hConsole, page);
			InventoryMoving(hero, hero->inventory, hConsole, scene, page);
			SetConsoleCursorPosition(hConsole, position);
			break;
		}
		case 'c':
		{//показывает состо€ние персонажа

			SetConsoleCursorPosition(hConsole, position);
			break;
		}
		}
	}
}

int main()
{
	/*	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < 20; i++)
		{
			SetConsoleTextAttribute(Console, i);
			cout << i << endl;
		}
		system("pause");*/
	Player h(10, 20);//init player
	Player* hero = &h;//get player pointer
	//init array of scene filenames
	string scenes[2] = { "D:\\C++ project\\Ќечто игровое\\MMORPG_WITH_MAP\\MMORPG_WITH_MAP\\town_ver2_widthX2.txt", "scene2.txt" };
	Scene s(scenes[0],"D:\\C++ project\\Ќечто игровое\\MMORPG_WITH_MAP\\MMORPG_WITH_MAP\\items_for_town.txt", SCENE_WIDTH, SCENE_HEIGHT);//init first scene
	Scene* currentScene = &s;//get first scene pointer
	Setup(hero, currentScene);//init all constants and global vars
	gameLoop(hero, currentScene);//start main loop

	delete[] hero;
	delete[] currentScene;
	
	system("pause");
	return 0;
}