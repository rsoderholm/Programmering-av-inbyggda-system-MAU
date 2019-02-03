/*
 * lab4.asm
 *
 * This program scans the keypad of the "iBridge keypad shield", and prints
 * the corresponding character of the key on a Nokia 5110 LCD, which is
 * mounted on the shield.
 * This program is written for the Arduino Mega board (ATmega2560).
 *
 * For registers in the Extended I/O space, STS must be used instead of
 * OUT, CBI, SBI. The macros SET_IO_BIT and CLR_IO_BIT is written for
 * the purpose of simplifying setting/clearing a specific bit in a I/O
 * register.
 *
 * "Created" by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
 * 
 * Modified and made better by Kristoffer Linderman and Robin Söderholm, Jeff 8/12 2016
 */
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU			RESET		 =	0x0000			; reset vector
	.EQU			PM_START	 =	0x0072			; start of program

	; Bit masks, to be used together with SET_IO_BIT and CLR_IO_BIT
	.EQU			BIT3_HIGH	 =	0x08	; 0b00001000
	.EQU			BIT3_LOW	 =	0xF7	; 0b11110111
	.EQU			BIT4_HIGH	 =	0x10	; 0b00010000
	.EQU			BIT4_LOW	 =	0xEF	; 0b11101111
	.EQU			BIT5_HIGH	 =	0x20	; 0b00100000
	.EQU			BIT5_LOW	 =	0xDF	; 0b11011111
	.EQU			BIT6_HIGH	 =	0x40	; 0b01000000
	.EQU			BIT6_LOW	 =	0xBF	; 0b10111111

;==============================================================================
; Macro for setting a bit in I/O register, located in the extended I/O space.
; Uses registers:
;	R24				Store I/O data
;
; Example: Set bit 6 in PORTH
;	SET_IO_BIT		PORTH,			BIT6_HIGH
;==============================================================================
	.MACRO			SET_IO_BIT

	LDS				R24,			@0
	ORI				R24,			@1
	STS				@0,				R24

	.ENDMACRO

;==============================================================================
; Macro for clearing a bit in I/O register, located in the extended I/O space.
; Uses registers:
;	R24				Store I/O data
;
; Example: Clear bit 6 in PORTH
;	CLR_IO_BIT		PORTH,			BIT6_LOW
;==============================================================================
	.MACRO			CLR_IO_BIT

	LDS				R24,			@0
	ANDI			R24,			@1
	STS				@0,				R24

	.ENDMACRO

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG			RESET
	RJMP			init

	.ORG			PM_START
	.INCLUDE		"delay.inc"
	.INCLUDE		"lcd.inc"					; avkommenteras i moment 3
	.INCLUDE		"keyboard.inc"				; avkommenteras i moment 5

;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
	LDI				R16,			LOW(RAMEND)		; Set stack pointer
	OUT				SPL,			R16				; at the end of RAM.
	LDI				R16,			HIGH(RAMEND)
	OUT				SPH,			R16
	RCALL			init_pins						; Initialize pins
	RCALL			init_pins_led
	RCALL			lcd_init						; Initialize LCD - avkommenteras i moment 3
	RJMP			main							; Jump to main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:
	; PORT B
	; output:	4, 5 and 6 (LCD command/character, reset, CS/SS)
	LDI				R16,			0x70
	OUT				DDRB,			R16
	; PORT H
	; output:	3 and 4 (keypad col 2 and 3)
	;			5 and 6 (LCD clock and data)
	LDI				R16,			0x78
	STS				DDRH,			R16
	; PORT E
	; output:	3 (keypad col 1)
	; input:	4 and 5 (keypad row 2 and 3)
	LDI				R16,			0x08
	OUT				DDRE,			R16
	; PORT F
	; input:	4 and 5 (keypad row 1 and 0)
	LDI				R16,			0x00
	OUT				DDRF,			R16
	; PORT G
	; output:	5 (keypad col 0)
	LDI				R16,			0x20
	OUT				DDRG,			R16
	RET

init_pins_led:
	SBI				DDRB,			7			; enable LED as output
	RET

;==============================================================================
; Main part of program
; Uses registers:
;	R20				temporary storage of pressed key
;	R24				input / output values
;==============================================================================
	
	main:
	CLEARSCREEN
	LCD_WRITE_CMD	0x00
	read:

	RCALL			read_keyboard_num

	;Check if the input is NO_KEY (16) 
	;If NO_KEY jump to read again
	CPI				R24,			NO_KEY
	BREQ			read

	RCALL			convert_to_ASCII
	LCD_WRITE_CHR


	no_repeat:
	RCALL			read_keyboard_num
	RCALL			convert_to_ASCII
	CPI				R24,			NO_KEY
	BRNE			no_repeat

	RJMP			read

	


 


