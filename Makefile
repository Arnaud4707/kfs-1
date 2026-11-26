NAME= kfs-1
KERNEL= iso/boot/$(NAME)
ISO= $(NAME).iso

DIR_SRC= src/
DIR_OBJ= obj/

CODE_KERNEL= kernel/kernel.c
CODE_TERMINAL= drivers/terminal.c drivers/color.c drivers/keyboard.c drivers/screen.c
CODE_BOOT= boot/boot.s

SRCK= $(addprefix $(DIR_SRC),$(CODE_KERNEL))
SRCT= $(addprefix $(DIR_SRC),$(CODE_TERMINAL))
SRCB= $(addprefix $(DIR_SRC),$(CODE_BOOT))

OBJ= $(patsubst $(DIR_SRC)%.c,$(DIR_OBJ)%.o,$(SRCK))
OBJ+= $(patsubst $(DIR_SRC)%.c,$(DIR_OBJ)%.o,$(SRCT))
OBJ+= $(patsubst $(DIR_SRC)%.s,$(DIR_OBJ)%.o,$(SRCB))

LDSCRIPT= linker.ld

AS= i686-elf-as
ASFLAGS= --32

CC= i686-elf-gcc
CFLAGS= -Wall -Wextra -Werror -I include -m32 -march=i386 -mtune=i386 -O2
CFLAGS+= -fno-builtin -ffreestanding -fno-exceptions
CFLAGS+= -fno-stack-protector -nostdlib -nodefaultlibs -fno-pie -fno-pic
CFLAGS+= -ffunction-sections -fdata-sections

LD= i686-elf-ld
LDFLAGS= -m elf_i386 --no-pie --gc-sections -T $(LDSCRIPT) --build-id=none -nostdlib

$(DIR_OBJ)boot/%.o: $(DIR_SRC)boot/%.s
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

$(DIR_OBJ)kernel/%.o: $(DIR_SRC)kernel/%.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)drivers/%.o: $(DIR_SRC)drivers/%.c 
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(ISO)

$(KERNEL): $(OBJ) $(LDSCRIPT)
	mkdir -p $(dir $@)
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
