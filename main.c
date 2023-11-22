#include <string.h>
#include<stdlib.h> // Para função srand() e system()
#include<time.h> // Para função rand()

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;
int incX = 1, incY = 1;

// Variáveis Globais
int c[300][2], pontos=1, cx=2, cy=2;
int comida[2], velo=150;

/**void printHello(int nextX, int nextY)
{
    // Define a cor do texto como ciano e o fundo como cinza escuro
    screenSetColor(CYAN, DARKGRAY);
    
    // Move o cursor para as coordenadas (x, y) e limpa a área de impressão
    screenGotoxy(x, y);
    printf("           ");
    
    // Atualiza as novas coordenadas
    x = nextX;
    y = nextY;
    
    // Move o cursor para as novas coordenadas e imprime "Hello World"
    screenGotoxy(x, y);
    printf("Hello World");
}
*/

void desenha(){ // Desenha a cobrinha
    screenSetColor(CYAN, DARKGRAY);
    int i;
    for(i=0; i<pontos; i++){
        screenGotoxy(c[i][0],c[i][1]);
        printf("%c",219);
    }
}

void atualiza(){ // Atualiza a posição da cobrinha
    int i;
    screenGotoxy(c[pontos][0],c[pontos][1]);
    printf(" ");
    for(i=pontos; i>=0; i--){
        c[i+1][0] = c[i][0];
        c[i+1][1] = c[i][1];
    }
}

int analiza(){ // Vê se a cobrinha enconstou em seu próprio corpo
    int i, retorno=0;
    for(i=1; i<pontos; i++){
        if(cx==c[i][0] && cy==c[i][1]){
            retorno=1;
        }
    }
    return retorno;
}

void geraComida(){ // Gera comida em local aleatório
    screenGotoxy(comida[0],comida[1]);
    printf("*");
    srand(time(NULL));
    comida[0] = (rand() % 48) +1;
    comida[1] = (rand() % 18) +1;
    screenGotoxy(comida[0],comida[1]);
    printf("%c",4);
}


void printKey(int ch)
{
    // Define a cor do texto como amarelo e o fundo como cinza escuro
    screenSetColor(YELLOW, DARKGRAY);
    
    // Posiciona o cursor para imprimir o texto "Key code:"
    screenGotoxy(35, 22);
    printf("Key code :");

    // Posiciona o cursor para limpar a linha onde será exibido o código da ch
    screenGotoxy(34, 23);
    printf("            ");
    
    // Posiciona o cursor com base no valor da ch e imprime o código da ch
    if (ch == 27)
        screenGotoxy(36, 23);
    else
        screenGotoxy(39, 23);

    printf("%d ", ch);
    
    // Aguarda e imprime outros códigos de ch enquanto houver chs pressionadas
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

int main() 
{
    static int ch = 0;
    int gameover = 0;
    int tecla = 0;
    

    // Inicializa a tela com bordas
    screenInit(1);
    
    // Inicializa o chdo e o temporizador
    keyboardInit();
    timerInit(50);

    // Atualiza a tela
    screenUpdate();

    while (ch != 10) // Enter
    {
        // Manipula a entrada do usuário
        if (keyhit()) 
        {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        // Atualiza o estado do jogo (move elementos, verifica colisões, etc)

            geraComida(); // Gera a primeira comida
            desenha(); // Desenha a cobra
            tecla='d';

            while(gameover == 0){
                screenGotoxy(52,2);
                printf("Pontos: %d\t",pontos);
                screenGotoxy(52,4); 
                printf("Velocidade: %.2d caracteres/s",1000/velo);

                c[0][0]=cx;
                c[0][1]=cy;
                
if(tecla=='w' || tecla=='W' || tecla==72){
            cy--;
            if(cy==0) break; // Se a cabeça da cobra estiver na parede superior,
        }                    // O jogo acaba
        if(tecla=='a' || tecla=='A' || tecla==75){
            cx--;
            if(cx==0) break; // Se a cabeça da cobra estiver na parede da esquerda,
        }                    // O Jogo acaba
        if(tecla=='s' || tecla=='S' || tecla==80){
            cy++;
            if(cy==20) break; // Se a cabeça da cobra estiver na parede de baixo,
        }                     // O jogo acaba
        if(tecla=='d' || tecla=='D' || tecla==77){
            cx++;
            if(cx>=50) break; // Se a a cabeça da cobra estiver na parede da direida,
        }                     // O jogo acaba
                if(cx==comida[0] && cy==comida[1]){ // Se a cobra comer a comida
                    pontos++;
                    if(velo>50) velo-=10; // Velocidade em milissegundos abaixa
                    geraComida();
                }


            

                gameover=analiza();
                atualiza(); // Atualiza a cobra
                desenha(); // Desenha a cobra
                screenGotoxy(50,20);

            // Imprime o código da ch em novas coordenadas
            printKey(ch);
            screenUpdate();
            }

            // Atualiza a tela
            screenUpdate();

        
    }

    // Libera recursos do chdo, tela e temporizador
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}