#ifndef TERMINAL_H
#define TERMINAL_H

#include "header.h"

extern    size_t terminal_row;
extern    size_t terminal_column;
extern    uint8_t terminal_color;
extern    uint16_t* terminal_buffer;

void terminal_initialize(void);
void terminal_writestring(const char* data) ;

#endif