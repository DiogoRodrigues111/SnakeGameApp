// SnakeGameApp.cpp : Defines the entry point for the application.
//

#include "SnakeGameApp.h"
#include <list>
#include <map>

// C
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>


using namespace std;

#define WIDTH 20
#define HEIGHT 20

// Position of the location and others stuff.
// 
static struct position
{
	int x;
	int y;
	int frtyX;
	int frtyY;
} __align(4);

// Direction of snake in console.
//
enum direction
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// System coords.
//
class System
{

public:
	System();
	virtual ~System();

	void _setup();
	void _logicals();
	void _directions();
	void _draw();
	void _clr(const char* clrlock);
	bool is_gameover();

public:
	int tailx[100], taily[100];
	int ntail;
	bool gameover = false;
	struct position pos;
	direction dir;
};

System::System()
{

}

System::~System()
{

}

// Clear console.
//
void System::_clr(const char *clrlock)
{
	system(clrlock);
}

// Condition returns TRUE, Its only returns FALSE in main function.
//
bool System::is_gameover()
{
	return gameover;
}

void System::_setup()
{
	pos.x = WIDTH / 2;
	pos.y = HEIGHT / 2;

	dir = STOP;

	pos.frtyX = rand() % WIDTH;
	pos.frtyY = rand() % HEIGHT;

	gameover = false;
}

// Logicals stuff
//
void System::_logicals()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'd':
			dir = RIGHT;
			break;

		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'a':
			dir = LEFT;
			break;
		}
	}
}

void System::_directions()
{
	int pvX = tailx[0];
	int pvY = taily[0];
	int pv2x, pv2y;

	tailx[0] = pos.x;
	taily[0] = pos.y;

	for (int i = 0; i < ntail; i++)
	{
		pv2x = tailx[i];
		pv2y = taily[i];

		tailx[i] = pv2x;
		taily[i] = pv2y;

		pvX = pv2x;
		pvY = pv2y;
	}

	switch (dir)
	{
	case RIGHT:
		pos.x++;
		break;

	case LEFT:
		pos.x--;
		break;

	case UP:
		pos.y--;
		break;

	case DOWN:
		pos.y++;
		break;
	}

	if (pos.x > WIDTH || pos.x < 0 || pos.y > HEIGHT || pos.y < 0)
	{
		gameover = true;
	}

	for (int i = 0; i < ntail; i++)
	{
		if (tailx[i] == pos.x && taily[i] == pos.y)
			gameover = true;
	}

	if (pos.x == pos.frtyX && pos.y == pos.frtyY)
	{
		pos.frtyX = rand() % WIDTH;
		pos.frtyY = rand() % HEIGHT;
		ntail++;
	}
}

// Draw stuff.
//
void System::_draw()
{
	bool kprint = false;

	_clr("cls");

	cout << endl;
	cout << " " << endl;

	for (int i = 0; i < WIDTH + 2; i++)
		cout << "#";

	cout << endl;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (j == 0)
				cout << "#";

			if (i == pos.y && j == pos.x)
			{
				cout << "O";
			}
			else
			{
				if (i == pos.frtyY && j == pos.frtyX)
				{
					cout << "F";
				}
				else
				{
					for (int k = 0; k < ntail; k++)
					{
						if (tailx[k] == j && taily[k] == i)
						{
							cout << "o";
							kprint = true;
						}
					}

					if (!kprint)
						cout << " ";
				}
			}

			if (j == WIDTH - 1)
				cout << "#";
		}
		cout << endl;
	}
}

void _sleep_ms(long ms)
{
	int i, j;
	for (i = 0; i < 6500 /1000; i++)
		for (j = 0; j < ms % 60; j++)
			continue;
}

int main()
{
	// dont instancing this.
	// access to directly memory, is an possible violation access.
	System sys;

	sys._setup();

	while (!sys.gameover)
	{
		sys._logicals();
		sys._directions();
		sys._draw();

		_sleep_ms(2);
	}

	return 0;
}
