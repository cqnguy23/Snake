#include <iostream>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <windows.h>
using namespace std;
bool over;
const int width = 20;
const int height = 20;
int x, y, targetX, targetY, score;
int tailX[width * height];
int tailY[width * height];
int numTail; 
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction dir;
void setup()
{
	srand(time(NULL));
	over = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	targetX = rand() % width;
	targetY = rand() % height;
	while (targetX == 0 || targetX == width - 1)
	{
		targetX = rand() % width;
	}
	while (targetY == 0 || targetY == height - 1)
	{
		targetY = rand() % height;
	}
	score = 0;
	
}
void draw()
{
	system("cls");
	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 0; j < width; j++)
		{
			
			if (i == y && j == x)
				cout << "O";
			else if (i == targetY && j == targetX)
				cout << "T";
			else if (j == 0 || j == width - 1)
				cout << "#";
			else
			{
				int print = false;
				for (int k = 0; k < numTail; k++)
					if (i == tailY[k] && j == tailX[k])
					{
						cout << "o";
						print = true;
					}
				if (!print)
				cout << " ";

			}	
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "SCORE: " << score << endl;
	
	cout << "**Note: The snake cannot make a 180 degree turn if it has a tail" << endl;
	cout << "Press 'X' to exit" << endl;
}
void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			dir = LEFT;
			over = true;
			break;
		}
	}
}
void logic()
{
	int preX = tailX[0];
	int preY = tailY[0];
	int preX2, preY2;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < numTail; i++)
	{
		preX2 = tailX[i];
		preY2 = tailY[i];

		tailX[i] = preX;
		tailY[i] = preY;

		preX = preX2;
		preY = preY2;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x >= width - 1 || x <= 0 || y >= height - 1 || y <= 0)
		over = true;
	/* if (x >= width - 1)
	{
		x = 0;
	}
	else if (x <= 0)
		x = width - 1;

	if (y >= height - 1)
	{
		y = 0;
	}
	else if (y <= 0)
		y = height - 1;
		*/
	if (x == targetX && y == targetY)
	{
		
		score+=10;
		targetX = rand() % width;
		targetY = rand() % height;
		while (targetX == 0 || targetX == width - 1)
		{
			targetX = rand() % width;
		}
		while (targetY == 0 || targetY == height - 1)
		{
			targetY = rand() % height;
		}
		numTail++;
	}

	for (int i = 1; i < numTail; i++)
	{
		if (x == tailX[i] && y == tailY[i])
			over = true;
	}
}
int main()
{
	setup();
	int diff;
	int delay;
	cout << "----SNAKE GAME-----" << endl;
	cout << endl << "A: Move Left; S: Move Down; D: Move Right; W: Move Up" << endl;
	cout << endl << "Choose your difficulty" << endl << "1: easy" << endl << "2: medium" << endl << "3: hard" << endl;
	cin >> diff;
	if (diff == 1)
		delay = 100;
	else if (diff == 2)
		delay = 50;
	else
		delay = 20;
	while (!over)
	{
		draw();
		input();
		logic();
		Sleep(delay);
	}
	cout << "----Game Over!!!-----" << endl;
	return 0;
}
