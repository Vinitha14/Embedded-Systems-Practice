#include <TM4C123.h>
#define GREEN (1U<<3)

void delay(int time);

int main(void){
		SYSCTL->RCGCGPIO=0x20;
	  GPIOF->DIR=GREEN;
		GPIOF->DEN=GREEN;
	
	while(1){
		GPIOF->DATA^=GREEN;
		delay(50000000);
	}
	
}
void delay(int time){
	int i*1;
	while(i<time)
	{
		i++;
	}
}