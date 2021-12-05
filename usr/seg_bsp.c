/*
 * @Description: eight segment led board support package 
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-11-28 14:19:25
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-05 20:20:50
 */
#include "r_cg_userdefine.h"
volatile uint8_t flag_digital_led;
bit bit_control;

/**
 * @description: SEG PORT Init
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void Seg_Port_Init(void)
{

    P1 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0 |
         _00_Pn5_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn7_OUTPUT_0;
    P5 = _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0 | _00_Pn5_OUTPUT_0;
    PM1 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT |
          _00_PMn4_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT;
    PM5 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT |
          _00_PMn5_MODE_OUTPUT | _C0_PM5_DEFAULT;
}

/**
 * @description: SEG PORT Init
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void Seg_Init(void)
{
    Seg_Port_Init();
}

/**
 * @description: get the display code
 * @param {uint8_t } i
 * @return {*}
 * @author: PengXuanyao
 */
uint8_t Getcode(uint8_t i) /*digital_led segment table ---->"k"*/
{
    uint8_t p;
    switch (i)
    {
    case 0:
        p = 0x3f;
        break; /* 0 */
    case 1:
        p = 0x06;
        break; /* 1 */
    case 2:
        p = 0x5B;
        break; /* 2 */
    case 3:
        p = 0x4F;
        break; /* 3 */
    case 4:
        p = 0x66;
        break; /* 4 */
    case 5:
        p = 0x6D;
        break; /* 5 */
    case 6:
        p = 0x7D;
        break; /* 6 */
    case 7:
        p = 0x07;
        break; /* 7 */
    case 8:
        p = 0x7F;
        break; /* 8 */
    case 9:
        p = 0x6F;
        break; /* 9 */
    case 0x0a:
        p = 0x77;
        break; /* a */
    case 0x0b:
        p = 0x7c;
        break; /* b */
    case 0x0c:
        p = 0x39;
        break; /* c */
    case 0x0d:
        p = 0x5e;
        break; /* d */
    case 0x0e:
        p = 0x79;
        break; /* e */
    case 0x0f:
        p = 0x71;
        break; /* f */
    case 16:
        p = 0x80;
        break; /* . */
    case 17:
        p = 0x73;
        break; /* p */
    case 18:
        p = 0x3e;
        break; /* u */
    case 19:
        p = 0x31;
        break; /* t */
    case 20:
        p = 0x6e;
        break; /* y */
    case 21:
        p = 0xff;
        break; /* 8.*/
    case 22:
        p = 0x00;
        break; /*close*/
    default:
        break;
    }
    return (p);
}

/**
 * @description: Display the number
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void display(void)
{
    static uint8_t count = 0;
    array_key[0] = num_keyboard % 10; //the second char
    array_key[1] = num_keyboard / 10; //the front char
    if (count < 2)
    {
        if (count == 0)
            bit_control = 1; //from bit4 to bit1
        if (count == 1)
            bit_control = 0;
        DIGTAL_LED_D4 = ~bit_control;
        DIGTAL_LED_D3 = ~bit_control;

        DIGTAL_PORT = Getcode(array_key[count]);

        DIGTAL_LED_D4 = bit_control;
        DIGTAL_LED_D3 = ~bit_control;
        delay(1000);
        count++;
    }
    else
    {
        count = 0;
    }
}
/**
 * @description: show the high(first 2 seg) and low(last 2 seg) number
 * @param {uint8_t} numh
 * @param {uint8_t} numl
 * @return {*}
 * @author: PengXuanyao
 */
void displayNum(uint8_t numh, uint8_t numl)
{
    static uint8_t count = 0;
    array_key[0] = numh / 10; //the second char
    array_key[1] = numh % 10; //the first char
    array_key[2] = numl / 10; //the thrid char
    array_key[3] = numl % 10; //the last char
    switch (count)
    {
    case 0:
        DIGTAL_PORT = Getcode(array_key[count]);
        DIGTAL_LED_ALL_0FF();
        DIGTAL_LED_D1_ON();
        break;
    case 1:
        DIGTAL_PORT = Getcode(array_key[count]);
        DIGTAL_LED_ALL_0FF();
        DIGTAL_LED_D2_ON();
        break;
    case 2:
        DIGTAL_PORT = Getcode(array_key[count]);
        DIGTAL_LED_ALL_0FF();
        DIGTAL_LED_D3_ON();
        break;
    case 3:
        DIGTAL_PORT = Getcode(array_key[count]);
        DIGTAL_LED_ALL_0FF();
        DIGTAL_LED_D4_ON();
        break;
    default:
        break;
    }
    count = (count + 1) % 4;
}