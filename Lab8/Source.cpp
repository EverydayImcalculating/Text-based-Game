#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string>
using namespace std;

#define scount 80 
#define screen_x 80 
#define screen_y 25 


HANDLE wHnd;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0,0 };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
HANDLE rHnd;
DWORD fdwMode;
DWORD numEvents = 0;
DWORD numEventsRead = 0;
COORD playerPos = { 0,0 };

bool gameOn = 1;
const char* starCh = "*";
const char* playerShip = "<'-0-'>";
short color = 7;
int live = 10;

struct Star
{
	COORD position;

} star[scount];

void Setup();

int randrange(int start, int stop)
{
	return rand() % (stop - start + 1) + start;
}

void clear_buffer()
{
	for (int y = 0; y < screen_y; ++y)
	{
		for (int x = 0; x < screen_x; ++x)
		{
			consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
			consoleBuffer[x + screen_x * y].Attributes = 7;
		}
	}
}

void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
}

void init_star()
{
	for (int i = 0; i < scount; i++)
	{
		star->position = { short(randrange(0,screen_x)),short(randrange(0,screen_y)) };
		star[i] = { star->position.X,star->position.Y };
	}
}

void star_fall()
{
	int i;
	for (i = 0; i < scount; i++)
	{
		if (star[i].position.Y >= screen_y - 1)
		{
			star[i] =
			{ short((rand() % screen_x)),1 };
		}
		else
		{
			star[i].position.Y++;
			if (star[i].position.Y == playerPos.Y && playerPos.X <= star[i].position.X && star[i].position.X < playerPos.X + 7)
			{
				--live;
				star[i] = { short(rand() % screen_x), 1 };
			}

		}
	}
}

void draw(const char* strCh, COORD coord, unsigned short color = 7)
{
	int x = coord.X;
	int y = coord.Y;
	for (int i = 0; i < strlen(strCh); i++)
	{
		if (x >= 0 && x < screen_x)
		{
			consoleBuffer[x + screen_x * y].Char.AsciiChar = strCh[i];
			consoleBuffer[x + screen_x * y].Attributes = color;
		}
		x++;
	}
}

int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
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



void setcursor(bool visible)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = 100;
	lpCursor.bVisible = visible;
	SetConsoleCursorInfo(consoleHandle, &lpCursor);
}



int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}


int main()
{
	Setup();
	while (gameOn && live > 0)
	{
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0)
		{
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i)
			{
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true)
				{
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
					{
						gameOn = false;
					}
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == 0x43)
					{
						color = randrange(1, 15);
					}
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT)
				{
					int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
					{
						color = randrange(1, 15);
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED)
					{
						playerPos = { short(posx),short(posy) };
						playerPos.X -= 3;
					}
				}
			}
			delete[] eventBuffer;
		}

		star_fall();
		clear_buffer();
		for (int i = 0; i < scount; i++)
		{
			draw(starCh, star[i].position);
		}
		draw(playerShip, playerPos, color);
		fill_buffer_to_console();
		Sleep(100);
	}

	return 0;
}

void Setup()
{
	srand(time(NULL));
	setConsole(screen_x, screen_y);
	setMode();
	init_star();
}



