

typedef enum {
	DOWN,
	UP

}ENABLE_DISABLE;

typedef enum{
	 SEQ0,
   SEQ1,
	SEQ2,
	SEQ3
	
}sample_sequencer;

typedef enum{
	PROCESSOR,
	RUNNING= 0xf000
	
}emux_selector;

typedef enum{
  AIN0,
	AIN1,
	AIN2,
	AIN3,
	AIN4,
	AIN5,
	AIN6,
	AIN7,
	AIN8,
	AIN9,
	AIN10,
	AIN11
	
}ssmux_selector;
void ADCInit(sample_sequencer seq,emux_selector emux_sel, ssmux_selector seqmux_sel  );
