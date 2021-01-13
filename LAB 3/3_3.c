#include "PLL.h"
#include "tm4c123gh6pm.h"
#include <TM4C123.h>

void DisableInterrupts(void);// Disable interrupts
void EnableInterrupts(void);// Enable interrupts
void WaitForInterrupt(void);// low power mode
void PortA_Init(void);// start sound output
void PortF_Init(void);
void SysFun(void);
void SysInit(void);//initialize SysTick timer
void SysLoad(unsigned long period);//Load reload value

int main(void)
{ 
	int k;
	PLL_Init();
	SysFun();
	PortA_Init();
	PortF_Init();
	SysInit();
	
	while(1)
	{
		k=0;
				while( (GPIO_PORTF_DATA_R&0x11)==0x01)
				{
						SysLoad(80000);
					  k=k+1;
				}
				
			  while(k>0)
				{
					GPIO_PORTA_DATA_R=0x20;
					SysLoad(80000);
					k--;
				}
				GPIO_PORTA_DATA_R=0x00;	  
	}
}

void PortA_Init(void)
{
	unsigned long volatile delay;
	/*PORT Initialization*/
	SYSCTL_RCGC2_R |= 0x01; // Port a clock
	delay = SYSCTL_RCGC2_R; // wait 3-5 bus cycles
	GPIO_PORTA_DIR_R |= 0x20; // PA5 output
	GPIO_PORTA_AFSEL_R &= ~0x20; // not alternative
	GPIO_PORTA_AMSEL_R &= ~0x20; // no analog
	GPIO_PORTA_PCTL_R &= ~0x00F00000; // bits for PA5
	GPIO_PORTA_DEN_R |= 0x20; // enable PA5
}
void PortF_Init(void)
{
	unsigned long volatile delay;
	/*PORT Initialization*/
	SYSCTL_RCGC2_R |= 0x00000020;// Port a clock
	delay = SYSCTL_RCGC2_R; // wait 3-5 bus cycles
	GPIO_PORTF_DIR_R = 0x00; // No output pins
	GPIO_PORTF_AFSEL_R &= ~0xFF;// not alternative
	GPIO_PORTF_AMSEL_R &= ~0xFF; // no analog
	GPIO_PORTF_PCTL_R = 0x00000000;//PCTL GPIO on PF4-0
	GPIO_PORTF_PUR_R=0x11;
	GPIO_PORTF_DEN_R |= 0x11; // enable digital input PF4,PF0
}

void SysLoad(unsigned long period)
{
	NVIC_ST_RELOAD_R = period -1;
	NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears  
	while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag 
		}
}
void SysInit(void)
{
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;// any write to current clears it
	NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R&0x00FFFFFF;// priority 0
	NVIC_ST_CTRL_R = 0x00000005;// enable with core clock and interrupts
}
void SysFun(void)
{
	NVIC_ST_CTRL_R = 0;               // disable SysTick during setup  
	NVIC_ST_CTRL_R = 0x00000005; 
} 
