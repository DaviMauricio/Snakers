#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// Variáveis Globais
int c[300][2] = {0};
int pontos = 1, cx = 2, cy = 2;
int comida[2] = {0}, velo = 150;

// FUNÇÕES
void gotoxy(int x, int y) {
    printf("\e[%d;%dH", y, x);
}

void desenha() {
    int i;
    for (i = 0; i < pontos; i++) {
        gotoxy(c[i][0], c[i][1]);
        printf("%c", 219);
    }
}

void atualiza() {
    int i;
    gotoxy(c[pontos][0], c[pontos][1]);
    printf(" ");
    for (i = pontos; i >= 0; i--) {
        c[i + 1][0] = c[i][0];
        c[i + 1][1] = c[i][1];
    }
}

int analiza() {
    int i, retorno = 0;
    for (i = 1; i < pontos; i++) {
        if (cx == c[i][0] && cy == c[i][1]) {
            retorno = 1;
        }
    }
    return retorno;
}

void geraComida() {
    gotoxy(comida[0], comida[1]);
    printf(" ");
    srand(time(NULL));
    do {
        comida[0] = (rand() % 48) + 1;
        comida[1] = (rand() % 18) + 1;
    } while (comida[0] == cx && comida[1] == cy);
    gotoxy(comida[0], comida[1]);
    printf("*");
}

// Função para obter entrada de teclado sem bloquear
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int main() {
    int i, gameover = 0;
    int tecla;

    printf("\e[2J\e[H");

    for (i = 0; i < 50; i++) { // Linha superior
        gotoxy(i, 0);
        printf("%c", 219);
        usleep(5000); // Pausa execução por 5 milissegundos
    }
    for (i = 0; i < 20; i++) { // Coluna da direita
        gotoxy(50, i);
        printf("%c", 219);
        usleep(5000);
    }
    for (i = 50; i >= 0; i--) { // Linha inferior
        gotoxy(i, 20);
        printf("%c", 219);
        usleep(5000);
    }
    for (i = 20; i > 0; i--) { // Coluna da esquerda
        gotoxy(0, i);
        printf("%c", 219);
        usleep(5000);
    }
    geraComida();
    desenha();
    tecla = 'd';

    while (gameover == 0) {
        gotoxy(52, 2);
        printf("Pontos: %d\t", pontos);
        gotoxy(52, 4);
        printf("Velocidade: %.2f caracteres/s", 1000.0 / velo);
        c[0][0] = cx;
        c[0][1] = cy;

        if (kbhit()) {
            tecla = getchar();
        }

        if (tecla == 'w' || tecla == 'W' || tecla == 72) {
            cy--;
            if (cy == 0) break;
        }
        if (tecla == 'a' || tecla == 'A' || tecla == 75) {
            cx--;
            if (cx == 0) break;
        }
        if (tecla == 's' || tecla == 'S' || tecla == 80) {
            cy++;
            if (cy == 20) break;
        }
        if (tecla == 'd' || tecla == 'D' || tecla == 77) {
            cx++;
            if (cx >= 50) break;
        }

        if (cx == comida[0] && cy == comida[1]) {
            pontos++;
            if (velo > 50) velo -= 10;
            geraComida();
        }
        gameover = analiza();
        atualiza();
        desenha();
        usleep(velo * 1000);
    }

    printf("Você perdeu! Fez %d pontos.\n", pontos);
    printf("Pressione Enter para sair...");
    getchar(); // Espera o usuário pressionar Enter antes de sair
    return 0;
}
