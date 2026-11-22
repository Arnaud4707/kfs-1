#ifndef TERMINAL_H
#define TERMINAL_H

#include "header.h"

#define CURSOR			0x3D4
#define CURSOR_START	0x02
#define CURSOR_END		0x03

extern    size_t terminal_row;
extern    size_t terminal_column;
extern    uint8_t terminal_color;
extern    uint16_t* terminal_buffer;
extern    uint16_t* addr_cursor;

void terminal_initialize(void);
void terminal_writestring(const char* data);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();


#endif