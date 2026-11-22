#include "../include/terminal.h"

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
	terminal_writestring("\033[1mHello\033[0m, \033[15mkernel\033[0m \033[4mWorld\033[0m!\nNew \033[13mline is\033[0m done\n");
	terminal_writestring("\033[10mLorem ipsum dolor sit amet\033[0m, \nconsectetur adipiscing elit.");
	// enable_cursor(13 , 15);
	// disable_cursor();
	while (1);
}
