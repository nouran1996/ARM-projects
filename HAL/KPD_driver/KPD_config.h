/***************************************************/
/******************  Author:  Nouran ***********/
/******************  Layer:	  HAL		 ***********/
/******************	 SWC:	  KEYPAD       ***********/
/******************  Version: 1.00       ***********/
/***************************************************/
/***************************************************/

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_u8_COL_PORT         DIO_U8_PORTC
#define KPD_u8_ROW_PORT         DIO_U8_PORTC

/*(output + high) pins*/
#define KPD_u8_COL1_PIN         DIO_U8_PIN0
#define KPD_u8_COL2_PIN         DIO_U8_PIN1
#define KPD_u8_COL3_PIN         DIO_U8_PIN2
#define KPD_u8_COL4_PIN         DIO_U8_PIN3

/*input pull up (input + high)*/
#define KPD_u8_ROW1_PIN         DIO_U8_PIN4
#define KPD_u8_ROW2_PIN         DIO_U8_PIN5
#define KPD_u8_ROW3_PIN         DIO_U8_PIN6
#define KPD_u8_ROW4_PIN         DIO_U8_PIN7

#define KPD_u8_KEY_VAL       {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'c','0','=','+'}}
//#define KPD_u8_KEY_VAL			{{7,8,9,47},{4,5,6,42},{1,2,3,45},{100,0,61,43}}


#define KPD_u8_NO_PRESSED_KEY     0xFF


#endif
