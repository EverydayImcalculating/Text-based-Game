#include <iostream>
#include <windows.h>
#include <time.h>
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

struct Score
{
	int hit = 0;
	int scorecount = 0;
};

Score score;

void Setup();
void gotoxy(int x, int y);
char cursor(int x, int y);
void setcursor(bool visible);
void setcolor(int fg, int bg);

void draw_ship(int x, int y);
void erase_ship(int x, int y);

void clrscr();

void updateBullet(int index);

void draw_star(int n);

void scoreInit();
void updateScore();


int main()
{
	Setup();
	do
	{
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
						bullets[i].yBull = y - 1;
						bullets[i].alive = 1;
						if (bullets[i].alive == 1)
						{
							Beep(500, 100);
						}
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

		erase_ship(x, y);

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
		if (dir == 2)
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
	srand(time(NULL));

	scoreInit();
	draw_star(20);
	
	draw_ship(x, y);
	setcursor(0);
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

char cursor(int x, int y) 
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
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

void erase_ship(int x, int y)
{
	setcolor(7, 0);
	gotoxy(x, y);
	cout << "         ";
}

void setcursor(bool visible)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = 100;
	lpCursor.bVisible = visible;
	SetConsoleCursorInfo(consoleHandle, &lpCursor);
}


void draw_star(int n) // Draw star n times.
{
	int x, y;
	setcolor(7, 0);

	for (int i = 0; i <= n; i++)
	{
		x = 10 + (rand()%60); // x = 10 - 60
		y = 2 + (rand()%3); // y = 2 - 5
		gotoxy(x, y);
		cout << "*";
	}

}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void updateBullet(int index)
{
	setcolor(7, 0);
	if (bullets[index].alive)
	{
		gotoxy(bullets[index].xBull, bullets[index].yBull);
		cout << " ";
		if (bullets[index].yBull > 0)
		{
			if (cursor(bullets[index].xBull, bullets[index].yBull - 1) == '*')
			{
				score.hit = 1;
				if (score.hit == 1)
				{
					Beep(800, 100);
					updateScore();
				}
			} 
			gotoxy(bullets[index].xBull, --bullets[index].yBull);
			cout << "\'";
			
		}
		else
		{
			bullets[index].alive = 0;
		}
	}
	
}

void scoreInit()
{
	gotoxy(100, 1);
	cout << "SCORE : 0";
}

void updateScore()
{
	++score.scorecount;
	gotoxy(108, 1);
	cout << score.scorecount;
	score.hit = 0;
}
