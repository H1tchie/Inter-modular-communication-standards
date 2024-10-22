#include <LPC21xx.H>
#include <math.h>

#define CS (1<<10)
#define SPIF (1<<7)
#define MASTER_MODE      (1<<5)
#define MULTIPLIER_X1    (1<<5)
#define OUTPUT_POWER_ON  (1<<4)

unsigned int Sin_LUT[360];

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
	 
  while(!(S0SPSR & SPIF)){}; 

	S0SPDR = uiVoltage & 0x0FF ;

	while(!(S0SPSR & SPIF)){}; 

	IO0SET = CS;
		
 };
 

 void DAC_MCP4921_Set_mV(unsigned int uiVoltage){
	 DAC_MCP4921_Set((uiVoltage*4096)/3300);
 }
 
 
 void DAC_MCP4921_Sinus(void){
	 unsigned int uiPhase;
	 for(uiPhase = 0; uiPhase < 360; uiPhase++){
		DAC_MCP4921_Set_mV(sin((uiPhase * 3.14) / 180)*1000 + 1000) ;
	 }
 };
 
 
void DAC_MCP4921_Sinus_fast(void){
	 unsigned int uiPhase;
	 for(uiPhase = 0; uiPhase < 360; uiPhase++){
		DAC_MCP4921_Set_mV(Sin_LUT[uiPhase]) ;
	 }
 };
 
 
 void Create_Sin_LUT(void){
	 
unsigned int uiPhase;

for(uiPhase = 0; uiPhase < 360; uiPhase++){
	Sin_LUT[uiPhase]=(sin((uiPhase * 3.14) / 180)*1000 + 1000) ;
}	 
 }
 
 
 int main(){

	Create_Sin_LUT();
	 while(1){
		 DAC_MCP4921_Sinus_fast();
	 }; 
 };
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 
 
