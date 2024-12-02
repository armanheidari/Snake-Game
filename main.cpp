#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

#define WIDTH 50
#define HEIGHT 25
#define MAX_SNAKE_LENGTH 100
#define H_INDENT "\t\t\t"
#define V_INDENT "\n\n\n"

#define STOP 0
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

bool gameOver;
int foodX, foodY;
int snakeX[MAX_SNAKE_LENGTH], snakeY[MAX_SNAKE_LENGTH];
int snakeLength;
int direction;
int score;

void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
        cout << " ";
}

void setCursorVisibility(bool visible)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void setupGame()
{
    setCursorVisibility(false);
    system("cls");

    gameOver = false;
    direction = STOP;
    score = 0;

    snakeLength = 1;
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;

    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
        case 75: // Left arrow
            if (direction != RIGHT)
                direction = LEFT;
            break;

        case 'd':
        case 77:
            if (direction != LEFT)
                direction = RIGHT;
            break;

        case 'w':
        case 72:
            if (direction != DOWN)
                direction = UP;
            break;

        case 's':
        case 80:
            if (direction != UP)
                direction = DOWN;
            break;

        case 'x':
        case 27: // ESC key
            gameOver = true;
            break;
        }
    }
}

int main()
{
    return 0;
}