#ifndef TERMINAL_H
#define TERMINAL_H

#include "header.h"
#include <stdint.h>

typedef struct screen_s {
	size_t terminal_row;
	size_t terminal_column;
	uint8_t terminal_color;
	uint16_t *terminal_buffer;
	uint16_t *addr_cursor;
} screen_t;

typedef struct focus_s{
	uint8_t	screen;
} focus;

#define CURSOR 0x3D4
#define CURSOR_START 0x02
#define CURSOR_END 0x03

enum	vga_screen{
	SCREEN_1 = 0,
	SCREEN_2 = 1,
	SCREEN_3 = 2,
	SCREEN_4 = 3,
	SCREEN_5 = 4,
	SCREEN_6 = 5,
	SCREEN_7 = 6,
	SCREEN_8 = 7,
};

extern screen_t vga_window[8];
extern focus	fs;

void terminal_initialize(void);
void terminal_writestring(const char *data);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void terminal_putchar(char c);

void cursor_location(size_t x, size_t y);
void disable_cursor();

static inline void print_hex(uint8_t data) {
  const char *hex = "0123456789ABCDEF";

  terminal_putchar(hex[data >> 4]);
  terminal_putchar(hex[data & 0x0F]);
  terminal_putchar('\n');
};

#endif