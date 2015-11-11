#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include<Windows.h>
////////////////////////////
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
////////////////////////////
using namespace std;
bool gameOver;
int screen_width = 10;
int screen_height = 10;
int width = screen_width;
int height = screen_height;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
char p = 'p';
bool wall_present = false;
void Setup()
{
	width = screen_width;
	height = screen_height;
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	foodX = rand() % width;
	foodY = rand() % height;
	score = 0;
}
void Draw()
{
	HANDLE hConsole;
	int col = 12;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	for (int i = 0; i < width + 2; i++)
		cout << ".";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << ".";
			if (i == y && j == x)
				cout << "O";
			else if (i == foodY && j == foodX)
			{
				FlushConsoleInputBuffer(hConsole);

				//SetConsoleTextAttribute(hConsole,20);
				SetConsoleTextAttribute(hConsole, col);
				//system("COLOR 4C");
				cout << "*";
				SetConsoleTextAttribute(hConsole, 10);
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{

						cout << "*";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << ".";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << ".";
	cout << endl;
	cout << "Score:" << score << endl;
}
void Input()
{
	for (int i = 0; i < 10000000; i++);
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (dir != RIGHT)
				dir = LEFT;
			break;
		case 'd':
			if (dir != LEFT)
				dir = RIGHT;
			break;
		case 'w':
			if (dir != DOWN)
				dir = UP;
			break;
		case 's':
			if (dir != UP)
				dir = DOWN;
			break;
		case 'p':
			p = 'p';
			while (_getch() == 'p'){}
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
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
	if (wall_present)
	{
		if (x > width || x < 0 || y > height || y < 0)
			gameOver = true;
	}
	if (!wall_present)
		if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == foodX && y == foodY)
	{
		score += 10;
		foodX = rand() % width;
		foodY = rand() % height;
		nTail++;
	}
}
int main()
{
	char select;

	long int speed = 0;
	HANDLE hConsole;
	int col = 12;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	cout << "\t\t\tSET UP GAME SETTINGS\n";
A:
	cout << "PRESS 'Y' FOR SCREEN TO BE SOLID AND 'N' FOR SCREEN TO BE TRANSPASSING\n";
	cin >> select;
	if (select == 'y' || select == 'Y')
	{
		wall_present = true;
	}
	else if ((select != 'n') && (select != 'N'))
	{
		cout << "\n\t\tWRONG INPUT TRY AGAIN";
		goto A;
	}
B:
	cout << "\n\t\tSET SPEED\n";
	cout << "\n\tFOR MEDIUM SPEED PRESS'M' AND 'S' FOR SLOW\n";
	cin >> select;
	if (select == 'm' || select == 'M'){}
	else if (select == 's' || select == 'S'){}
	else {
		cout << "\n\t\tWRONG INPUT TRY AGAIN";
		goto B;
	}
C:
	cout << "\n\t\tENTER SCREEN WIDTH\n";
	cin >> screen_width;
	if (screen_width <= 0)
	{
		cout << "\n\t\tWRONG INPUT TRY AGAIN";
		goto C;
	}

	cout << "\n\t\tENTER SCREEN HEIGHT\n";
	cin >> screen_height;
	if (screen_height <= 0)
	{
		cout << "\n\t\tWRONG INPUT TRY AGAIN";
		goto C;
	}
	Setup();
	while (!gameOver)
	{

		Draw();
		Input();
		Logic();
		if (select == 'm')
		{
			for (int i = 0; i < 10000; i++);
		}
		else if (speed == 's')
		{
			for (int i = 0; i < 1000; i++)
				for (int j = 0; j < 1000; j++);
		}
	}
	///////////////////////////////////////
	while (1)
	{
		for (int i = 0; i < 1000; i++)
		{
			system("cls");


			gotoxy(i % 100, 1);
			//cout << "mayank";
			cout << "by MAYANK";
			cout << "     score=";
			cout << score;
			for (int j = 0; j < 10000; j++)
				for (int k = 0; k < 10000; k++)
				{
				}
		}
		}

		cout << endl;
		///////////////////////////////////////
		return 0;
	}