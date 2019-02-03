/* ---------------------------------------------------
Space in the RAM to save the results from dice throws.

	The following functions are provided:
	store_stat (R24 contains the dice value)
			The function will increment the
			Total number of throws and the
			number of throws with results equals R24.

	get_stat (R24 gives the value for which the
			result is retrieved. If R24 = 0, the
			total number of throws shall be returned.
			The result is returned in R24.

	clear_stat (no parameters in nor out)
			Clears all data.
--------------------------------------------------------*/

	.DSEG			; The following applies to the RAM:
	.ORG 0x200		; Set starting point
					; address of data
					; segment to 0x200
	dice_stat:		.BYTE		7

	.CSEG

store_stat: 
	LDI				XH,			HIGH(dice_stat)
	LDI				XL,			LOW(dice_stat)

	LD				R25,		X	;
	INC				R25
	ST				X,			R25

	ADD				XL,			R24
	LD				R25,		X
	INC				R25
	ST				X,			R25
	
	RET

get_stat: 
	LDI				XH,			HIGH(dice_stat)
	LDI				XL,			LOW(dice_stat)


	ADD				XL,			R24
	LD				R24,		X
	
	RET

clear_stat: 
	LDI				XH,			HIGH(dice_stat)
	LDI				XL,			LOW(dice_stat)

	LDI				R20,		7		;Counter for the loop
	LDI				R25,		0

loop:
	ST				X+,			R25

	DEC				R20
	BRNE			loop

	RET