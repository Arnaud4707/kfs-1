#ifndef COLOR_H
#define COLOR_H

#include "header.h"

#define BLACK "\033[0m"
#define BLUE "\033[1m"
#define GREEN "\033[2m"
#define CYAN "\033[3m"
#define RED "\033[4m"
#define MAGENTA "\033[5m"
#define BROWN "\033[6m"
#define LIGHT_GREY "\033[7m"
#define DARK_GREY "\033[8m"
#define LIGHT_BLUE "\033[9m"
#define LIGHT_GREEN "\033[10m"
#define LIGHT_CYAN "\033[11m"
#define LIGHT_RED "\033[12m"
#define LIGHT_MAGENTA "\033[13m"
#define LIGHT_BROWN "\033[14m"
#define WHITE "\033[15m"
#define ENDCOLOR "\033[0m"

bool color_terminal(uint8_t *color, char c);

#endif