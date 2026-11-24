#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "header.h"
#include "io.h"

#define PS2_DATA    0x60
#define PS2_STATUS  0x64
#define PS2_COMMAND 0x64

uint8_t ps2_read_status(void)
{
    return inb(PS2_STATUS);
}

uint8_t ps2_read_data(void)
{
    return inb(PS2_DATA);
}

void ps2_wait_write(void)
{
    while (inb(PS2_STATUS) & 0x02);
}

void ps2_wait_read(void)
{
    while (!(inb(PS2_STATUS) & 0x01));
}

#endif