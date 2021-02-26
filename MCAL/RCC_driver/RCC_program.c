/*
 * RCC_PROGRAM.c
 *
 *  Created on: Feb 2, 2021
 *      Author: Nouran
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "RCC_INTERFACE.h"
#include "RCC_PRIVATE.h"
#include "RCC_CONFIG.h"

void RCC_voidInit(void)
{
	u32 local_u32TimeOut=0;

#if    CLOCK_TYPE==RCC_HSI
	/* HSI ON*/
	SET_BIT(RCC_CR,0);
	/* IS HSI READY ? */
	while(GET_BIT(RCC_CR,1)==0 && local_u32TimeOut !=10000);
	{local_u32TimeOut++;}

#elif  CLOCK_TYPE==RCC_HSE
	/* HSE ON*/
	SET_BIT(RCC_CR,16);
	/* SYSTEM CLOCK SWITCH*/
	SET_BIT(RCC_CFGR,0);
	CLR_BIT(RCC_CFGR,1);
	/* HSE IS CRYSTAL OR RC*/
#if RCC_PLL_SOURCE == RCC_CRYSTAL
	CLR_BIT(RCC_CR,18);
#elif RCC_PLL_SOURCE == RCC_RC
	SET_BIT(RCC_CR,18);
#endif
	/* IS HSI READY ? */
	while(GET_BIT(RCC_CR,17)==0 && local_u32TimeOut !=10000);
	{local_u32TimeOut++;}

	while(GET_BIT(RCC_CFGR,2)==0 && GET_BIT(RCC_CFGR,3)==1&& local_u32TimeOut !=10000);
	{local_u32TimeOut++;}

#elif	CLOCK_TYPE == RCC_PLL
#if 	PLL_INPUT  == RCC_HSIDIV2
	/* HSI ON*/
	SET_BIT(RCC_CR,0);
	/* IS HSI READY ? */
	while((GET_BIT(RCC_CR,1)==0) && Local_u32TimeOut<10000)
	{
		Local_u32TimeOut++;
	}
	/*input HSI/2	*/
	CLR_BIT(RCC_CFGR,16);

#elif	PLL_INPUT  == RCC_HSE

#if	  RCC_HSE_SOURCE == RCC_CRYSTAL
	CLR_BIT(RCC_CR,18);
#elif RCC_HSE_SOURCE == RCC_RC
	SET_BIT(RCC_CR,18);
#endif
	/* HSE ON*/
	SET_BIT(RCC_CR,16);


	while((GET_BIT(RCC_CR,17)==0) && Local_u32TimeOut < 10000)
	{
		Local_u32TimeOut++;
	}
	Local_u32TimeOut = 0;

	while((GET_BIT(RCC_CFGR,2)==0) &&(GET_BIT(RCC_CFGR,3)==1) && Local_u32TimeOut < 10000)
	{
		Local_u32TimeOut++;
	}
	/*****************************clock security added********************************/
	/*set input of PLL as HSE or HSE/2*/
	SET_BIT(RCC_CFGR,16);
	/*set input of PLL as HSE */
	CLR_BIT(RCC_CFGR,17);

#elif	PLL_INPUT  == RCC_HSE/2
#if	  RCC_HSE_SOURCE == RCC_CRYSTAL
	CLR_BIT(RCC_CR,18);
#elif RCC_HSE_SOURCE == RCC_RC
	SET_BIT(RCC_CR,18);
#endif

	/*HSE ON*/
	SET_BIT(RCC_CR,16);

	while((GET_BIT(RCC_CR,17)==0) && Local_u32TimeOut < 10000)
	{
		Local_u32TimeOut++;
	}
	Local_u32TimeOut = 0;

	while((GET_BIT(RCC_CFGR,2)==0) &&(GET_BIT(RCC_CFGR,3)==1) && Local_u32TimeOut < 10000)
	{
		Local_u32TimeOut++;
	}

	SET_BIT(RCC_CFGR,16);
	SET_BIT(RCC_CFGR,17);


#endif


#if 	PLL_MUL_FACTOR == 1
#elif	PLL_MUL_FACTOR == 2		RCC_CFGR |=(0x0<<18);
#elif	PLL_MUL_FACTOR == 3		RCC_CFGR |=(0x1<<18);
#elif	PLL_MUL_FACTOR == 4		RCC_CFGR |=(0x2<<18);
#elif	PLL_MUL_FACTOR == 5		RCC_CFGR |=(0x3<<18);
#elif	PLL_MUL_FACTOR == 6		RCC_CFGR |=(0x4<<18);
#elif	PLL_MUL_FACTOR == 7		RCC_CFGR |=(0x5<<18);
#elif	PLL_MUL_FACTOR == 8		RCC_CFGR |=(0x6<<18);
#elif	PLL_MUL_FACTOR == 9		RCC_CFGR |=(0x7<<18);
#elif	PLL_MUL_FACTOR == 10	RCC_CFGR |=(0x8<<18);
#elif	PLL_MUL_FACTOR == 11	RCC_CFGR |=(0x9<<18);
#elif	PLL_MUL_FACTOR == 12	RCC_CFGR |=(0xA<<18);
#elif	PLL_MUL_FACTOR == 13	RCC_CFGR |=(0xB<<18);
#elif	PLL_MUL_FACTOR == 14	RCC_CFGR |=(0xC<<18);
#elif	PLL_MUL_FACTOR == 15	RCC_CFGR |=(0xD<<18);
#elif	PLL_MUL_FACTOR == 16	RCC_CFGR |=(0xE<<18);

#endif

	/* PLL ON */
	SET_BIT(RCC_CR,24);
	Local_u32TimeOut = 0;
	/*IS PLL  ready	*/
	while((GET_BIT(RCC_CR,25)==0) && Local_u32TimeOut < 10000)
	{
		Local_u32TimeOut++;
	}
#else 	#error "Value PLL_MUL_FACTOR is not exist "
	CLR_BIT(RCC_CFGR,0);
	SET_BIT(RCC_CFGR,1);

#endif

}
void RCC_voidEnablePeripheralClock(u8 Copy_BusID,u8 Copy_PeralID)
{
	if(Copy_PeralID<32)

	{
		switch(Copy_BusID)
		{
		case RCC_AHB: SET_BIT(RCC_AHBENR,Copy_PeralID); break;
		case RCC_APB1: SET_BIT(RCC_APB1ENR,Copy_PeralID); break;
		case RCC_APB2: SET_BIT(RCC_APB2ENR,Copy_PeralID); break;
		}
	}
	else{/* error */}
}
void RCC_voidDisablePeripheralClock(u8 Copy_BusID,u8 Copy_PeralID)
{
	if(Copy_PeralID<32)

	{
		switch(Copy_BusID)
		{
		case RCC_AHB:  CLR_BIT(RCC_AHBENR,Copy_PeralID); break;
		case RCC_APB1: CLR_BIT(RCC_APB1ENR,Copy_PeralID); break;
		case RCC_APB2: CLR_BIT(RCC_APB2ENR,Copy_PeralID); break;
		}
	}
	else{/* error */}
}
