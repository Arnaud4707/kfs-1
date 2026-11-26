#include "../include/terminal.h"
#include "../include/vga.h"

void	change_screen(uint8_t* sc)
{
	uint16_t buff[VGA_HEIGHT * VGA_WIDTH];
	size_t	term_c;
	size_t	term_x;
	size_t	term_y;
	for (uint8_t y = 0; y < VGA_HEIGHT; y++){
		term_c = vga_window[0].terminal_color;
		term_x = vga_window[0].terminal_column;
		term_y = vga_window[0].terminal_row;
		vga_window[0].terminal_color = vga_window[*sc].terminal_color;
		vga_window[0].terminal_column = vga_window[*sc].terminal_column;
		vga_window[0].terminal_row = vga_window[*sc].terminal_row;
		vga_window[*sc].terminal_color = term_c;
		vga_window[*sc].terminal_column = term_x;
		vga_window[*sc].terminal_row = term_y;

		for (uint8_t x = 0; x < VGA_WIDTH; x++){
			uint16_t index = y * VGA_WIDTH + x;
			buff[index] = vga_window[0].terminal_buffer[index];
			vga_window[0].terminal_buffer[index] = vga_window[*sc].terminal_buffer[index];
			vga_window[*sc].terminal_buffer[index] = buff[index];
		}
	}
	*sc = 0;
	cursor_location(vga_window[0].terminal_column, vga_window[0].terminal_row);
}