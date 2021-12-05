/*
 * @Description: keyboard header file
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-11-28 12:26:11
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-05 20:01:34
 */

#ifndef __KB_BSP__
#define __KB_BSP__

#define KEY_PORT P7
#define KEY_PORT_IN0 P7 .7
#define KEY_PORT_IN1 P7 .6
#define KEY_PORT_IN2 P7 .5
#define KEY_PORT_IN3 P7 .4

void delay(uint8_t t);
void Keyboard_scan(void);
void kb_Init(void); //use the function for initial only, it calls the next port initial function
void kb_PortInit(void);

extern volatile uint8_t num_keyboard;
extern uint8_t array_key[4];
extern uint8_t kb_temp;
extern uint8_t testvalue;

#endif
