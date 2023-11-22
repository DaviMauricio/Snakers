/**
 * screen.h
 * Criado em 23 de agosto de 2023
 * Autor: Tiago Barros
 * Baseado no curso "De C para C++ - 2002"
 * Referência: https://en.wikipedia.org/wiki/ANSI_escape_code
 */

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>

// Sequências de controle do terminal
#define ESC            "\033"
#define NORMALTEXT     "[0m"
#define BOLDTEXT       "[1m"
#define ITALICTEXT     "[3m"
#define BLINKTEXT      "[5m"
#define REVERSETEXT    "[7m"
#define HOMECURSOR     "[f"
#define SHOWCURSOR     "[?25h"
#define HIDECURSOR     "[?25l"
#define CLEARSCREEN    "[2J"

// Desenhos de caixa - Terminais semelhantes ao Unix
#define BOX_ENABLE     "(0"
#define BOX_DISABLE    "(B"
#define BOX_VLINE      0x78
#define BOX_HLINE      0x71
#define BOX_UPLEFT     0x6C
#define BOX_UPRIGHT    0x6B
#define BOX_DWNLEFT    0x6D
#define BOX_DWNRIGHT   0x6A
#define BOX_CROSS      0x6E
#define BOX_TLEFT      0X74
#define BOX_TRIGHT     0X75
#define BOX_TUP        0X77
#define BOX_TDOWN      0X76

#define BOX_DIAMOND    0x60
#define BOX_BLOCK      0x61
#define BOX_DOT        0x7E

// Constantes da tela
#define SCRSTARTX      3      // Posições iniciais e finais na tela para o jogo
#define SCRENDX        75     // Significa a área que pode ser desenhada
#define SCRSTARTY      1
#define SCRENDY        23

#define MINX           1      // Posição mínima horizontal na tela
#define MINY           1      // Posição mínima vertical na tela
#define MAXX           80     // Posição máxima horizontal na tela
#define MAXY           24     // Posição máxima vertical na tela

/**
 * Tipo de cores da tela
 */
typedef enum {BLACK, RED, GREEN, BROWN, BLUE, MAGENTA, CYAN, LIGHTGRAY,
        DARKGRAY, LIGHTRED, LIGHTGREEN, YELLOW, LIGHTBLUE, 
        LIGHTMAGENTA, LIGHTCYAN, WHITE} screenColor;

/**
 * Mover o cursor para a posição (0,0)
 */
static inline void screenHomeCursor()
{
    printf("%s%s", ESC, HOMECURSOR);
}

/**
 * Mostrar o cursor
 */
static inline void screenShowCursor()
{
    printf("%s%s", ESC, SHOWCURSOR);
}

/**
 * Esconder o cursor
 */
static inline void screenHideCursor()
{
    printf("%s%s", ESC, HIDECURSOR);
}

/**
 * Limpar a tela
 */
static inline void screenClear()
{
    screenHomeCursor();
    printf("%s%s", ESC, CLEARSCREEN);
}

/**
 * Atualizar a tela imediatamente
 */
static inline void screenUpdate() {
    fflush(stdout);
}

/**
 * Definir o modo da tela para "normal"
 */
static inline void screenSetNormal()
{
    printf("%s%s", ESC, NORMALTEXT);
}

/**
 * Definir o modo da tela para "negrito"
 */
static inline void screenSetBold()
{
    printf("%s%s", ESC, BOLDTEXT);
}

/**
 * Definir o modo da tela para "piscar"
 */
static inline void screenSetBlink()
{
    printf("%s%s", ESC, BLINKTEXT);
}

/**
 * Definir o modo da tela para "inverso"
 */
static inline void screenSetReverse()
{
    printf("%s%s", ESC, REVERSETEXT);
}

/**
 * Habilitar caracteres de caixa no terminal
 */
static inline void screenBoxEnable()
{
    printf("%s%s", ESC, BOX_ENABLE);
}

/**
 * Desabilitar caracteres de caixa no terminal
 */
static inline void screenBoxDisable()
{
    printf("%s%s", ESC, BOX_DISABLE);
}

/**
 * Inicializar a tela, limpar a tela e opcionalmente desenhar bordas.
 *
 * @param drawBorders se diferente de zero, desenha bordas na tela.
 */
void screenInit(int drawBorders);

/**
 * Limpar a tela e restaurar para o estado inicial.
 */
void screenDestroy();

/**
 * Mover o cursor para a posição (x, y)
 * @param x posição x
 * @param y posição y
 */
void screenGotoxy(int x, int y);

/**
 * Definir as cores do texto
 * @param fg cor do primeiro plano, pode assumir valores de BLACK a WHITE
 * @param bg cor do fundo, pode assumir valores de BLACK a LIGHTGRAY
 */
void screenSetColor(screenColor fg, screenColor bg);

#endif /* __SCREEN_H__ */