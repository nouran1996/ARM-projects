/*
 * ADCA_config.h
 *
 *  Created on: Feb 12, 2021
 *      Author: Nouran
 */




#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_voidInit(void);
u16 ADC_u16Read(u8 Copy_u8Channel);
void ADC_u16ReadTwoChannels(u16* Copy_u8Channel1, u16* Copy_u8Channel2);

#define     CHANNEL_0     0
#define     CHANNEL_1     1
#define     CHANNEL_2     2
#define     CHANNEL_3     3
#define     CHANNEL_4     4
#define     CHANNEL_5     5
#define     CHANNEL_6     6
#define     CHANNEL_7     7


#endif /* ADC_INTERFACE_H_ */



