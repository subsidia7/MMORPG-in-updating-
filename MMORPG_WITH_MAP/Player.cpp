#include "Player.h"

void push_back(int* &pos, int &length, int value)
{
	int* newPos = new int[length + 1];
	for (int i = 0; i < length; i++)
	{
		newPos[i] = pos[i];
	}
	newPos[length] = value;
	length++;
	delete[] pos;
	pos = newPos;
}

Player::Player(short int x, short int y)
{
	this->x = x;
	this->y = y;
}

void Player::equip(Item item)
{

}

void Player::draw(COORD position, HANDLE hConsole)
{
	SetConsoleCursorPosition(hConsole, { position });
	SetConsoleTextAttribute(hConsole, this->color);
	cout << this->app;
}

void Player::remove(int x, int y, HANDLE hConsole, COORD position)
{
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hConsole, position);
	SetConsoleTextAttribute(hConsole, 15);
	cout << " ";
}

void createPath(Scene* scene, int* &X, int &x_count, int* &Y, int &y_count, int xEnd, int yEnd, int x0, int y0)
{
	while (true)
	{
		if (x0 != xEnd)
		{
			if (x0 < xEnd)
			{
				x0++;
			}
			if (x0 > xEnd)
			{
				x0--;
			}
		}
		if (y0 != yEnd)
		{
			if (y0 < yEnd)
			{
				y0++;
			}
			if (y0 > yEnd)
			{
				y0--;
			}
		}
		push_back(X, x_count, x0);
		push_back(Y, y_count, y0);
		if ((x0 == xEnd) && (y0 == yEnd))
		{
			break;
		}
	}
}

void Player::moveTo(int xEnd, int yEnd, COORD &position, Scene* scene)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int x_count = 1, y_count = 1;
	int x0 = this->x, y0 = this->y;
	int *X = new int[x_count], *Y = new int[y_count];
	X[0] = x0;
	Y[0] = y0;
	createPath(scene, X, x_count, Y, y_count, xEnd, yEnd, x0, y0);
	this->x = xEnd;
	this->y = yEnd;
	for (int i = 1; i < x_count; i++)
	{	
		this->remove(X[i - 1], Y[i - 1], hConsole, position);
		scene->map[Y[i-1]][X[i-1]].draw(hConsole, X[i-1], Y[i-1]);
		position.X = X[i];
		position.Y = Y[i];
		this->draw(position, hConsole);
		Sleep(70);
	}
	delete[] X;
	delete[] Y;
}

Player::~Player()
{
}
