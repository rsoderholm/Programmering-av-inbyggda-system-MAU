/*
 * delay.inc
 *
 * This file contains delay routines.
 *
 * Created by Mathias Beckius, 25 June 2015, for the course DA346A at
 * Malmo University.
 */

;==============================================================================
; Delay of 1 �s (including RCALL)
;==============================================================================
delay_1_micros:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	RET

;==============================================================================
; Delay of X �s
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R24				Input parameter data (X �s)
;==============================================================================
delay_micros:
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DEC				R24
	CPI				R24,			0				; more loops to do?
	BRNE			delay_micros					; continue!
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R18				Copy of parameter data (X ms)
;	R24				Input parameter data (X ms) and
;					also input to 'delay_micros'.
;==============================================================================
delay_ms:

	MOV				R18,			R24

;Call the method delay_micros so it runs 250*4 times thus being one ms. 
;Do this the amount of times that is given in R24 upon call
loop_dms:

	LDI				R24,			250
	RCALL			delay_micros
	LDI				R24,			250
	RCALL			delay_micros
	LDI				R24,			250
	RCALL			delay_micros
	LDI				R24,			250
	RCALL			delay_micros

	DEC				R18
	CPI				R18,			0				; more loops to do?
	BRNE			loop_dms						; continue!
	RET

;==============================================================================
; Delay of one (1) s
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_1_s:
	MOV				R17,			R24

	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms

	RET



;==============================================================================
; Delay of X s
;	LDI + RCALL = 4 cycles
; Uses registers:
;	R17				Copy of parameter data (X s)
;	R24				Input parameter data (X s) and
;					also input to 'delay_micros'.
;==============================================================================
delay_s:
	MOV				R17,			R24

;Call the method delay_micros so it runs 250*4 times thus being one ms. 
;Do this the amount of times that is given in R24 upon call
loop_ds:

	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms
	LDI				R24,			250
	RCALL			delay_ms

	DEC				R17
	CPI				R17,			0				; more loops to do?
	BRNE			loop_ds							; continue!
	RET

