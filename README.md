# 🏎️ Car Racing Game (C++ Console)

A real-time, console-based lane-switching racing game written in **C++** using **Object-Oriented Programming**. Dodge falling obstacles and enemy vehicles, survive as long as you can, and watch the game get faster as your score grows.

> Final project for the Object-Oriented Programming course at UET Taxila.

---

## 📖 Overview

You control a car at the bottom of a 10-lane road. Obstacles (`O`) and enemy vehicles (`X`) fall from the top of the screen. Move left or right to avoid them. Every second you survive adds to your score, and as your score increases, the level goes up and the game speeds up.

```
. . . . . . . . . .
. . O . . . . . . .
. . . . . X . . . .
. . . . . . . . . .
. . . . . . . O . .
. . C . . . . . . .

Score: 42
Level: 1
Speed: 180
Lives: 2
```

| Symbol | Meaning |
| :----: | ------- |
| `C` | Your car |
| `O` | Obstacle |
| `X` | Enemy vehicle |
| `.` | Empty road |

---

## ✨ Features

- Real-time, non-blocking keyboard input
- 10-lane road with falling obstacles and enemy vehicles
- Level-based difficulty: the game speeds up as your score increases
- Time-based scoring: points per second scale with your current level
- Lives system with a continue / quit prompt after each crash
- Clean OOP design with separate classes for each game entity

---

## 🎮 Controls

| Key | Action |
| :-: | ------ |
| `A` | Move left |
| `D` | Move right |
| `Y` / `N` | Continue or quit after a crash |

> **Note:** Use lowercase `a` and `d` (make sure Caps Lock is off).

---

## 🕹️ How to Play

1. Start the game. You begin with **2 lives** at **Level 1**.
2. Move left and right to avoid `O` and `X` as they fall toward you.
3. Your score increases every second, and the amount you earn per second equals your current level.
4. Every **50 points** you move up a level, and the game gets faster.
5. If you crash, you lose a life. If you still have lives left, you can choose to continue (`Y`) or quit (`N`).
6. When you run out of lives, the game ends and your final score is shown.

---

## ⚙️ Game Mechanics

| Mechanic | Rule |
| -------- | ---- |
| Road size | 10 lanes × 20 rows |
| Starting lives | 2 |
| Level | `level = (score / 50) + 1` |
| Frame delay (speed) | `speed = 200 - (level × 20)` ms, never lower than `50` ms |
| Score | `+ level` points every second |
| Collision | Happens when an obstacle or enemy reaches the player's row in the same lane |
| Spawn rate | Obstacles spawn about 1 in 5 frames, enemies about 1 in 7 frames |

> A **lower** speed value means a **shorter** delay between frames, so the game runs **faster**.

---

## 🧱 Project Structure and OOP Design

The game is built around four classes:

| Class | Responsibility |
| ----- | -------------- |
| `Car` | Represents the player. Keeps its lane and row **private** (encapsulation) and exposes `move()`, `reset()`, `getLane()` and `getRow()`. |
| `Obstacle` | A hazard that spawns at the top of a random lane and moves down one row per frame. |
| `Enemy` | A second type of hazard with the same movement behavior as an obstacle. |
| `Game` | The controller class. Owns the car, obstacles and enemies, and runs the game loop: **input → update → draw**. Handles collisions, scoring, levels and lives. |

**OOP concepts demonstrated:** classes and objects, encapsulation, constructors, and composition (`Game` contains `Car`, `vector<Obstacle>` and `vector<Enemy>`).

### Game Loop

```
while (true) {
    input();     // read A / D keys without blocking
    update();    // move objects, check collisions, update score, spawn new hazards
    draw();      // render the grid to the console
    Sleep(speed);
}
```

---

## 🛠️ Requirements

- **Operating system:** Windows (the game uses `<conio.h>` and `<windows.h>`)
- **Compiler:** Visual Studio (MSVC), or MinGW / g++ with C++11 or later

---

## 🚀 Getting Started

### Clone the repository

```bash
git clone https://github.com/<your-username>/<your-repo-name>.git
cd <your-repo-name>
```

### Option 1: Visual Studio

1. Open Visual Studio and create a new **Console App** project (or open the existing one).
2. Add `Car_Racing_Game.cpp` to the project.
3. Press **Ctrl + F5** to build and run.

### Option 2: MinGW / g++ (command line)

```bash
g++ Car_Racing_Game.cpp -o CarRacingGame.exe
CarRacingGame.exe
```

---

## 🔧 Possible Improvements

- Main menu and a high-score table saved to a file
- Better graphics using colors or ASCII car art
- Different power-ups (extra life, slow motion, shield)
- Support for arrow keys and uppercase `A` / `D`
- Smoother rendering (cursor repositioning instead of `system("cls")` to reduce flicker)
- Cross-platform support (replace `conio.h` / `windows.h`)

---

## 📄 Documentation

A full project report covering the design, class structure, implementation details, challenges and testing is included in this repository: `Car_Racing_Game_Final_Project_Report.docx`.

---

## 👤 Author

Muneeb Ur Rehman Sidhar

Computer Science, University of Engineering and Technology (UET), Taxila

---


