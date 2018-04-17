#include "gpiote.h"
#include "ppi.h"
#include "gpio.h"

int main()
{
	//Setter jordingspinnene som output og logisk lav
	for (int i = 4; i <= 12; i++)
	{
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
	
	//konfigurer pins til gpiotekanaler
	GPIOTE->CONFIG[0] = (17 << 8)|(1)|(2 << 16);
	GPIOTE->CONFIG[1] = (13 << 8)|(3)|(3 << 16)|(0 <<20);
	GPIOTE->CONFIG[2] = (14 << 8)|(3)|(3 << 16)|(0 <<20);
	GPIOTE->CONFIG[3] = (15 << 8)|(3)|(3 << 16)|(0 <<20);

	//initialiserer PPIkanaler

	PPI->CHENSET = (1)|(1 << 1)|(1 << 2);

	PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);

	PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);

	PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);

	while(1);
}