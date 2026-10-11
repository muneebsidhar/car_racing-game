#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <vector>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;

// ---------------- CAR ----------------
class Car {
private:
    int lane;
    int row;

public:
    Car() {
        lane = 2;
        row = HEIGHT - 1;
    }

    void move(char input) {
        if (input == 'a' && lane > 0) lane--;
        if (input == 'd' && lane < WIDTH - 1) lane++;
    }

    void reset() {
        lane = 2;
        row = HEIGHT - 1;
    }

    int getLane() { return lane; }
    int getRow() { return row; }
};

// ---------------- OBSTACLE ----------------
class Obstacle {
public:
    int lane;
    int row;

    Obstacle(int l) {
        lane = l;
        row = 0;
    }

    void move() {
        row++;
    }
};

// ---------------- ENEMY ----------------
class Enemy {
public:
    int lane;
    int row;

    Enemy(int l) {
        lane = l;
        row = 0;
    }

    void move() {
        row++;
    }
};

// ---------------- GAME ----------------
class Game {
private:
    Car car;
    vector<Obstacle> obstacles;
    vector<Enemy> enemies;

    int score;
    int level;
    int lives;
    int speed;   // ? NEW IMPORTANT VARIABLE

    time_t lastTick;

public:
    Game() {
        score = 0;
        level = 1;
        lives = 2;

        speed = 200; // start slow

        srand(time(0));
        lastTick = time(0);
    }

    void updateLevel() {
        level = (score / 50) + 1;

        // ? SPEED FIX (IMPORTANT PART)
        speed = 200 - (level * 20);

        if (speed < 50)
            speed = 50; // minimum limit (very fast but playable)
    }

    void updateScore() {
        time_t now = time(0);

        if (now != lastTick) {
            updateLevel();
            score += level;   // level-based scoring
            lastTick = now;
        }
    }

    void spawnObstacle() {
        obstacles.push_back(Obstacle(rand() % WIDTH));
    }

    void spawnEnemy() {
        enemies.push_back(Enemy(rand() % WIDTH));
    }

    bool askContinue() {
        char choice;
        cout << "\n?? You lost a life! Continue? (Y/N): ";
        cin >> choice;
        return (choice == 'Y' || choice == 'y');
    }

    void handleCrash() {
        lives--;

        system("cls");
        cout << "?? CRASH! Lives left: " << lives << endl;

        if (lives > 0) {
            if (askContinue()) {
                car.reset();
                obstacles.clear();
                enemies.clear();
            } else {
                cout << "Game Over! Final Score: " << score << endl;
                exit(0);
            }
        } else {
            cout << "?? No lives left!" << endl;
            cout << "Final Score: " << score << endl;
            exit(0);
        }
    }

    void checkCollision() {
        for (auto &o : obstacles) {
            if (o.row == HEIGHT - 1 && o.lane == car.getLane()) {
                handleCrash();
                return;
            }
        }

        for (auto &e : enemies) {
            if (e.row == HEIGHT - 1 && e.lane == car.getLane()) {
                handleCrash();
                return;
            }
        }
    }

    void input() {
        if (_kbhit()) {
            char ch = _getch();
            car.move(ch);
        }
    }

    void update() {
        for (auto &o : obstacles)
            o.move();

        for (auto &e : enemies)
            e.move();

        checkCollision();
        updateScore();

        if (rand() % 5 == 0)
            spawnObstacle();

        if (rand() % 7 == 0)
            spawnEnemy();
    }

    void draw() {
        system("cls");

        char grid[HEIGHT][WIDTH];

        for (int i = 0; i < HEIGHT; i++)
            for (int j = 0; j < WIDTH; j++)
                grid[i][j] = '.';

        grid[car.getRow()][car.getLane()] = 'C';

        for (auto &o : obstacles)
            if (o.row < HEIGHT)
                grid[o.row][o.lane] = 'O';

        for (auto &e : enemies)
            if (e.row < HEIGHT)
                grid[e.row][e.lane] = 'X';

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nScore: " << score << endl;
        cout << "Level: " << level << endl;
        cout << "Speed: " << speed << endl;
        cout << "Lives: " << lives << endl;
    }

    void run() {
        while (true) {
            input();
            update();
            draw();

            // ? FIXED SPEED SYSTEM
            Sleep(speed);
        }
    }
};

// ---------------- MAIN ----------------
int main() {
    Game game;
    game.run();
    return 0;
}