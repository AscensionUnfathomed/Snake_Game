#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cmath>
using namespace std;

bool gameOver;
const int width = 60;
const int height = 25;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int foodCounter = 0;
bool superFood = false;
clock_t startTime, superFoodTime;
bool superFoodActive = false;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPos;

double speedFactor = 1.0;
double baseSpeed = 100;

template<typename T>
double manipulatedSpeedFunction(T x) {
    return baseSpeed - atan(x) * 40;
}

class Direction {
public:
    static const int STOP = 0;
    static const int LEFT = 1;
    static const int RIGHT = 2;
    static const int UP = 3;
    static const int DOWN = 4;
};

int dir;

void SetColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Setup() {
    gameOver = false;
    dir = Direction::STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    foodCounter = 0;
    superFood = false;
    superFoodActive = false;
    startTime = clock();
    speedFactor = 1.0;
    HideCursor();
}

void Draw() {
    cursorPos.X = 0;
    cursorPos.Y = 0;
    SetConsoleCursorPosition(hConsole, cursorPos);
    
    SetColor(14);
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) { SetColor(14); cout << "#"; }
            if (i == y && j == x) { SetColor(10); cout << "O"; }
            else if (i == fruitY && j == fruitX) { 
                if (superFood) {
                    SetColor(13);
                    cout << "O"; // Large O for superfood
                } else {
                    SetColor(12);
                    cout << "o"; // Small o for normal food
                }
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        SetColor(11);
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    SetColor(8);
                    cout << " ";
                }
            }
            if (j == width - 1) { SetColor(14); cout << "#"; }
        }
        cout << endl;
    }
    SetColor(14);
    for (int i = 0; i < width + 2; i++) cout << "#";
    SetColor(7);
    cout << "\nScore: " << score << "\nTime: " << (clock() - startTime) / CLOCKS_PER_SEC << " sec" << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != Direction::RIGHT) dir = Direction::LEFT; break;
            case 'd': if (dir != Direction::LEFT) dir = Direction::RIGHT; break;
            case 'w': if (dir != Direction::DOWN) dir = Direction::UP; break;
            case 's': if (dir != Direction::UP) dir = Direction::DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
        case Direction::LEFT: x--; break;
        case Direction::RIGHT: x++; break;
        case Direction::UP: y--; break;
        case Direction::DOWN: y++; break;
        default: break;
    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += superFood ? 50 : 10;
        foodCounter++;
        if (foodCounter % 5 == 0) {
            superFood = true;
            superFoodActive = true;
            superFoodTime = clock();
            speedFactor /= 2;
        } else {
            superFood = false;
        }
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

    if (superFoodActive && (clock() - superFoodTime) / CLOCKS_PER_SEC >= 5) {
        superFoodActive = false;
        speedFactor *= 2;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(manipulatedSpeedFunction(nTail) * speedFactor);
    }
    SetColor(7);
    cout << "Game Over! Final Score: " << score << endl;
    return 0;
}
