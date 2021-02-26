/***************************************************/
/***************************************************/
/******************  Author:  Mona Elroh ***********/
/******************  Layer:	  HAL		 ***********/
/******************	 SWC:	  KEYPAD       ***********/
/******************  Version: 1.00       ***********/
/***************************************************/
/***************************************************/


#include "STD_TYPES.h"

#include"GPIO_interface.h"

#include "KPD_config.h"
#include "KPD_private.h"
#include "KPD_interface.h"


u8 KPD_u8GetPressedkey(void)
{
	u8 Local_u8PressdKey= KPD_u8_NO_PRESSED_KEY;
	u8 Local_u8PinState;

	/*static in order not to be reserved in the stack to avoid stack overflow*/
	static u8 Local_u8KPD_Arr[ROW_NUMBER][COL_NUMBER]=KPD_u8_KEY_VAL;

	u8 Local_u8RowIdx,Local_u8ColIdx;

	static u8 Local_u8ColArr[COL_NUMBER]={KPD_u8_COL1_PIN,KPD_u8_COL2_PIN,KPD_u8_COL3_PIN,KPD_u8_COL4_PIN};
	static u8 Local_u8ROWArr[COL_NUMBER]={KPD_u8_ROW1_PIN,KPD_u8_ROW2_PIN,KPD_u8_ROW3_PIN,KPD_u8_ROW4_PIN};

	/*Loop on the columns of the keypad*/
	for(Local_u8ColIdx=0;Local_u8ColIdx<COL_NUMBER;Local_u8ColIdx++)
	{
		/*Activate the current column*/
		DIO_voidSetPinValue(KPD_u8_COL_PORT,Local_u8ColArr[Local_u8ColIdx],DIO_U8_LOW);

		/*Loop on the rows of the keypad*/
		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUMBER;Local_u8RowIdx++)
		{
			/*Read the current row*/
			DIO_voidSetPinValue(KPD_u8_ROW_PORT,Local_u8ROWArr[Local_u8RowIdx],&Local_u8PinState);

			/*check the pin state*/
			if(DIO_U8_LOW == Local_u8PinState)
			{
				/*Get the value of pressed key*/
				Local_u8PressdKey = Local_u8KPD_Arr[Local_u8RowIdx][Local_u8ColIdx];

				/*wait (polling with blocking) until the key is released*/
				while(DIO_U8_LOW == Local_u8PinState)
				{
					DIO_voidSetPinValue(KPD_u8_ROW_PORT,Local_u8ROWArr[Local_u8RowIdx],&Local_u8PinState);
				}

				/*return the pressed key*/
				return Local_u8PressdKey;

			}
		}

		/*Deactivate the Current Column*/
		DIO_voidSetPinValue(KPD_u8_COL_PORT,Local_u8ColArr[Local_u8ColIdx],DIO_U8_HIGH);
	}
	return Local_u8PressdKey;

}
