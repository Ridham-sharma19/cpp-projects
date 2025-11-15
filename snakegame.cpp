#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

#define MAX_LENGTH 1000
#define SPEED 80   // lower = faster

// Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth, consoleHeight;

void initScreen() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

struct Point {
    int x, y;
    Point() {}
    Point(int a, int b) : x(a), y(b) {}
};

class Snake {
public:
    Point body[MAX_LENGTH];
    int length;
    char direction;

    Snake(int x, int y) {
        length = 1;
        body[0] = Point(x, y);
        direction = DIR_RIGHT;
    }

    void changeDirection(char newDir) {
        // Prevent opposite direction movement
        if (newDir == DIR_UP && direction != DIR_DOWN) direction = newDir;
        else if (newDir == DIR_DOWN && direction != DIR_UP) direction = newDir;
        else if (newDir == DIR_LEFT && direction != DIR_RIGHT) direction = newDir;
        else if (newDir == DIR_RIGHT && direction != DIR_LEFT) direction = newDir;
    }

    bool move(Point food) {
        // Move tail
        for (int i = length - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        // Move head
        if (direction == DIR_UP) body[0].y--;
        else if (direction == DIR_DOWN) body[0].y++;
        else if (direction == DIR_LEFT) body[0].x--;
        else if (direction == DIR_RIGHT) body[0].x++;

        // Boundary collision
        if (body[0].x < 0 || body[0].x >= consoleWidth ||
            body[0].y < 1 || body[0].y >= consoleHeight)
            return false;

        // Self-collision (start from 1)
        for (int i = 1; i < length; i++) {
            if (body[0].x == body[i].x && body[0].y == body[i].y)
                return false;
        }

        return true;
    }
};

class Board {
public:
    Snake* snake;
    Point food;
    int score;

    Board() {
        snake = new Snake(10, 10);
        score = 0;
        spawnFood();
    }

    ~Board() {
        delete snake;
    }

    void goToXY(int x, int y) {
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    void spawnFood() {
        while (true) {
            int x = rand() % consoleWidth;
            int y = (rand() % (consoleHeight - 2)) + 2; // avoid score row

            bool conflict = false;
            for (int i = 0; i < snake->length; i++) {
                if (snake->body[i].x == x && snake->body[i].y == y)
                    conflict = true;
            }

            if (!conflict) {
                food = Point(x, y);
                break;
            }
        }
    }

    void draw() {
        system("cls");

        // Score
        goToXY(0, 0);
        cout << "Score: " << score << "\n";

        // Snake
        for (int i = 0; i < snake->length; i++) {
            goToXY(snake->body[i].x, snake->body[i].y);
            cout << 'O';
        }

        // Food
        goToXY(food.x, food.y);
        cout << 'o';
    }

    void getInput() {
        if (kbhit()) {
            int key = getch();

            // W A S D
            if (key == 'w' || key == 'W') snake->changeDirection(DIR_UP);
            else if (key == 's' || key == 'S') snake->changeDirection(DIR_DOWN);
            else if (key == 'a' || key == 'A') snake->changeDirection(DIR_LEFT);
            else if (key == 'd' || key == 'D') snake->changeDirection(DIR_RIGHT);

            // Arrow keys
            else if (key == 0 || key == 224) {
                key = getch();
                if (key == 72) snake->changeDirection(DIR_UP);
                else if (key == 80) snake->changeDirection(DIR_DOWN);
                else if (key == 75) snake->changeDirection(DIR_LEFT);
                else if (key == 77) snake->changeDirection(DIR_RIGHT);
            }
        }
    }

    bool update() {
        bool ok = snake->move(food);
        if (!ok) return false;

        // Snake eats food
        if (snake->body[0].x == food.x && snake->body[0].y == food.y) {
            snake->body[snake->length] = snake->body[snake->length - 1];
            snake->length++;
            score++;
            spawnFood();
        }

        return true;
    }
};

int main() {
    srand(time(0));
    initScreen();

    Board* board = new Board();

    while (board->update()) {
        board->getInput();
        board->draw();
        Sleep(SPEED);
    }

    system("cls");
    cout << "\n\nGAME OVER!\nFinal Score: " << board->score << "\n";

    return 0;
}
