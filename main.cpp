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

void draw()
{
    //> 0. Move Cursor to top-left
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    //> 1. Top Border
    cout << V_INDENT << H_INDENT;
    for (int i = 0; i < WIDTH + 2; i++)
        cout << char(220); // ▄
    cout << endl;

    //> 2. Game Area
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            //? 2.1. Left Border
            if (x == 0)
                cout << H_INDENT << char(219); // █

            bool printed = false;

            //? 2.2. Snake
            for (int k = 0; k < snakeLength; k++)
            {
                if (snakeX[k] == x && snakeY[k] == y)
                {
                    if (k == 0)
                        cout << "O"; //. Head
                    else
                        cout << char(254); //. Body - ■
                    printed = true;
                    break;
                }
            }

            //? 2.3. Food
            if (not printed and foodX == x and foodY == y)
            {
                cout << "*";
                printed = true;
            }

            //? 2.5. Empty Space
            if (not printed)
                cout << " ";

            //? 2.6. Right Border
            if (x == WIDTH - 1)
                cout << char(219) << endl; // █
        }
    }

    //> 3. Bottom Border
    cout << H_INDENT;
    for (int i = 0; i < WIDTH + 2; i++)
        cout << char(223); // ▀
    cout << V_INDENT << endl;

    //> 4. Score
    cout << H_INDENT;
    printSpaces(WIDTH / 2 - 3);
    cout << "Score: " << score << endl;
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

void gameLogic()
{
    //> 1. Track Position
    int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prev2X, prev2Y;

    //> 2. Move Snake
    //? 2.1. Head
    switch (direction)
    {
    case LEFT:
        snakeX[0]--;
        break;
    case RIGHT:
        snakeX[0]++;
        break;
    case UP:
        snakeY[0]--;
        break;
    case DOWN:
        snakeY[0]++;
        break;
    }

    //? 2.2. Body
    for (int i = 1; i < snakeLength; i++)
    {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];

        snakeX[i] = prevX;
        snakeY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    //> 3. Check Collisions
    //? 3.1. Wall
    if (snakeX[0] >= WIDTH or snakeX[0] < 0 or snakeY[0] >= HEIGHT or snakeY[0] < 0)
        gameOver = true;

    //? 3.2. Self
    for (int i = 1; i < snakeLength; i++)
        if (snakeX[0] == snakeX[i] and snakeY[0] == snakeY[i])
            gameOver = true;

    //? 3.3. Food
    if (snakeX[0] == foodX and snakeY[0] == foodY)
    {
        score += 10;
        snakeLength++;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    }
}

int main()
{
    setupGame();
    while (not gameOver)
    {
        draw();
        input();
        gameLogic();
        Sleep(50);
    }
    setCursorVisibility(true);
    return 0;
}