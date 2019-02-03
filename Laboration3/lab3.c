/*
 * lab3.c
 *
 * Created: 2016-11-30 23:32:21
 *  Author: Spellabbet
 */ 


#include <avr/io.h>
#include "hmi/hmi.h"
#include "numkey/numkey.h"
#include "regulator/regulator.h"
#include <stdio.h>

  enum state{
	MOTOR_OFF,
	MOTOR_ON_FORWARD,
	MOTOR_RUNNING_FORWARD,
	MOROT_ON_BACKWARD,
	MOTOR_RUNNING_BACKWARD
	};
	
	typedef enum state state_t;

int main(void)
{
	hmi_init();
	regulator_init();
	char key;
	
	uint8_t regulator = 0;
	
	state_t current_state = MOTOR_OFF;
	state_t next_state = MOTOR_OFF;
	
	char regulator_str [17]; 
	
    while(1)
    {
       key = numkey_read();
	   regulator = regulator_read();
	   sprintf(regulator_str, "SPEED %u%% ", regulator);
	   
	   switch (current_state)
	   {
		   case MOTOR_OFF:
		   output_msg("MOTOR OFF", regulator_str,0);
			   if (key == '1' && regulator == 0)
			   {
				   next_state = MOROT_ON_BACKWARD;
				   
				   output_msg("MOTOR BACKWARD", regulator_str,0);
			   }else if (key == '3' && regulator == 0)
			   {
				   next_state = MOTOR_ON_FORWARD;
				    output_msg("MOTOR FORWARD", regulator_str,0);
			   }
			   break;
		   case MOTOR_ON_FORWARD:
		   
			   if (key == '0')
			   {
				   next_state = MOTOR_OFF;
				   output_msg("MOTOR OFF", regulator_str,0);
			   }else if(regulator > 0)
			   {
				   next_state = MOTOR_RUNNING_FORWARD;
				   output_msg("MOTOR RUN F", regulator_str,0);
			   }
			   break;
			case MOTOR_RUNNING_FORWARD:
			output_msg("MOTOR RUN F", regulator_str,0);
				if (key == '0')
				{
					next_state = MOTOR_OFF;
					output_msg("MOTOR OFF", regulator_str,0);
				}
				break;
			 case MOROT_ON_BACKWARD:
				 if (key == '0')
				 {
					 next_state = MOTOR_OFF;
					 output_msg("MOTOR OFF",regulator_str,0);
				 }else if(regulator > 0)
				 {
					 next_state = MOTOR_RUNNING_BACKWARD;
					 output_msg("MOTOR RUN B", regulator_str,0);
				 }
				 break;
			case MOTOR_RUNNING_BACKWARD:
			output_msg("MOTOR RUN B", regulator_str,0);
				 if (key == '0')
				 {
					 next_state = MOTOR_OFF;
					 output_msg("MOTOR OFF", regulator_str,0);
				 }
				 break;
	   }
	   current_state = next_state;
	  
    }
}