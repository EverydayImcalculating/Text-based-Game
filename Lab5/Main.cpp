#include <iostream>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
    gotoxy(x, y);
    std::cout << "  <'-(0)-'>  ";
}

void setcursor(bool visible)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.dwSize = 100;
    lpCursor.bVisible = visible;
    SetConsoleCursorInfo(consoleHandle, &lpCursor);
}

void erase_ship()
{
    system("cls");
}

//void setcolor(int fg, int bg)
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
//}

int main(void)
{
    char ch = ' ';
    int x = 50, y = 15; // Screensize 120x30.
    //setcolor(5, 8);
    draw_ship(x, y);
    do {
        setcursor(0);
        if (_kbhit()) {
            ch = _getch();
            if (ch == 'a')
            {
                if (x > 0)
                    draw_ship(--x, y);
            }
            if (ch == 'd')
            {
                if (x < 107)
                {
                    draw_ship(++x, y);
                }
            }
            if (ch == 'w')
            {
                if (y > 0)
                {
                    erase_ship();
                    draw_ship(x, --y);
                }
            }
            if (ch == 's')
            {
                if (y < 29)
                {
                    erase_ship();
                    draw_ship(x, ++y);
                }
            }
            fflush(stdin);
        }
        Sleep(100);
    } while (ch != 'x');

    return 0;
}