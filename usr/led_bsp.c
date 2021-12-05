/*
 * @Description:  led board support package
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-11-27 20:43:42
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-11-27 22:28:54
 */
#include "r_cg_userdefine.h"

/**
 * @description: let the led blink on a row
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void LED_Flowing(void)
{
	static unsigned char flag = 0;
	switch (flag)
	{
	case 0:
		P4 .1 = 0;
		P4 .2 = 1;
		P4 .3 = 1;
		break;
	case 1:
		P4 .1 = 1;
		P4 .2 = 0;
		P4 .3 = 1;
		break;
	case 2:
		P4 .1 = 1;
		P4 .2 = 1;
		P4 .3 = 0;
		break;
	default:
		break;
	}
	flag = (flag + 1) % 3;
}

/**
 * @description: initial the P4.1 P4.2 P4.3
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void LED_Port_Init(void)
{
	P4 = _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
	PM4 = _01_PMn0_NOT_USE | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM4_DEFAULT;
}

/**
 * @description: LED Init turn off three led
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void LED_Init(void)
{
	LED_Port_Init();
	LED_ALL_ON();
}
