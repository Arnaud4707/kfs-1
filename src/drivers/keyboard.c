#include "../include/vga.h"
#include "../include/terminal.h"
#include "../include/keyboard.h"
#include "../include/screen.h"
#include <stdbool.h>

uint8_t STATUS_KEY = 0; 

uint8_t ps2_read_status(void)
{
    return inb(PS2_STATUS); 
}

uint8_t	ps2_read_data(void)
{
	return inb(PS2_DATA);
}

void	ps2_write_data(uint8_t data)
{
	outb(PS2_DATA, data);
}

void	ps2_wait_write(void)
{
	while (inb(PS2_STATUS) & 0x02)
    	;
}

void	ps2_wait_read(void)
{
    while (!(inb(PS2_STATUS) & 0x01))
        ;
}

void    keyboard(uint8_t data)
{
    static char shift = 0;
    static bool lockshift = false;
    static bool checklockshift = false;

    if (KEY_PRESS(data, KEY_ESCAPE_RELEASED))
        reboot();
    else if (KEY_PRESS(data, KEY_LSHIFT_PRESSED))
        STATUS_KEY |= (1 << BLSHIFT);
    else if (KEY_PRESS(data, KEY_LSHIFT_RELEASED))
        STATUS_KEY &= ~(1 << BLSHIFT);
    else if (KEY_PRESS(data, KEY_RSHIFT_PRESSED))
        STATUS_KEY |= (1 << BRSHIFT);
    else if (KEY_PRESS(data, KEY_RSHIFT_RELEASED))
        STATUS_KEY &= ~(1 << BRSHIFT);
    else if (KEY_PRESS(data, KEY_CRTL_PRESSED))
        STATUS_KEY |= (1 << BCRTL);
    else if (KEY_PRESS(data, KEY_CRTL_RELEASED))
    {
        if (fs.screen)
            change_screen(&fs.screen);
        STATUS_KEY &= ~(1 << BCRTL);
    }
    else if (KEY_PRESS(data, KEY_LOCKSHIFT_PRESSED))
    {
        if (!(lockshift))
            STATUS_KEY ^= (1 << BLOCKSHIFT);
        else
            checklockshift = true;
    }
    else if (KEY_PRESS(data, KEY_LOCKSHIFT_RELEASED))
    {
        if (checklockshift)
        {
            STATUS_KEY ^= (1 << BLOCKSHIFT);
            checklockshift = false;
        }
    }
    else if (KEY_PRESS(data, KEY_ALTGR_PRESSED))
        STATUS_KEY |= (1 << BALTGR);
    else if (KEY_PRESS(data, KEY_ALTGR_RELEASED))
        STATUS_KEY &= ~(1 << BALTGR);
    else if (KEY_PRESS(data, KEY_DELATE_PRESSED) || KEY_PRESS(data, KEY_BACK_PRESSED))
    {
        if (vga_window[fs.screen].terminal_column > 0)
        {
            if (vga_window[fs.screen].terminal_column >= 1)
                --(vga_window[fs.screen].terminal_column);
            terminal_putchar(' ');
            if (vga_window[fs.screen].terminal_column >= 1)
                --(vga_window[fs.screen].terminal_column);
            cursor_location(vga_window[fs.screen].terminal_column,   vga_window[fs.screen].terminal_row);
        }
    }
    else if (KEY_PRESS(data, KEY_TAB_PRESSED))
    {
        if ((STATUS_KEY & (1 << BCRTL)) && ((STATUS_KEY & (1 << BLSHIFT)) || (STATUS_KEY & (1 << BRSHIFT))))
            fs.screen = (fs.screen - 1) % 8;
        else if ((STATUS_KEY & (1 << BCRTL)))
            fs.screen = (fs.screen + 1) % 8;
        else
            terminal_writestring("  ");
    }
    else if (KEY_PRESS(data, KEY_ENTER_PRESSED))
        terminal_putchar('\n');
    else if (KEY_PRESS(data, KEY_A_PRESSED))
        terminal_putchar('a' - shift);
    else if (KEY_PRESS(data, KEY_Z_PRESSED))
        terminal_putchar('z' - shift);
    else if (KEY_PRESS(data, KEY_E_PRESSED))
    {
        if (STATUS_KEY & (1 << BALTGR))
            terminal_writestring("€");
        else
            terminal_putchar('e' - shift);}
    else if (KEY_PRESS(data, KEY_R_PRESSED))
        terminal_putchar('r' - shift);
    else if (KEY_PRESS(data, KEY_T_PRESSED))
        terminal_putchar('t' - shift);
    else if (KEY_PRESS(data, KEY_Y_PRESSED))
        terminal_putchar('y' - shift);
    else if (KEY_PRESS(data, KEY_U_PRESSED))
        terminal_putchar('u' - shift);
    else if (KEY_PRESS(data, KEY_I_PRESSED))
        terminal_putchar('i' - shift);
    else if (KEY_PRESS(data, KEY_O_PRESSED))
        terminal_putchar('o' - shift);
    else if (KEY_PRESS(data, KEY_P_PRESSED))
        terminal_putchar('p' - shift);
    else if (KEY_PRESS(data, KEY_Q_PRESSED))
        terminal_putchar('q' - shift);
    else if (KEY_PRESS(data, KEY_S_PRESSED))
        terminal_putchar('s' - shift);
    else if (KEY_PRESS(data, KEY_D_PRESSED))
        terminal_putchar('d' - shift);
    else if (KEY_PRESS(data, KEY_F_PRESSED))
        terminal_putchar('f' - shift);
    else if (KEY_PRESS(data, KEY_G_PRESSED))
        terminal_putchar('g' - shift);
    else if (KEY_PRESS(data, KEY_H_PRESSED))
        terminal_putchar('h' - shift);
    else if (KEY_PRESS(data, KEY_J_PRESSED))
        terminal_putchar('j' - shift);
    else if (KEY_PRESS(data, KEY_K_PRESSED))
        terminal_putchar('k' - shift);
    else if (KEY_PRESS(data, KEY_L_PRESSED))
        terminal_putchar('l' - shift);
    else if (KEY_PRESS(data, KEY_M_PRESSED))
        terminal_putchar('m' - shift);
    else if (KEY_PRESS(data, KEY_W_PRESSED))
        terminal_putchar('w' - shift);
    else if (KEY_PRESS(data, KEY_X_PRESSED))
        terminal_putchar('x' - shift);
    else if (KEY_PRESS(data, KEY_C_PRESSED))
        terminal_putchar('c' - shift);
    else if (KEY_PRESS(data, KEY_V_PRESSED))
        terminal_putchar('v' - shift);
    else if (KEY_PRESS(data, KEY_B_PRESSED))
        terminal_putchar('b' - shift);
    else if (KEY_PRESS(data, KEY_N_PRESSED))
        terminal_putchar('n' - shift);
    else if (KEY_PRESS(data, KEY_1_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('1');
        else
            terminal_putchar('&');
    }
    else if (KEY_PRESS(data, KEY_2_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('2');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('~');
        else
            terminal_writestring("é");
    }
    else if (KEY_PRESS(data, KEY_3_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('3');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('#');
        else
            terminal_putchar('"');
    }
    else if (KEY_PRESS(data, KEY_4_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('4');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('{');
        else
            terminal_putchar('\'');
    }
    else if (KEY_PRESS(data, KEY_5_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('5');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('[');
        else
            terminal_putchar('(');
    }
    else if (KEY_PRESS(data, KEY_6_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('6');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('|');
        else
            terminal_putchar('-');
    }
    else if (KEY_PRESS(data, KEY_7_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('7');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('`');
        else
            terminal_writestring("è");
    }
    else if (KEY_PRESS(data, KEY_8_PRESSED))
    {
        if ((STATUS_KEY & ((uint8_t)1 << BLSHIFT) || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))))
            terminal_putchar('8');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('\\');
        else
            terminal_putchar('_');
    }
    else if (KEY_PRESS(data, KEY_9_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('9');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('^');
        else
            terminal_writestring("ç");
    }
    else if (KEY_PRESS(data, KEY_0_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('0');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('@');
        else
            terminal_writestring("à");
    }
    else if (KEY_PRESS(data, KEY_SPECIAL01_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_writestring("Œ");
        else
            terminal_writestring("œ");
    }
    else if (KEY_PRESS(data, KEY_SPECIAL02_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_writestring("°");
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar(']');
        else
            terminal_putchar(')');
    }
    else if (KEY_PRESS(data, KEY_SPECIAL03_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('+');
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_putchar('}');
        else
            terminal_putchar('=');
    }
    else if (KEY_PRESS(data, KEY_SPECIAL05_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_writestring("£");
        else if (STATUS_KEY & ((uint8_t)1 << BALTGR))
            terminal_writestring("ê");
        else
            terminal_writestring("$");
    }
    else if (KEY_PRESS(data, KEY_SPECIAL06_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_writestring("µ");
        else
            terminal_putchar('*');
    }
    else if (KEY_PRESS(data, KEY_SPECIAL07_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('%');
        else
            terminal_writestring("ù");
    }
    else if (KEY_PRESS(data, KEY_SPECIAL08_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('?');
        else
            terminal_putchar(',');
    }
    else if (KEY_PRESS(data, KEY_SPECIAL09_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('.');
        else
            terminal_putchar(';');
    }
    else if (KEY_PRESS(data, KEY_SPECIAL10_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('/');
        else
            terminal_putchar(':');
    }
    else if (KEY_PRESS(data, KEY_SPECIAL11_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_writestring("§");
        else
            terminal_putchar('!');
    }
    else if (KEY_PRESS(data, KEY_SPECIAL12_PRESSED))
    {
        if (STATUS_KEY & ((uint8_t)1 << BLSHIFT)
        || (STATUS_KEY & ((uint8_t)1 << BLOCKSHIFT))
        || (STATUS_KEY & (1 << BRSHIFT)))
            terminal_putchar('>');
        else
            terminal_putchar('<');
    }
    else if (KEY_PRESS(data, KEY_UP_PRESSED))
    {
        if (vga_window[fs.screen].terminal_row >= 1)
            --(vga_window[fs.screen].terminal_row);
        cursor_location(vga_window[fs.screen].terminal_column, vga_window[fs.screen].terminal_row);
    }
    else if (KEY_PRESS(data, KEY_DOWN_PRESSED))
    {
        if (vga_window[fs.screen].terminal_row < (VGA_HEIGHT - 1))
            ++(vga_window[fs.screen].terminal_row);
        cursor_location(vga_window[fs.screen].terminal_column, vga_window[fs.screen].terminal_row);
    }
    else if (KEY_PRESS(data, KEY_LEFT_PRESSED))
    {
        if (vga_window[fs.screen].terminal_column >=  1)
            --(vga_window[fs.screen].terminal_column);
        cursor_location(vga_window[fs.screen].terminal_column, vga_window[fs.screen].terminal_row);
    }
    else if (KEY_PRESS(data, KEY_RIGHT_PRESSED))
    {
        if (vga_window[fs.screen].terminal_column < (VGA_WIDTH - 1))
            ++(vga_window[fs.screen].terminal_column);
        cursor_location(vga_window[fs.screen].terminal_column, vga_window[fs.screen].terminal_row);
    }
    // else {
    //     print_hex(data);
    // }

    if (STATUS_KEY & (1 << BLSHIFT)
    || STATUS_KEY & (1 << BLOCKSHIFT)
    || (STATUS_KEY & (1 << BRSHIFT)))
        shift = 32;
    else
        shift = 0;

    if (STATUS_KEY & (1 << BLOCKSHIFT))
        lockshift = true;
    else
        lockshift = false;
}
