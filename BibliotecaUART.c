//FUNCIONES PARA EL PROYECTO DEL ROMPECABEZAS-2D
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "BibliotecaUART.h"
#include <stdbool.h>

//*****************************************************************
void ConfigUART0(void)
{
    SYSCTL_RCGC1_R |= SYSCTL_SRCR1_UART0; 		//Habilitamos reloj para el UART0
    SYSCTL_RCGC2_R |= SYSCTL_SRCR2_GPIOA; 		//Habilitamos reloj para GPIOD
    UART0_CTL_R &= ~UART_CTL_UARTEN; 					//Se desactiva el UART
    // Velocidad 38400 (Fsysclk = 16MHz)
		UART0_IBRD_R = (UART0_IBRD_R & 0xFFFF0000) | 26;
		UART0_FBRD_R = (UART0_FBRD_R & 0xFFFFFFC0) | 27;
	
		// 8, 1 bits de parada, paridad par, FIFOs habilitados
		UART0_LCRH_R = (UART0_LCRH_R & 0xFFFFFF00) | 0x76;
		// Habilitamos el UART0, recepción y transmisión
		UART0_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
    GPIO_PORTA_DIR_R |= (1<<1); 							//PA1 como salida
    GPIO_PORTA_DIR_R &= ~(1<<0); 							//PA0 como entrada
    GPIO_PORTA_AMSEL_R &= ~((1<<1)|(1<<0)); 	//Deshabilita funciones analógicas
    GPIO_PORTA_AFSEL_R |= ((1<<1)|(1<<0)); 		//Activa función alternativa
    GPIO_PORTA_PCTL_R &= ~((0xF<<(1*4)) | (0xF<<(0*4)));
    GPIO_PORTA_PCTL_R |= ((0x1<<(1*4)) | (0x1<<(0*4))); //U0Rx, U0Tx
    GPIO_PORTA_DEN_R |= ((1<<1)|(1<<0)); 			//Activa funciones digitales
}

//*****************************************************************
void SiguienteLinea(void){
    // Transmitimos nueva línea (LF)
    TxCar(LF);
    // Transmitimos retorno de carro (CR)
    TxCar(CR);
}
//*****************************************************************
void TxCar( uint8_t Car )
{
    while((UART0_FR_R & UART_FR_TXFF) != 0 ) ; //Espera mientras pila llena
    UART0_DR_R = Car;
}
//*****************************************************************
uint8_t RxCar( void )
{
    while((UART0_FR_R & UART_FR_RXFE) != 0 ) ; //Espera mientra pila vacía
    return UART0_DR_R & 0xFF;
}
//*****************************************************************
uint8_t HayCarRx( void )
{
    if ((UART0_FR_R & UART_FR_RXFE) != 0 )
        return 0; 														//pila vacía
    else
        return 1; 														//hay caracter recibido
}
//*****************************************************************
void TxCadena( uint8_t Cadena[] )
{
    uint8_t i;
    for( i = 0; Cadena[i] != '\0'; i++ )
        TxCar( Cadena[i] );
}
//*****************************************************************
void UART_TransmiteDig(uint32_t numero){
    TxCar(numero + '0');
}
//*****************************************************************

