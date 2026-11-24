#include "../include/terminal.h"
#include "../include/color.h"


/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
	#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
	#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

	/* Newline support is left as an exercise. */
	terminal_writestring(BLUE"Hello"ENDCOLOR", "WHITE"kernel"ENDCOLOR" "RED"World"ENDCOLOR"!\nNew "LIGHT_MAGENTA"line is"ENDCOLOR" done\n");
	terminal_writestring(LIGHT_GREEN"Lorem ipsum dolor sit amet"ENDCOLOR", \nconsectetur adipiscing elit.");
	enable_cursor(0 , 15);
	// disable_cursor();
	while (1);
}
