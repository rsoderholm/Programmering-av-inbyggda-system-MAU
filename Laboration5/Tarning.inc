
/*
* Loads value 6 in R25
* Author Kristoffer Linderman and Robin Söderholm
*/

;==============================================================================
; Roll function for rolling a dice 
; Uses registers:
;	R25				temporary storage of the dice
;==============================================================================

roll_dice:

	LDI				R25,			6			;dice have 6 values

/*
* Test program which lets the user roll the dice
*/
test:

	NOP
	NOP

	RCALL			read_keyboard_num			;key-value in RVAL
	CPI				R24,			NO_KEY
	
	BRNE			roll						;yes, key 1 is still pressed
	RET											;no, key is released


/*
* Rolls the dice.
*
*/
roll:
	DEC				R25
	BREQ			roll_dice					;R25 is zero, start agn at 6
	RJMP			test						;no, keep rolling
