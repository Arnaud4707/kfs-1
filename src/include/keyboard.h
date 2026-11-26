#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "header.h"
#include "io.h"
#include <stdint.h>

#define PS2_DATA 0x60
#define PS2_STATUS 0x64
#define PS2_COMMAND 0x64

// Alphabet:
#define KEY_A_PRESSED 	0x10
#define KEY_A_RELEASED 	0x90
#define KEY_Z_PRESSED	0x11
#define KEY_Z_RELEASED 	0x91
#define KEY_E_PRESSED	0x12
#define KEY_E_RELEASED	0x91
#define KEY_R_PRESSED	0x13
#define KEY_R_RELEASED	0x92
#define KEY_T_PRESSED	0x14
#define KEY_T_RELEASED	0x93
#define KEY_Y_PRESSED	0x15
#define KEY_Y_RELEASED	0x94
#define KEY_U_PRESSED	0x16
#define KEY_U_RELEASED	0x95
#define KEY_I_PRESSED	0x17
#define KEY_I_RELEASED	0x96
#define KEY_O_PRESSED	0x18
#define KEY_O_RELEASED	0x97
#define KEY_P_PRESSED	0x19
#define KEY_P_RELEASED	0x98
#define KEY_Q_PRESSED	0x1E
#define KEY_Q_RELEASED	0x9E
#define KEY_S_PRESSED	0x1F
#define KEY_S_RELEASED	0x9F
#define KEY_D_PRESSED	0x20
#define KEY_D_RELEASED	0xA0
#define KEY_F_PRESSED	0x21
#define KEY_F_RELEASED	0xA1
#define KEY_G_PRESSED	0x22
#define KEY_G_RELEASED	0xA2
#define KEY_H_PRESSED	0x23
#define KEY_H_RELEASED	0xA3
#define KEY_J_PRESSED	0x24
#define KEY_J_RELEASED	0xA4
#define KEY_K_PRESSED	0x25
#define KEY_K_RELEASED	0xA5
#define KEY_L_PRESSED	0x26
#define KEY_L_RELEASED	0xA6
#define KEY_M_PRESSED	0x27
#define KEY_M_RELEASED	0xA7
#define KEY_W_PRESSED	0x2C
#define KEY_W_RELEASED	0xAC
#define KEY_X_PRESSED	0x2D
#define KEY_X_RELEASED	0xAD
#define KEY_C_PRESSED	0x2E
#define KEY_C_RELEASED	0xAE
#define KEY_V_PRESSED	0x2F
#define KEY_V_RELEASED	0xAF
#define KEY_B_PRESSED	0x30
#define KEY_B_RELEASED	0xB0
#define KEY_N_PRESSED	0x31
#define KEY_N_RELEASED	0xB1

// Numbers:
#define KEY_1_PRESSED	0x02
#define KEY_1_RELEASED	0x82
#define KEY_2_PRESSED	0x03
#define KEY_2_RELEASED	0x83
#define KEY_3_PRESSED	0x04
#define KEY_3_RELEASED	0x84
#define KEY_4_PRESSED	0x05
#define KEY_4_RELEASED	0x85
#define KEY_5_PRESSED	0x06
#define KEY_5_RELEASED	0x86
#define KEY_6_PRESSED	0x07
#define KEY_6_RELEASED	0x87
#define KEY_7_PRESSED	0x08
#define KEY_7_RELEASED	0x88
#define KEY_8_PRESSED	0x09
#define KEY_8_RELEASED	0x89
#define KEY_9_PRESSED	0x0A
#define KEY_9_RELEASED	0x8A
#define KEY_0_PRESSED	0x0B
#define KEY_0_RELEASED	0x8B

// control key left
#define KEY_TAB_PRESSED		0x0F
#define KEY_TAB_RELEASED	0x8F
#define KEY_LSHIFT_PRESSED	0x2A
#define KEY_LSHIFT_RELEASED	0xAA
#define KEY_CRTL_PRESSED	0x1D
#define KEY_CRTL_RELEASED	0x9D

// control key right
#define KEY_DELATE_PRESSED	0x53
#define KEY_DELATE_RELEASED	0xD3
#define KEY_BACK_PRESSED	0x0E
#define KEY_BACK_RELEASED	0x8E
#define KEY_ENTER_PRESSED	0x1C
#define KEY_ENTER_RELEASED	0x9C
#define KEY_SPACE_PRESSED	0x39
#define KEY_SPACE_RELEASED	0xB9
#define KEY_ALTGR_PRESSED	0x38
#define KEY_ALTGR_RELEASED	0xB8

// Arrows:
#define KEY_UP_PRESSED	0x48
#define KEY_UP_RELEASED	0xC8
#define KEY_DOWN_PRESSED	0x50
#define KEY_DOWN_RELEASED	0xD0
#define KEY_LEFT_PRESSED	0x4B
#define KEY_LEFT_RELEASED	0xCB
#define KEY_RIGHT_PRESSED	0x4D
#define KEY_RIGHT_RELEASED	0xCD

/*
	@struct		Status Register Control Key

	@brief		Register of key'status, 3 bits describ there status.
				
	@param		bit 0: shift control, if 0 lowercase character, if 1 uppercase character.
				
	@param		bit 1: crtl control, if 0 ctrl disable, if 1 enable.
				
	@param		bit 2: alt gr control, if 0 alt gr disable, if 1 enable.
*/
extern uint8_t STATUS_KEY;	

/*
	@struct		Marco KEY_PRESS()

	@brief		Returne true if key has been pressed, data == key

	@param		data	data receive from device

	@param		key		scan code 1 (AZRTY) of key
*/
#define KEY_PRESS(data, key)	(data == key)

uint8_t ps2_read_status(void);
uint8_t	ps2_read_data(void);
void	ps2_write_data(uint8_t data);
void	ps2_wait_write(void);
void	ps2_wait_read(void);

void    keyboard(uint8_t data);

#endif