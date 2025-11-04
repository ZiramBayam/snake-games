#include <iostream>
#include <conio.h>
#include <windows.h>
#include <deque>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point {
    int x;
    int y;
};

enum Direction { UP, DOWN, LEFT, RIGHT };

static const int WIDTH = 40;
static const int HEIGHT = 20;

void hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 25;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
}

void setCursorPosition(short x, short y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x, y };
    SetConsoleCursorPosition(hOut, pos);
}

void drawBorder() {
    setCursorPosition(0, 0);
    for (int i = 0; i <= WIDTH + 1; ++i) cout << '#';
    for (int y = 1; y <= HEIGHT; ++y) {
        setCursorPosition(0, y);
        cout << '#';
        setCursorPosition(WIDTH + 1, y);
        cout << '#';
    }
    setCursorPosition(0, HEIGHT + 1);
    for (int i = 0; i <= WIDTH + 1; ++i) cout << '#';
}

bool contains(const deque<Point>& body, const Point& p) {
    for (const auto& s : body) if (s.x == p.x && s.y == p.y) return true;
    return false;
}

Point randomEmptyCell(const deque<Point>& snake) {
    Point p;
    do {
        p.x = rand() % WIDTH;
        p.y = rand() % HEIGHT;
    } while (contains(snake, p));
    return p;
}

void drawCell(const Point& p, char ch) {
    setCursorPosition(p.x + 1, p.y + 1); // +1 to account for border
    cout << ch;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    hideCursor();

    // Initialize snake in the center
    deque<Point> snake;
    Point start = { WIDTH / 2, HEIGHT / 2 };
    snake.push_back(start);
    snake.push_back({ start.x - 1, start.y });
    snake.push_back({ start.x - 2, start.y });

    Direction dir = RIGHT;
    bool gameOver = false;

    drawBorder();

    // Initial draw
    for (const auto& s : snake) drawCell(s, 'o');
    drawCell(snake.front(), 'O');

    Point food = randomEmptyCell(snake);
    drawCell(food, '*');

    int score = 0;
    setCursorPosition(0, HEIGHT + 2);
    cout << "Score: " << score << "    ";

    int tickMs = 120; // initial speed

    while (!gameOver) {
        // Input (non-blocking)
        if (_kbhit()) {
            int ch = _getch();
            // Arrow keys come as two codes (224 then code)
            if (ch == 224) {
                int arrow = _getch();
                if (arrow == 72 && dir != DOWN) dir = UP;        // Up
                else if (arrow == 80 && dir != UP) dir = DOWN;   // Down
                else if (arrow == 75 && dir != RIGHT) dir = LEFT;// Left
                else if (arrow == 77 && dir != LEFT) dir = RIGHT;// Right
            } else {
                // WASD fallback
                if ((ch == 'w' || ch == 'W') && dir != DOWN) dir = UP;
                else if ((ch == 's' || ch == 'S') && dir != UP) dir = DOWN;
                else if ((ch == 'a' || ch == 'A') && dir != RIGHT) dir = LEFT;
                else if ((ch == 'd' || ch == 'D') && dir != LEFT) dir = RIGHT;
                else if (ch == 27) { // ESC to quit
                    gameOver = true;
                }
            }
        }

        // Compute next head
        Point head = snake.front();
        Point next = head;
        if (dir == UP) next.y -= 1;
        else if (dir == DOWN) next.y += 1;
        else if (dir == LEFT) next.x -= 1;
        else if (dir == RIGHT) next.x += 1;

        // Check wall collision
        if (next.x < 0 || next.x >= WIDTH || next.y < 0 || next.y >= HEIGHT) {
            gameOver = true;
        }
        // Check self collision
        else if (contains(snake, next)) {
            gameOver = true;
        }

        if (gameOver) break;

        // Move: add head
        snake.push_front(next);
        drawCell(next, 'O');
        // Redraw old head as body
        drawCell(head, 'o');

        // Eat or move tail
        if (next.x == food.x && next.y == food.y) {
            score += 10;
            if (tickMs > 50) tickMs -= 2; // speed up slightly
            setCursorPosition(0, HEIGHT + 2);
            cout << "Score: " << score << "    ";
            // Place new food
            food = randomEmptyCell(snake);
            drawCell(food, '*');
        } else {
            // Erase tail on screen
            Point tail = snake.back();
            snake.pop_back();
            drawCell(tail, ' ');
        }

        Sleep(tickMs);
    }

    // Game over
    setCursorPosition(0, HEIGHT + 3);
    cout << "Game Over! Final Score: " << score << "        \n";
    cout << "Press any key to exit...";
    _getch();

    return 0;
}
