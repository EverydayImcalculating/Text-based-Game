#include <iostream>
#include <windows.h>
#include <conio.h>

int x, y;
char ch = ' ';
int dir;
int fire;


struct Bullet
{
	int xPos = 0;
	int yPos = 0;
	int alive = 0;

} bullets[5];


void Setup();
void gotoxy(int x, int y);
void setcursor(bool visible);
void setcolor(int fg, int bg);

void draw_ship(int x, int y);

void clrscr();

void shootBullet(int index);

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
				for (int i = 0; i < 5; i++)
				{
					if (bullets[i].alive == 0)
					{
						bullets[i].xPos = x + 4;
						bullets[i].yPos = y;
						bullets[i].alive = 1;
						break;
					}
				}
				break;
			}
			fflush(stdin);
		}
		for (int i = 0; i < 5; i++)
		{
			shootBullet(i);
		}
		if (dir == 0)
		{
			draw_ship(x, y);
		}
		if (dir == 1 && x > 0) {
			draw_ship(--x, y);
		}
		else { draw_ship(x, y); }
		if (dir == 2 && x < 111) {
			draw_ship(++x, y);
		}
		else { draw_ship(x, y); }

		Sleep(50);
	} while (ch != 'x');

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
	std::cout << "<'-(0)-'>";
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

void shootBullet(int index)
{
	if (bullets[index].alive)
	{
		gotoxy(bullets[index].xPos, bullets[index].yPos);
		std::cout << " ";
		if (bullets[index].yPos > 0)
		{
			gotoxy(bullets[index].xPos, --bullets[index].yPos);
			std::cout << "\'";
		}
		else
		{
			bullets[index].alive = 0;
		}
	}
}


