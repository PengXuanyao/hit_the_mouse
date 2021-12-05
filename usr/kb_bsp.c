/*
 * @Description: key board board support pakage
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-11-28 12:24:49
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-05 19:59:33
 */
#include "r_cg_userdefine.h"

volatile uint8_t num_keyboard;
uint8_t array_key[4];
uint8_t kb_temp = 0;
uint8_t testvalue;

/**
 * @description: delay
 * @param {uint8_t} t
 * @return {*}
 * @author: PengXuanyao
 */
void delay(uint8_t t)
{
    for (; t > 0; t--)
        ;
    for (; t > 0; t--)
        ;
}

/**
 * @description: initial the port
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void kb_PortInit(void)
{
    P7 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
    PU7 = _10_PUn4_PULLUP_ON | _20_PUn5_PULLUP_ON | _40_PUn6_PULLUP_ON | _80_PUn7_PULLUP_ON;
    PM7 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT |
          _10_PMn4_MODE_INPUT | _20_PMn5_MODE_INPUT | _40_PMn6_MODE_INPUT | _80_PMn7_MODE_INPUT;
}

/**
 * @description: kb port init
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void kb_Init(void)
{
    kb_PortInit();
}

/**
 * @description: Key board scan 
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void Keyboard_scan(void)
{

    KEY_PORT = 0xff;
    P7 .3 = 0;
    kb_temp = KEY_PORT;
    kb_temp = kb_temp & 0xf0; /*check  four  lower  bits*/
    if (kb_temp != 0xf0)      /*first check*/
    {
        delay(100); /*delay some time*/
        kb_temp = KEY_PORT;
        kb_temp = kb_temp & 0xf0; /*check  four  lower  bits*/
        if (kb_temp != 0xf0)      /*second check*/
        {
            kb_temp = KEY_PORT;
            kb_temp = kb_temp & 0xf0;
            switch (kb_temp)
            {
            case 0xe0:
                num_keyboard = 1;
                break;
            case 0xd0:
                num_keyboard = 5;
                break;
            case 0xb0:
                num_keyboard = 9;
                break;
            case 0x70:
                num_keyboard = 13;
                break;
            }
        }
        testvalue = num_keyboard;
    }

    KEY_PORT = 0xff; /*as above*/
    P7 .2 = 0;
    kb_temp = KEY_PORT;
    kb_temp = kb_temp & 0xf0;
    if (kb_temp != 0xf0)
    {
        delay(100);
        kb_temp = KEY_PORT;
        kb_temp = kb_temp & 0xf0;
        if (kb_temp != 0xf0)
        {
            kb_temp = KEY_PORT;
            kb_temp = kb_temp & 0xf0;
            switch (kb_temp)
            {
            case 0xe0:
                num_keyboard = 2;
                break;
            case 0xd0:
                num_keyboard = 6;
                break;
            case 0xb0:
                num_keyboard = 10;
                break;
            case 0x70:
                num_keyboard = 14;
                break;
            }
        }
    }

    KEY_PORT = 0xff; /*as above*/
    P7 .1 = 0;
    kb_temp = KEY_PORT;
    kb_temp = kb_temp & 0xf0;
    if (kb_temp != 0xf0)
    {
        delay(100);
        kb_temp = KEY_PORT;
        kb_temp = kb_temp & 0xf0;
        if (kb_temp != 0xf0)
        {
            kb_temp = KEY_PORT;
            kb_temp = kb_temp & 0xf0;
            switch (kb_temp)
            {
            case 0xe0:
                num_keyboard = 3;
                break;
            case 0xd0:
                num_keyboard = 7;
                break;
            case 0xb0:
                num_keyboard = 11;
                break;
            case 0x70:
                num_keyboard = 15;
                break;
            }
        }
    }

    KEY_PORT = 0xff; /*as above*/
    P7 .0 = 0;
    kb_temp = KEY_PORT;
    kb_temp = kb_temp & 0xf0;
    if (kb_temp != 0xf0)
    {
        delay(100);
        kb_temp = KEY_PORT;
        kb_temp = kb_temp & 0xf0;
        if (kb_temp != 0xf0)
        {
            kb_temp = KEY_PORT;
            kb_temp = kb_temp & 0xf0;
            switch (kb_temp)
            {
            case 0xe0:
                num_keyboard = 4;
                break;
            case 0xd0:
                num_keyboard = 8;
                break;
            case 0xb0:
                num_keyboard = 12;
                break;
            case 0x70:
                num_keyboard = 16;
                break;
            }
        }
    }
}