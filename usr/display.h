/*
 * @Description: the headerfile of the display
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-12-04 18:15:02
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-06 16:31:41
 */
#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#define BUFFERLENTH 32
extern void delay_ms(uint16_t);
extern void showHome(void);
extern void curDisplay(void);
extern void scoreDisplay(void);
extern void screenDisplay(void);
extern uint8_t posTransfer(uint8_t pos);
#endif