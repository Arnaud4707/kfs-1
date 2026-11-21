.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

.section .multiboot 			/* set section multiboot in sections'table of binary */
.align 4 						/* align on 4 bytes boundaries */
.long MAGIC						/* format MAGIC on 4 bytes, GRUB search signature at first 8 KiB of binary */
.long FLAGS						/* format FLAGS on 4 bytes */
.long CHECKSUM					/* format CHECKSUM on 4 bytes */

/* set stack */

.section .bss 					/* set section bss in sections'table of binary */
.align 16						/* align on 16 bytes boundaries because System V ABI for 32bit */
stack_bottom:					/* Bottom of stack, stack increase form bottom to top in memory */
.skip 16384 					# 16 KiB
stack_top:

.section .text					/* set segment of code in section text */
.global _start					/* _start is the entry point of kernel */
.type _start, @function
_start:

	mov $stack_top, %esp /* mov stack_top in esp register who is the pointer of stack */

	/* 
		call kernel_main function, this symbol is into binary. 2 things are done here,
		1st save address of next instruction (return's address) on the stack and 2nd jump at kernel_main's address.
	*/

	call kernel_main

	cli 							/* Disable interrupts */
1:	hlt 							/* Wait for the next interrupt to arrive */
	jmp 1b 							/* Jump to last label 1 so (1)*/

.size _start, . - _start			/* set size of start function */
