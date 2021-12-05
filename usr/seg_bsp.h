/*
 * @Description: segment led board support package
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-11-28 14:17:17
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-05 20:30:20
 */

#ifndef __SEG_BSP__
#define __SEG_BSP__

#define DIGTAL_LED_D1 P5 .2
#define DIGTAL_LED_D2 P5 .3
#define DIGTAL_LED_D3 P5 .4
#define DIGTAL_LED_D4 P5 .5

#define DIGTAL_LED_D1_ON() (P5 |= 0X04)
#define DIGTAL_LED_D2_ON() (P5 |= 0X08)
#define DIGTAL_LED_D3_ON() (P5 |= 0X10)
#define DIGTAL_LED_D4_ON() (P5 |= 0X20)
#define DIGTAL_LED_ALL_ON() (P5 |= 0X3f)
#define DIGTAL_LED_ALL_0FF() (P5 &= ~0X3f)
#define DIGTAL_PORT P1

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* 16-bit timer data register 00 (TDR00) */
#define _3E7F_TAU_TDR00_VALUE (0x3E7FU)
/* Clock divisor for TAU0 channel 0 */
#define _0001_TAU0_CHANNEL0_DIVISOR (0x0001U)

void Seg_Port_Init(void);
void Seg_Init(void);
uint8_t Getcode(uint8_t i);
void display(void);
extern volatile uint8_t flag_digital_led;
extern bit bit_control;
extern void displayNum(uint8_t numh, uint8_t numl);
#endif
