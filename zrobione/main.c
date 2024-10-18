#include <LPC21xx.H>
#include <math.h>

#define CS (1<<10)
#define SPIF (1<<7)
#define MASTER_MODE      (1<<5)
#define MULTIPLIER_X1    (1<<5)
#define OUTPUT_POWER_ON  (1<<4)


void Delay(int iTimeInMs){
	int iCycle ;
	int iNumberOfCycles = 10000 * iTimeInMs ;
	
	for (iCycle = 0; iCycle < iNumberOfCycles; iCycle++) {}
}

 void DAC_MCP4921_Set(unsigned int uiVoltage){
  PINSEL0 = 0x5500; 
	IO0DIR |= CS;
  S0SPCR = MASTER_MODE; 
 
  VPBDIV = 0x1; 
  S0SPCCR = 0x8; 
 
	IO0CLR = CS;	
	 
	S0SPDR = MULTIPLIER_X1 | OUTPUT_POWER_ON | (( uiVoltage & 0xF00 ) >> 8);
	 
  S0SPSR &= !SPIF;
  while(!(S0SPSR & SPIF)){}; 

	S0SPDR = uiVoltage & 0x0FF ;
	S0SPSR &= !SPIF;
	while(!(S0SPSR & SPIF)){}; 

	IO0SET = CS;
		
 };
 

 void DAC_MCP4921_Set_mV(unsigned int uiVoltage){
	 DAC_MCP4921_Set((uiVoltage*4096)/3300);
 }
 
 // czas jednego okresu sinusa 4.2 przedzialki przy skali 5ms 4.2 * 5ms = 21ms
 
 void DAC_MCP4921_Sinus(void){
	 unsigned int uiIterator;
	 for(uiIterator = 0; uiIterator < 360; uiIterator++){
		DAC_MCP4921_Set_mV(sin((uiIterator * 3.14) / 180)*1000 + 1000) ;
	 }
 };
 
 
 int main(){
	 while(1){
		 DAC_MCP4921_Sinus();
	 }; 
 };
 