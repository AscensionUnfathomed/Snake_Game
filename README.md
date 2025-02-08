
# Snake Game

A simple Snake game implemented in C++ using the console interface. The game features a moving snake that grows when it eats food, and the player controls the snake using keyboard inputs.

## Features
- Classic Snake game logic.
- Continuous movement with real-time input.
- Game over on self-collision and boundary collision.
- Score tracking and game duration display.
- Console cursor hiding for smooth display updates.

## How to Play
- Use `W`, `A`, `S`, `D` keys to move Up, Left, Down, and Right, respectively.
- Press `X` to exit the game.
- The goal is to collect food (`o`) and super food (`O`) to grow the snake and increase the score.
- Avoid colliding with the snake's own body to prevent game over.

## Requirements
- A C++ compiler (e.g., g++ or MSVC).
- Windows OS (due to Windows-specific headers like `conio.h` and `windows.h`).

## Compilation and Execution

### Using g++
```sh
 g++ snake_game.cpp -o snake_game.exe
 ./snake_game.exe
```
### Using MSVC
```sh
 cl snake_game.cpp
 snake_game.exe
```

## Code Structure
- **Setup()**: Initializes the game, places the snake and food, and hides the console cursor.
- **Draw()**: Updates the console display with the game state.
- **Input()**: Captures user input for snake movement.
- **Logic()**: Handles movement, food consumption, collision detection, and game over conditions.
- **Main loop**: Continuously calls `Draw()`, `Input()`, and `Logic()` while the game is running.

## Data Structure Analysis
### Arrays
- `tailX[100]`, `tailY[100]`: Used to store the snake's tail coordinates.

### Enum
- `enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };`: Represents the possible movement directions of the snake.

### Variables
- `int x, y`: Stores the snake's head position.
- `int fruitX, fruitY`: Stores the food's position.
- `int score`: Keeps track of the player's score.
- `int nTail`: Stores the current length of the snake's tail.
- `bool gameOver`: Controls the main game loop.
- `clock_t startTime`: Tracks the game duration.

## Speed Variation
The speed of the snake is controlled using the `Sleep(120);` function inside the game loop. The value `120` represents the delay in milliseconds before the next update cycle. As the game progresses, the speed remains constant unless modified manually.

### Super Food Effect
The provided code does not include a "super food" mechanism, but if added, consuming it could temporarily increase the snake's speed by reducing the sleep duration (e.g., `Sleep(80);`). However, currently, the snake moves at a constant speed throughout the game.

## Future Improvements
- Adding different difficulty levels with increasing speed.
- Implementing a high-score tracking system.
- Improving graphics with a better UI.
- Adding a game menu for better user interaction.

## Created By
Team - Code Slayers    

Members:
1) Neel Khatri - 202401093
2) Kavya Bhojwani - 202401090
3) Kavish Inani - 202401089
4) Manal Patel - 202401112  




