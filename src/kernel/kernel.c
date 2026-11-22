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
	terminal_writestring("Hello, kernel World!\nNew line is done");
	terminal_writestring("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus varius diam a mi iaculis laoreet. Maecenas libero dolor, pretium eu pharetra ut, scelerisque non sapien. Suspendisse purus sapien, consequat vel viverra sit amet, faucibus eget leo. Integer volutpat turpis ante, eget egestas urna sodales a. Sed condimentum eros urna, in vestibulum diam imperdiet sit amet. Proin vehicula commodo metus eget placerat. Integer ac ante et nunc vulputate ultrices. Morbi eget metus arcu. Aliquam erat volutpat. Nunc euismod tortor ante, eget blandit tellus posuere eget. " \
	" Sed interdum erat vitae risus tempus, nec facilisis enim faucibus. Nunc interdum arcu lectus, et posuere dui pharetra et. Maecenas non sapien mollis, tristique felis in, vestibulum dui. Ut eu quam pharetra, auctor odio et, gravida metus. Aliquam tincidunt consequat varius. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Suspendisse potenti. Fusce nec urna pulvinar, consectetur nulla quis, consectetur odio. Morbi congue diam ac dolor dignissim elementum. Vestibulum sed mattis quam. Aliquam ac nulla tellus. Integer massa ligula, feugiat quis odio in, ornare finibus nisl. Mauris consectetur accumsan ante condimentum tristique." \
	"Nulla laoreet nisl enim, nec mollis ex gravida vitae. Curabitur et nulla velit. Aenean at erat sed leo imperdiet elementum. Mauris euismod, leo vel accumsan facilisis, leo lorem convallis turpis, a tempor erat ante eu mauris. Proin feugiat lacus eu condimentum finibus. Cras id sapien sed tellus hendrerit commodo. Quisque id metus in orci fringilla sollicitudin. Sed mollis quam at sodales ornare. Pellentesque commodo sapien feugiat nisl lobortis posuere. Vestibulum vitae diam nisi. Cras eleifend sem eu imperdiet semper. Mauris semper vitae enim a vulputate. Vivamus quis nisi semper, bibendum arcu sit amet, cursus orci." \
	"Quisque vel interdum magna. In gravida lectus lectus, vel lacinia felis eleifend ac. Sed eget libero arcu. Donec quis urna vel lacus egestas pharetra ut at sem.");
	while (1);
}
