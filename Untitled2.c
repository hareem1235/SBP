#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define row 20
#define coloumn 20

int snakeX[100], snakeY[100];
int snakeLength = 1;
char direction;
int score = 0;
int fruitx, fruity;

void generate_fruit() {
    fruitx = rand() % (row - 2) + 1;
    fruity = rand() % (coloumn - 2) + 1;
}

void setup() {
    snakeLength = 1;
    score = 0;

    snakeX[0] = row / 2;
    snakeY[0] = coloumn / 2;

    generate_fruit();
}

void draw_boundary_with_fruit() {
    system("cls");
    for (int i = 0; i < row*2+3; i++) {
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < coloumn; i++) {
        printf("|");
        for (int j = 0; j < coloumn; j++) {
            if (i == fruitx && j == fruity)
                printf("F ");
            else {
                int isSnakeSegment = 0;
                for (int k = 0; k < snakeLength; k++) {
                    if (snakeX[k] == i && snakeY[k] == j) {
                        printf("O ");
                        isSnakeSegment = 1;
                        break;
                    }
                }
                if (!isSnakeSegment)
                    printf("  ");
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < row*2+3; i++) {
        printf("-");
    }
    printf("\n");

    printf("Score: %d\n", score);
    printf("Press 'X' to quit the game\n");
}

void snake_movement() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'w':
            case 'W':
                if (direction != 'd')
                    direction = 'u';
                break;
            case 'a':
            case 'A':
                if (direction != 'r')
                    direction = 'l';
                break;
            case 's':
            case 'S':
                if (direction != 'u')
                    direction = 'd';
                break;
            case 'd':
            case 'D':
                if (direction != 'l')
                    direction = 'r';
                break;
            case 'x':
            case 'X':
                exit(0);
        }
    }

    for (int i = snakeLength; i > 0; --i) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    switch (direction) {
        case 'u':
            snakeX[0]--;
            break;
        case 'd':
            snakeX[0]++;
            break;
        case 'l':
            snakeY[0]--;
            break;
        case 'r':
            snakeY[0]++;
            break;
    }
}

void snake_body() {
    if (snakeX[0] == fruitx && snakeY[0] == fruity) {
        snakeLength++;
        score += 10;
        generate_fruit();
    }
}

int isGameOver() {
    if (snakeX[0] <= 0 || snakeX[0] >= row - 1 || snakeY[0] <= 0 || snakeY[0] >= coloumn - 1) {
        return 1;
    }
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[i] == snakeX[0] && snakeY[i] == snakeY[0]) {
            return 1;
        }
    }
    return 0;
}

void gameOver() {
    printf("Game Over!\n");
    printf("Final Score: %d\n", score);
    exit(0);
}

int main() {
    srand(time(NULL));
    setup();

    while (1) {
        draw_boundary_with_fruit();
        snake_movement();
        snake_body();
        if (isGameOver()) {
            gameOver();
        }
        Sleep(100);
    }

    return 0;
}

