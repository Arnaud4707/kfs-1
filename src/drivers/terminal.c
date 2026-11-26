#include "../include/vga.h"
#include "../include/terminal.h"
#include "../include/color.h"
#include "../include/io.h"

/**
	Each page of VGA MEMORY BUFFER use 4Mo so with unsined int 16 bits we move of 16 bits
	when we add 1 to address so 2000 * 2 byte = 4M
*/
screen_t vga_window[8] = {
	{0,0, 0, (uint16_t*)VGA_MEMORY, (uint16_t*)CURSOR},
	{0,0, 0, (uint16_t*)VGA_MEMORY + 2000, (uint16_t*)CURSOR},
	{0,0, 0, (uint16_t*)VGA_MEMORY + 4000, (uint16_t*)CURSOR},
	{0,0, 0, (uint16_t*)VGA_MEMORY + 6000, (uint16_t*)CURSOR},
	{0,0, 0, (uint16_t*)VGA_MEMORY + 8000, (uint16_t*)CURSOR},
	{0,0, 0, (uint16_t*)VGA_MEMORY + 10000, (uint16_t*)CURSOR},
	{0,0, 0, (uint16_t*)VGA_MEMORY + 12000, (uint16_t*)CURSOR},
	{0,0, 0, (uint16_t*)VGA_MEMORY + 14000, (uint16_t*)CURSOR}
};

focus fs = {0};

void terminal_initialize(void)
{
	for (uint8_t i = 0; i < 8; i++){
		vga_window[i].terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

		for (size_t y = 0; y < VGA_HEIGHT; y++) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				const size_t index = y * VGA_WIDTH + x;
				vga_window[i].terminal_buffer[index] = vga_entry(' ', vga_window[i].terminal_color);
			}
		}
	}

}

void terminal_setcolor(uint8_t color, enum vga_screen sc) 
{
	vga_window[sc].terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	vga_window[fs.screen].terminal_buffer[index] = vga_entry(c, color);
}

void terminal_Scrolling()
{
	vga_window[fs.screen].terminal_row = VGA_WIDTH - 1;
	for (size_t y = 0; (y + 1) < VGA_HEIGHT; y++){
		for (size_t x = 0; x < VGA_WIDTH; x++){
		const size_t index = y * VGA_WIDTH + x;
		const size_t index_bis = (y + 1) * VGA_WIDTH + x;
		vga_window[fs.screen].terminal_buffer[index] = vga_window[fs.screen].terminal_buffer[index_bis];
		}
	}
	for (size_t x = 0; x < VGA_WIDTH; x++){
		const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
		vga_window[fs.screen].terminal_buffer[index] = vga_entry(' ', vga_window[fs.screen].terminal_color);
	}
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void cursor_location(size_t x, size_t y)
{
	uint16_t pos = y * VGA_WIDTH + x;
	outb(0x3D4, 0x0E);
	outb(0x3D5, (inb(0x3D5) & 0x00) | (uint8_t)((pos >> 8) & 0xFF));

	outb(0x3D4, 0x0F);
	outb(0x3D5, (inb(0x3D5) & 0x00) | (uint8_t)(pos & 0xFF));
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void terminal_putchar(char c) 
{
	if (color_terminal(&(vga_window[fs.screen].terminal_color), c) == true)
		return;
	if (c != 0x0A)
		terminal_putentryat(c, vga_window[fs.screen].terminal_color, vga_window[fs.screen].terminal_column, vga_window[fs.screen].terminal_row);
	else
	{
		vga_window[fs.screen].terminal_column = 0;
		if (++(vga_window[fs.screen].terminal_row) == VGA_HEIGHT)
			terminal_Scrolling();
		cursor_location(vga_window[fs.screen].terminal_column, vga_window[fs.screen].terminal_row);
		return;
	}
	if (++(vga_window[fs.screen].terminal_column) == VGA_WIDTH) {
		vga_window[fs.screen].terminal_column = 0;
		if (++(vga_window[fs.screen].terminal_row) == VGA_HEIGHT)
			terminal_Scrolling();
	}
	cursor_location(vga_window[fs.screen].terminal_column, vga_window[fs.screen].terminal_row);
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}