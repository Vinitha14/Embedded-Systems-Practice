// Lab13.c

// Runs on LM4F120 or TM4C123

// Use SysTick interrupts to implement a 4-key digital piano

// edX Lab 13 

// Daniel Valvano, Jonathan Valvano

// March 13, 2014

// Port B bits 3-0 have the 4-bit DAC

// Port E bits 3-0 have 4 piano keys


#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "TExaS.h"
#include "DAC.h"

// basic functions defined at end of startup.s

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);



int main(void){ // Real Lab13 

	unsigned long i;     
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
  TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn); // activate grader and set system clock to 80 MHz

  // PortE used for piano keys, PortB used for DAC        

	DisableInterrupts();
  Sound_Init(500000); // initialize SysTick timer and DAC
  EnableInterrupts();  // enable after all initialization are done	
	Sound_Off();



	// Initial testing, law of superposition

  DAC_Out(1);
  DAC_Out(2);
  DAC_Out(4);

// static testing, single step and record Vout

  for(i=0;i<8;i++){

    DAC_Out(i);

  }

  while(1) {              

		Sound_Tone(1000);		

  }            

}

// Inputs: Number of msec to delay

// Outputs: None

void delay(unsigned long msec){ 

  unsigned long count;

  while(msec > 0 ) {  // repeat while there are still delay

    count = 16000;    // about 1ms

    while (count > 0) { 

                count--;

    } // This while loop takes approximately 3 cycles

    msec--;
  }
}

