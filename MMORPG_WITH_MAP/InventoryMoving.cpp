#include "InventoryMoving.h"
#include <conio.h>

void arrowUp(HANDLE hConsole, COORD &ArrowPos, string arrow, int limit)
{
	if (ArrowPos.Y > limit)
	{
		SetConsoleCursorPosition(hConsole, ArrowPos);
		cout << "   ";
		SetConsoleCursorPosition(hConsole, { ArrowPos.X, --ArrowPos.Y });
		cout << arrow;
	}
}

void arrowDown(HANDLE hConsole, COORD &ArrowPos, string arrow, int limit)
{
	if (ArrowPos.Y < limit)
	{
		SetConsoleCursorPosition(hConsole, ArrowPos);
		cout << "   ";
		SetConsoleCursorPosition(hConsole, { ArrowPos.X, ++ArrowPos.Y });
		cout << arrow;
	}
}

void write(HANDLE hConsole, string word, int color, short int x, short int y)
{
	SetConsoleTextAttribute(hConsole, color);
	SetConsoleCursorPosition(hConsole, { x,y });
	cout << word;
}

void back(Scene* scene, HANDLE hConsole, int y, int x0)
{
	for (int i = y; i < y + 3; i++)
	{
		for (int j = x0; j < x0 + 13; j++)
		{
			scene->map[i][j].draw(hConsole, j, i);
		}
	}
	return;
}

void inventoryInteriorMenu(int y, Inventory &inv)
{
	short int width = 13;
	short int x0 = inv.x0 + inv.width;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	string words[] = { "Equip", "Delete", "Back" };
	for (short int i = y, k = 0, color = 10; i < y + 3; i++, k++, color+=2)
	{
		for (short int j = x0; j < x0 + width; j++)
		{
			SetConsoleCursorPosition(hConsole, { j, i });
			cout << " ";
		}
		write(hConsole, words[k], color, x0, i);
	}
}

void inventoryInteriorMoving(short int y, Inventory &inv, string arrow, Player* &player, Scene* scene, const int page)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	short int x0 = inv.x0 + inv.width + 10;//13 is a width of interior but arrow length is 3
	COORD interPos = { x0,y };
	SetConsoleCursorPosition(hConsole, interPos);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << arrow;
	while (true)
	{
		switch (_getch())
		{
		case 80:
		{// нажата клавиша вниз
			arrowDown(hConsole, interPos, arrow, y + 2);
			break;
		}
		case 72:
		{// нажата клавиша вверх
			arrowUp(hConsole, interPos, arrow, y);
			break;
		}
		case 13:
		{// нажат enter
			switch (interPos.Y - y)
			{
			case 0:
			{
				if (y - inv.y0 - 2 + page * (inv.height - 2) < player->inventory.item_count)
				{
					player->equip(inv.items[interPos.Y - y]);
				}
				back(scene, hConsole, y, inv.x0 + inv.width);
				return;
				break;
			}
			case 1:
			{
				if (y - inv.y0 - 2 + page * (inv.height - 2) < player->inventory.item_count)
				{
					inv.deleteItem(y - inv.y0 - 2 + page * (inv.height - 2));
				}
				back(scene, hConsole, y, inv.x0 + inv.width);
				return;
				break;
			}
			case 2:
			{
				back(scene, hConsole, y, inv.x0 + inv.width);
				return;
				break;
			}
			}
			break;
		}
		}
	}
}

void InventoryMoving(Player* &player, Inventory &inv, HANDLE hConsole, Scene* scene, int &page)
{
	COORD ArrowPos;
	string arrow = "<--";
	ArrowPos.X = inv.x0 + inv.width - 4;//position of arrow
	ArrowPos.Y = inv.y0 + 2;
	SetConsoleCursorPosition(hConsole, ArrowPos);
	cout << arrow;
	while (true)
	{
		switch (_getch())
		{
		case 'i':
		{//close inventory
			inv.remove(hConsole, scene);//delete inventory from screen
			player->draw({ player->x,player->y }, hConsole);//player redraw
			return;
			break;
		}
		case 80:
		{// нажата клавиша вниз
			arrowDown(hConsole, ArrowPos, arrow, inv.y0 + inv.height - 1);
			break;
		}
		case 72:
		{// нажата клавиша вверх
			arrowUp(hConsole, ArrowPos, arrow, inv.y0 + 2);
			break;
		}
		case 77:
		{// нажата клавиша вправо
			if (inv.item_count > (page + 1) * (inv.height - 2))
			{
				inv.show(hConsole, ++page);
				return InventoryMoving(player, inv, hConsole, scene, page);
			}
			break;
		}
		case 75:
		{// нажата клавиша влево
			if (page != 0)
			{
				inv.show(hConsole, --page);
				return InventoryMoving(player, inv, hConsole, scene, page);
			}
			break;
		}
		case 13:
		{// нажат enter
			if (!inv.isEmpty())
			{
				inventoryInteriorMenu(ArrowPos.Y, inv);//draw interior menu 
				inventoryInteriorMoving(ArrowPos.Y, inv, arrow, player, scene, page);
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
				inv.show(hConsole, page);
				return InventoryMoving(player, inv, hConsole, scene, page);
			}
			break;
		}
		}	
	}
}