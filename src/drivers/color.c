#include "../include/vga.h"

bool color_terminal(uint8_t *color, char c) {
	static	uint8_t state = 0;
	static	size_t value = 0;

	switch (state) {
		case 0:
			if (c == '\033'){
				state = 1;
				return true;
			}
			return false;
		case 1:
			if (c == '['){
				state = 2;
				return true;
			}
			state = 0;
			return true;
		case 2:
			if (c >= '0' && c <= '9'){
				value = value * 10 + (c - '0');
				return true;
			}

			if (c == 'm'){
				if (value == 0)
					*color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
				else
					*color = vga_entry_color(value, VGA_COLOR_BLACK);
			}
			state = 0;
			value = 0;
			return true;
	}
	return false;
}