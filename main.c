/****************************************************************************/
/****************************************************************************/
/*****              PONTIFICIA UNIVERSIDAD CATÓLICA DEL PERÚ            *****/
/*****                  FACULTAD DE CIENCIAS E INGENIERÍA               *****/
/*****                      SISTEMAS DIGITALES                          *****/
/****************************************************************************/
/*****          Proyecto:           PUZZLE_2D											      *****/
/****************************************************************************/
/*****          Microcontrolador:   TM4C123GH6PM                        *****/
/*****          EvalBoard:       Tiva C Series TM4C123G LaunchPad       *****/
/*****          Autores:         Franco Teodoro Vela      			   			*****/
/*****          					       Pedro Jacinto Calderon               	*****/
/*****          Asesor:					 Luis Gonzales               				    *****/
/*****          Fecha:              15-12-2020		                      *****/
/****************************************************************************/
/*****          Estado:         LISTO PARA EL FUNCIONAMIENTO            *****/
/****************************************************************************/
/****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "tm4c123gh6pm.h"
#include "Nokia5110.h"
#include "BibliotecaUART.h"
#include "BibliotecaTIVA.h"
#include "bitmapPhotos.h"
/*****************************************************************************
Defininimos variables que manejan 
los graficos de la pantalla nokia*/
/****************************************************************************/

uint8_t ActualizarPantalla;
uint8_t contActualizarPantalla=0;

/*****************************************************************************
Declaramos las funciones empleadas */
/****************************************************************************/
void PortF_Init(void);
void ConfiguraSysTick(void);
void SysTick_Handler(void);
void config_portF(void);

void ConfiguraSysTick(void){        // Temporiza 1mseg, Fclksys=16MHz   
    NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE;
    NVIC_ST_RELOAD_R = (NVIC_ST_RELOAD_R&0xFF000000)|0x00003E7F;//16000-1
    NVIC_ST_CURRENT_R &= ~(0x00FFFFFF);
    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_ENABLE;
}

void SysTick_Handler(void){
		// Actualizar la pantalla cada 80ms
		if(++contActualizarPantalla>79){
			contActualizarPantalla=0;
			ActualizarPantalla=1;
		}
}

int comparar( int arreglo1[] ,int arreglo2[]){			//Funcion que retorna V si los
                                                    //elementos del arreglo son iguales
		for ( int i = 0; i < 9; i++){                   //o F sin son diferentes
			int valorarr1 = arreglo1[i];
			int valorarr2 = arreglo2[i];
		if ( valorarr1 != valorarr2	) 
		{
			return 0;
		}
	}
	return 1;
}	
int main(void)
{
    // Inicializacion
    Nokia5110_Init();
    Nokia5110_ClearBuffer();
    ConfiguraSysTick(); 
    ConfigUART0();
	  config_portF(); 
    
    uint8_t Columnas[3] = {0,15,30};
    uint8_t Filas[3]    = {13,28,43} ;
    
		char c;     
    int temp;
    const unsigned char *numeros[10];
    
		numeros[0] = NUM1;
    numeros[1] = NUM2;
    numeros[2] = NUM3;
    numeros[3] = NUM4;
    numeros[4] = NUM5;
    numeros[5] = NUM6;
    numeros[6] = NUM7;
    numeros[7] = NUM8;
    numeros[8] = VACIO;
    TxCadena((uint8_t *) "Proyecto Sistemas Digitales" );
    TxCadena((uint8_t *)"\r\n" );
    TxCadena((uint8_t *)"PUZZLE 2D" );
    TxCadena((uint8_t *)"\r\n" );
		TxCadena((uint8_t *)"PRESIONE CUALQUIER TECLA PARA COMENZAR :3" );
    
		int j ;
		int x;
		
		int ordenado[9]     = {0,1,2,3,4,5,6,7,8};
    int tabla[9]        = {0,1,2,3,4,5,6,7,8};
		int indicealeatorio = 0;
		int indiceoriginal  = 0;
   // espera un caracter para iniciar el juego 
		uint32_t aux;
		while( !HayCarRx() ) aux++; 
		srand(aux);
		
		while(indicealeatorio<9)
		{		
				
			indiceoriginal= rand();
			indiceoriginal= indiceoriginal%9;
			if(ordenado[indiceoriginal]!=-1)
			{
				tabla[indicealeatorio]   = ordenado[indiceoriginal];
				ordenado[indiceoriginal] = -1;
				if(tabla[indicealeatorio]== 8) j = indicealeatorio;
				indicealeatorio++;
				
			}
		}
	  for(indicealeatorio=0;indicealeatorio<9;indicealeatorio++)ordenado[indicealeatorio] = indicealeatorio;
			

		while(1){

			// Realiza el refresco de la pantall Nokia
        if(ActualizarPantalla == 1){
            Nokia5110_ClearBuffer();
            ActualizarPantalla=0;						
					
            Nokia5110_PrintBMP(Columnas[0], Filas[0] ,numeros[tabla[0]], 5); 
            Nokia5110_PrintBMP(Columnas[1], Filas[0], numeros[tabla[1]], 5);
            Nokia5110_PrintBMP(Columnas[2], Filas[0], numeros[tabla[2]], 5);
            Nokia5110_PrintBMP(Columnas[0], Filas[1], numeros[tabla[3]], 5);    
            Nokia5110_PrintBMP(Columnas[1], Filas[1], numeros[tabla[4]], 5);
            Nokia5110_PrintBMP(Columnas[2], Filas[1], numeros[tabla[5]], 5);
            Nokia5110_PrintBMP(Columnas[0], Filas[2], numeros[tabla[6]], 5);
            Nokia5110_PrintBMP(Columnas[1], Filas[2], numeros[tabla[7]], 5);
            Nokia5110_PrintBMP(Columnas[2], Filas[2], numeros[tabla[8]], 5); 
					  Nokia5110_DisplayBuffer();
			  }
						// Imprime "PUZZLE 2D" en la pantalla
					  Nokia5110_SetCursor(8,0);
	          Nokia5110_OutString("P");
    				Nokia5110_SetCursor(8,1);
	          Nokia5110_OutString("U");				
    				Nokia5110_SetCursor(8,2);
	          Nokia5110_OutString("Z");						
    				Nokia5110_SetCursor(8,3);
	          Nokia5110_OutString("Z");
    				Nokia5110_SetCursor(8,4);
	          Nokia5110_OutString("L");
    				Nokia5110_SetCursor(8,5);
	          Nokia5110_OutString("E");	
						Nokia5110_SetCursor(10,2);
						Nokia5110_OutString("2D");

        if( HayCarRx() )
        {
            switch( c =RxCar() )
            {
            case 'D':
                if ( j != 0 && j != 3 && j != 6)
                {   
                    TxCadena((uint8_t *) "->" );
                    TxCar(c);
                    temp = tabla[j];
                    tabla[j] = tabla[j-1];
                    tabla[j-1] = temp;
										x = j;
                    j--;
                }   
                else  
                {
										x = j;
                    TxCadena((uint8_t *) "Caracter Invalido:" );
                    TxCar(c);
                }
                break;

            case 'A':
                if ( j != 2 && j != 5 && j != 8)
                {
                    TxCadena( (uint8_t *)"->" );
                    TxCar(c);
                    temp = tabla[j];
                    tabla[j] = tabla[j+1];
                    tabla[j+1] = temp;
										x = j;
                    j++;
                }
                else
								{
										x = j;
                    TxCadena((uint8_t *) "Caracter Invalido:" );
                    TxCar(c);
                }
								break;
            case 'W':
                if ( j != 6 && j != 7 && j != 8)
                {
                    TxCadena((uint8_t *) "->" );
                    TxCar(c);
                    temp = tabla[j];
                    tabla[j] = tabla[j+3];
                    tabla[j+3] = temp;
										x = j;
                    j= j+3;
                }
                else
                {
										x = j;
                    TxCadena((uint8_t *) "Caracter Invalido:" );
                    TxCar(c);
                }

                break;

            case 'S':
                if ( j != 0 && j != 1 && j != 2)
                {
                    TxCadena((uint8_t *) "->" );
                    TxCar(c);
                    temp = tabla[j];
                    tabla[j] = tabla[j-3];
                    tabla[j-3] = temp;
										x = j;
                    j=j-3;
                }
                else
                {
										x = j;
                    TxCadena((uint8_t *) "Caracter Invalido:" );
                    TxCar(c);
                }
                break;
						
            }
						
            TxCadena((uint8_t *) "\r\n" );

						if ( x != j)
						{
							parpadeorojo();
						}
        }
				
			if( comparar(ordenado, tabla) == 1)
			{
				prendeverde();
			}
			else 
			apagaled();
    }

}       

