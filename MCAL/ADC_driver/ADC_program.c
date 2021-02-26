/*
 * ADC_program.c
 *
 *  Created on: Feb 12, 2021
 *      Author: Nouran
 */

#include "StdTypes.h"
#include "Utils.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"


void ADC_voidInit(void)
{

	/*   Enable ADC first time  (Continues) */
	ADC->CR2 =0x0003;

	/*   Enable ADC second time   */
	/*ADON bit is set and cleared by software. If ADON bit holds a value of zero and a 1 is written to it
      then it wakes up the ADC from Power Down state.
      Conversion starts when ADON bit holds a value of 1 and a 1 is written to it.*/
	ADC -> CR2 = 0x0003;

	/*   ON calibration          */
	ADC -> CR2 = 0x0007;

}

#if (NUMBER_OFCHANNELS == 1)

u16 ADC_u16Read(u8 Copy_u8Channel)
{
	u16 Local_u16Read=0;

	/*   Select Channel for sequence             */
	ADC -> SQR3 = Copy_u8Channel;

	/*   Configure Sampling rate for Channel     */
	ADC->  SMPR2 = 0b111 << (Copy_u8Channel*3);

	/*   Start Conversion on regular channel     */
	SET_BIT(ADC -> CR2, 22);

	/*   Polling on status register      EOC     */
	while(!GET_BIT(ADC -> SR , 1));

	/*   READ                                    */
	Local_u16Read= ADC -> DR;

	return Local_u16Read;
}

#elif (NUMBER_OFCHANNELS == 2)

void ADC_u16ReadTwoChannels(u16* Copy_u8Channel1, u16* Copy_u8Channel2)
{
	/*       Select Channel for sequence           */
	ADC -> SQR3 = (*Copy_u8Channel1) | (*Copy_u8Channel2 << 5) ;

	/*       Configure Sampling rate for Channel   */
	ADC->  SMPR2 = (0b111) << (*Copy_u8Channel1);
	ADC->  SMPR2 = (0b111) << (*Copy_u8Channel2);

	/*       Choose 2 conversions                  */
	SET_BIT(ADC -> SQR1, 20);

	/*       Start Conversion on regular channel   */
	SET_BIT(ADC -> CR2, 22);

	/*       Polling on status register EOC        */
	while(!GET_BIT(ADC -> SR , 1));

	/*       READ     (By using DMA)                             */
	*Copy_u8Channel1 = ADC -> DR;
	//*Copy_u8Channel2 = ADC -> DR;
}

#endif




