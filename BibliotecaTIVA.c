#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "BibliotecaTIVA.h"


//***************************************************************** 
void config_portF(void) {
	// Activamos la señal de reloj del puerto F
	SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R5;
	// Se espera a que realmente se active
	while( (SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5)==0) {}
	GPIO_PORTF_LOCK_R = 0x4C4F434B; // Desbloquear puerto F
	GPIO_PORTF_CR_R |= 0x01;				//0x1F; // Se habilita del PF0 al PF4

	// Configuraciones de pines de entrada
	// SW1 está conectado al pin PF4 y SW2 al PF0.
	GPIO_PORTF_DIR_R &=~((1<<4)|(1<<0)); 				//~(0x11); // PF4 y PF0 como entrada
	GPIO_PORTF_AFSEL_R &=~((1<<4)|(1<<0));			//~(0x11); // No utilizar funciones alternas
	GPIO_PORTF_PUR_R |= ((1<<4)|(1<<0));				//0x11; // Activar resistencias de pull-up en pines PF4 y PF0
	GPIO_PORTF_DEN_R |= ((1<<4)|(1<<0));				//0x11; // Habilitar pines PF4 y PF0 en funcion digital
	// Configuraciones de pines de salida
	// El LED rojo conectado a PF1, azul a PF2 y verde a PF3.
	GPIO_PORTF_DIR_R |= (1<<1)|(1<<2)|(1<<3);		//0x0E; // Configura los pines PF1, PF2 y PF3 como salida
	GPIO_PORTF_DR8R_R |=(1<<1)|(1<<2)|(1<<3);		//0x0E; // se activa el driver de 8 mA para cada pin.
	GPIO_PORTF_DEN_R |=(1<<1)|(1<<2)|(1<<3); 		//0x0E; // se activa los pines PF1,PF2 y PF3 como salida digital.
	GPIO_PORTF_DATA_R&= ~((1<<1)|(1<<2)|(1<<3));
} 
//***************************************************************** 
void parpadeorojo(void)
{
	GPIO_PORTF_DATA_R |= 0x02; // Parpadeo rojo
	for(int i=0; i<150000; i++);
	GPIO_PORTF_DATA_R &= ~(0x02);

}
//***************************************************************** 
void prendeverde(void)
{
	GPIO_PORTF_DATA_R |= 0x08; // prende verde
}
//***************************************************************** 
void apagaled(void)
{
	GPIO_PORTF_DATA_R &= ~(0x0E); // apaga led
}	
//***************************************************************** 


