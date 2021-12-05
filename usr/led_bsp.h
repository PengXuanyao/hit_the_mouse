/*
 * @Description: LED BSP header
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-11-27 20:43:54
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-11-27 22:25:47
 */
#ifndef __LED_BSP__
#define __LED_BSP__

#define LED_ALL_ON() (P4 &= ~0X0E)
#define LED_ALL_OFF() (P4 |= 0X0E)

#define L1_ON() (P4 &= ~0X02)
#define L1_OFF() (P4 |= 0X02)
#define L1_TOGGLE() (P4 ^= 0X02)

#define L2_ON() (P4 &= ~0X04)
#define L2_OFF() (P4 |= 0X04)
#define L2_TOGGLE() (P4 ^= 0X04)

#define L3_ON() (P4 &= ~0X08)
#define L3_OFF() (P4 |= 0X08)
#define L3_TOGGLE() (P4 ^= 0X08)

void LED_Flowing(void);
void LED_Port_Init(void);
void LED_Init(void);

#endif