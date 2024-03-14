//FUNCIONES PRINCIPALES DEL PROYECTO DEL ROMPECABEZAS-2D

//BIBLIOTECA UART
//CONSTANTES PARA CARACTERES ASCII-Z
#define LF 10 // Nueva línea
#define FF 12 // Nueva página
#define CR 13 // Retorno de carro

//*****************************************************************
void ConfigUART0(void);
//CONFIGURA EL UART0 A UNA VELOCIDAD DE 38400 bps
//Transmite 8 bits, 1 bit de parada, paridad par y FIFOS habilitados
//ENTRADA: 	NINGUNA
//SALIDA: 	NINGUNA
//*****************************************************************
void SiguienteLinea(void);

//FUNCION QUE PARA POSICIONAR EL CURSOR AL INICIO DE LA SIGUIENTE LINEA
//ENTRADA: 	NINGUNA
//SALIDA:		NINGUNA
//*****************************************************************
void TxCar(uint8_t Car);
//Funcion que se encarga de transmitir un caracter
//ENTRADA:	Caracter recibido "Car"
//SALIDA:		NINGUNA
//*****************************************************************
uint8_t RxCar(void);
//FUNCION QUE SE ENCARGA DE ESPERAR HASTA RECIBIR UN CARACTER
//ENTRADA:	NINGUNA
//SALIDA:		NINGUNA
//*****************************************************************
uint8_t HayCarRx(void);
//FUNCIONE QUE VERIFICA EL ESTADO DE LA PILA DE RECEPCION
//ENTRADA: 	NINGUNA
//SALIDA:		si es "0" -> PILA VACIA
//					si es "1" -> HAY UN CARACTER RECIBIDO
//*****************************************************************
void TxCadena(uint8_t Cadena[]);
//FUNCION QUE TRANSMITE UNA CADENA ASCII-Z
//ENTRADA:	cadena recibida "Cadena[]"
//SALIDA:		NINGUNA
//*****************************************************************
void UART_TransmiteDig(uint32_t numero);
//FUNCION QUE SE ENCARGA DE TRANSMITIR UN NUMERO
//ENTRADA: 	numero que se desea transmitir "numero"
//SALIDA:		NINGUNA
//*****************************************************************

