#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

int x, y;
char ch = ' ';
int dir;

const int MAX_BULLETS = 5;

struct Bullet
{
	int xBull = 0;
	int yBull = 0;
	int alive = 0;

} bullets[MAX_BULLETS];


void Setup();
void gotoxy(int x, int y);
void setcursor(bool visible);
void setcolor(int fg, int bg);

void draw_ship(int x, int y);

void clrscr();

void updateBullet(int index);

int main()
{
	Setup();
	do
	{
		clrscr();

		if (_kbhit()) {
			ch = _getch();
			switch (ch)
			{
			case'a':
				dir = 1;
				break;
			case 'd':
				dir = 2;
				break;
			case 's':
				dir = 0;
				break;
			case ' ':
				for (int i = 0; i < MAX_BULLETS; i++)
				{
					if (bullets[i].alive == 0)
					{
						bullets[i].xBull = x + 4;
						bullets[i].yBull = y;
						bullets[i].alive = 1;
						break;
					}
				}
				break;
			}
			fflush(stdin);
		}
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			updateBullet(i);
		}
		if (dir == 0)
		{
			draw_ship(x, y);
		}
		if (dir == 1) {
			if (x > 0)
			{
				draw_ship(--x, y);
			}
			else { draw_ship(++x, y); dir = 0; }
		}
		if (dir == 2 ) 
		{
			if (x < 111) 
			{
				draw_ship(++x, y);
			}
			else { draw_ship(--x, y); dir = 0; }
		}
		Sleep(100);
	} while (ch != 'x');

	setcolor(7, 0);
	return 0;
}


void Setup()
{

	x = 50, y = 28; // Screensize 120x30.
	dir = 0;

	draw_ship(x, y);
	setcursor(0);
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clrscr()
{
	setcolor(7, 0);
	system("cls");
}

void draw_ship(int x, int y)
{
	setcolor(2, 4);
	gotoxy(x, y);
	cout << "<'-(0)-'>";
}

void setcursor(bool visible)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = 100;
	lpCursor.bVisible = visible;
	SetConsoleCursorInfo(consoleHandle, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void updateBullet(int index)
{
	if (bullets[index].alive)
	{
		gotoxy(bullets[index].xBull, bullets[index].yBull);
		cout << " ";
		if (bullets[index].yBull > 0)
		{
			gotoxy(bullets[index].xBull, --bullets[index].yBull);
			cout << "\'";
		}
		else
		{
			bullets[index].alive = 0;
		}
	}
}


