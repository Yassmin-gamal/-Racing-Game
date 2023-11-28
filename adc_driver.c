
#include "../TM4C123GH6PM.h"
#include "tm4c123gh6pm11.h"

#include "../driver/gpio.h"
#include "adc_driver.h"

ADC0_Type* ADC0_CFGS= (ADC0_Type *)  ADC0_BASE;
#define SYSCTL_RCGCADC_R        (*((volatile unsigned long *)0x400FE638))
	#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))
#define NVIC_EN1_R              (*((volatile unsigned long *)0xE000E104))
	
extern GPIOA_Type * GPIO_PORTS_REGS [6];
extern int adcData;
void ADCInit(sample_sequencer seq,emux_selector emux_sel, ssmux_selector seqmux_sel  ){

  //Enable the ADC clock using the RCGCADC register 
   SYSCTL_RCGCADC_R |= (UP<<0);//Enable ADC module 0

  //Enable analog functionality for used port
	GPIO_PORTS_REGS[GPIO_PORT_E]->AMSEL |= (1<<1);
	
	//Sample Sequencer is disabled
	ADC0_CFGS->ACTSS |= seq;
	
	//Sample Sequencer running mode
	ADC0_CFGS->EMUX |= emux_sel;
	//Sample Sequencer reads from AINn
	
	ADC0_CFGS->SSMUX3 |= seqmux_sel;
	//End bit (1) must be set and bit 2 to enable interrupt for Sample Sequencer 

	ADC0_CFGS->SSCTL3 |= ( UP<<1) | (UP <<2);
	//Enable interrupt mask for Sample Sequencer 

	ADC0_CFGS->IM |=( UP << seq);
	//Clear interrupt status for Sample Sequencer 

	ADC0_CFGS->RIS |=( UP << seq);
	//Sample Sequencer is enabled

	ADC0_CFGS->ACTSS |=( UP << seq);
	
	//Enable IRQ for ADC0SSn
   if (seq == 0 || seq== 1){
    NVIC_EN0_R|=(1<< (30+seq));
	 }else{
		 NVIC_EN1_R|=(1<<(seq-2));
	 }
}
