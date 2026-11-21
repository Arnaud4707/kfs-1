NAME= kfs-1
KERNEL= iso/boot/$(NAME)
ISO= $(NAME).iso

DIR_SRC= src/

CCODE= kernel/kernel.c
SCODE= boot/boot.s
DIR_OBJ= obj/
OBJ= $(addprefix  $(DIR_OBJ), $(CCODE:.c=.o))
OBJ+= $(addprefix  $(DIR_OBJ), $(SCODE:.s=.o))
LDSCRIPT= linker.ld

AS= i686-elf-as
ASFLAGS= -- 32

CC= i686-elf-gcc
CFLAGS= -Wall -Wextra -Werror -m32 -mtune=i386 -fno-builtin -fno-exceptions -fno-stack-protector
CFLAGS+= -nostdlib -nodefaultlibs -fno-pie -fno-pic -O2

LD= i686-elf-ld
LDFLAGS= -m elf_i386 --no-pie --gc-sections -T $(LDSCRIPT) --build-id=none

$(DIR_OBJ)%.o: %.s
	mkdir -p $(dir $@)
	$(AS) -c $< -o $@

$(DIR_OBJ)%.o: %.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(ISO)

$(KERNEL): $(OBJ) $(LDFLAGS)
	mkdir -p iso/boot/
	$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJ)

$(ISO): $(KERNEL)
	grub-mkrescue -o $(ISO) iso

run_kernel: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL)

run_iso: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(ISO) $(KERNEL)

re: fclean all

.PHONY: all clean fclean re run_iso run_kernel
