#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include <sys/time.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#include "timer.h"
#include "keyboard.h"

// Constantes do jogo
#define MAX_SNAKE_SIZE 100
#define INITIAL_SNAKE_SIZE 5
#define INITIAL_DELAY 150000
#define MINX 1
#define MINY 1


// Estrutura que representa a cobra
typedef struct {
    int x[MAX_SNAKE_SIZE];
    int y[MAX_SNAKE_SIZE];
    int size;
} Snake;

// Funções do jogo
void initializeSnake(Snake *snake);
void drawSnake(Snake *snake);
void moveSnake(Snake *snake, char direction);
int checkCollision(Snake *snake);
void generateFood(int *foodX, int *foodY);
void drawFood(int foodX, int foodY);

int main() {
    // Inicialização das bibliotecas
    screenInit(1);
    keyboardInit();
    timerInit(INITIAL_DELAY);

    // Inicialização do jogo
    Snake snake;
    initializeSnake(&snake);
    char direction = 'd';
    int foodX, foodY;
    generateFood(&foodX, &foodY);

    while (1) {
        // Verifica se uma tecla foi pressionada
        if (keyhit()) {
            char key = readch();
            if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
                direction = key;
            }
        }

        // Move a cobra
        moveSnake(&snake, direction);

        // Verifica colisão
        if (checkCollision(&snake)) {
            screenDestroy();
            printf("Game Over! Pontuação: %d\n", snake.size - INITIAL_SNAKE_SIZE);
            break;
        }

        // Verifica se a cobra comeu a comida
        if (snake.x[0] == foodX && snake.y[0] == foodY) {
            snake.size++;
            generateFood(&foodX, &foodY);
        }

        // Desenha a cobra e a comida
        screenClear();
        drawSnake(&snake);
        drawFood(foodX, foodY);
        screenUpdate();

        // Verifica o tempo para controlar a velocidade da cobra
        if (timerTimeOver()) {
            usleep(INITIAL_DELAY);
            timerUpdateTimer(INITIAL_DELAY);
        }
    }

    // Finalização das bibliotecas
    keyboardDestroy();
    timerDestroy();

    return 0;
}

void initializeSnake(Snake *snake) {
    snake->size = INITIAL_SNAKE_SIZE;
    for (int i = 0; i < snake->size; i++) {
        snake->x[i] = MAXX / 2 - i;
        snake->y[i] = MAXY / 2;
    }
}

void drawSnake(Snake *snake) {
    for (int i = 0; i < snake->size; i++) {
        screenGotoxy(snake->x[i], snake->y[i]);
        printf("*");
    }
}

void moveSnake(Snake *snake, char direction) {
    // Move a cabeça
    for (int i = snake->size - 1; i > 0; i--) {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
    }

    // Move a cabeça na direção desejada
    if (direction == 'w') {
        snake->y[0]--;
    } else if (direction == 'a') {
        snake->x[0]--;
    } else if (direction == 's') {
        snake->y[0]++;
    } else if (direction == 'd') {
        snake->x[0]++;
    }
}

int checkCollision(Snake *snake) {
    // Verifica colisão com as paredes
    if (snake->x[0] <= MINX || snake->x[0] >= MAXX || snake->y[0] <= MINY || snake->y[0] >= MAXY) {
        return 1;
    }

    // Verifica colisão consigo mesma
    for (int i = 1; i < snake->size; i++) {
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i]) {
            return 1;
        }
    }

    return 0;
}

void generateFood(int *foodX, int *foodY) {
    // Gera coordenadas aleatórias para a comida
    srand(time(NULL));
    *foodX = rand() % (MAXX - MINX) + MINX;
    *foodY = rand() % (MAXY - MINY) + MINY;
}

void drawFood(int foodX, int foodY) {
    screenGotoxy(foodX, foodY);
    printf("#");
}