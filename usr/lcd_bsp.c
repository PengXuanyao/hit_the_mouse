/***********************************************************************************************************************
 * File Name    : r_cg_lcd.c
 * Version      : RL78/G13 V 0.01 1503 [23 Jan 2015]
 * Device(s)    : R5F100LG
 * Tool-Chain   : CA78K0R
 * Description  : This file implements main function.
 * Company Name : Getsoon Electronic Co.Ltd , Shanghai.China
 * Creation Date: 2015-1-23
 ***********************************************************************************************************************/
#include "r_cg_userdefine.h"

#define DBUS_BITS 8

#define LCD_EH() (P14 .1 = 1)
#define LCD_EL() (P14 .1 = 0)

#define LCD_RWH() (P14 .7 = 1)
#define LCD_RWL() (P14 .7 = 0)

#define LCD_RSH() (P14 .6 = 1)
#define LCD_RSL() (P14 .6 = 0)

#define LCD_RESTH() (P3 .0 = 1)
#define LCD_RESTL() (P3 .0 = 0)

#define BACKLIGHT_ON() (P13 .0 = 1)
#define BACKLIGHT_OFF() (P13 .0 = 0)

#if DBUS_BITS == 4
#define LCD_WDATA() (P2 = data)
#else
#define LCD_WDATA() (P2 = data)
#endif

#define GET_DB2() (P2 .7)

#define DB2_PIN_OUT() (PM2 = 0x00)

#define DB2_PIN_IN() (PM2 = 0xff)

#define LCD_REST_OUT() (PM3 &= ~0x01)

/**
 * @description: make the lcd port init
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void LCD_PORT_Create(void)
{
    P2 = _00_Pn0_OUTPUT_0 | _00_Pn1_OUTPUT_0 | _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _00_Pn4_OUTPUT_0 |
         _00_Pn5_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn7_OUTPUT_0;
    P13 = _00_Pn0_OUTPUT_0;
    P14 = _00_Pn1_OUTPUT_0 | _00_Pn6_OUTPUT_0 | _00_Pn7_OUTPUT_0;
    PMC14 = _00_PMCn7_DI_ON | _7F_PMC14_DEFAULT;
    ADPC = _01_ADPC_DI_ON;
    PM2 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT |
          _00_PMn4_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT;
    PM14 = _01_PMn0_NOT_USE | _00_PMn1_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn7_MODE_OUTPUT | _3C_PM14_DEFAULT;
    PU4 = _01_PUn0_PULLUP_ON;
}

/**
 * @description: delay
 * @param {unsigned short} val
 * @return {*}
 * @author: PengXuanyao
 */
void lcd_delay(unsigned short val)
{
    unsigned short i;
    while (val--)
        for (i = 0; i < 600; i++)
            ;
}

void shortdel(void)
{
    unsigned char i;
    for (i = 0; i < 10; i++)
        ;
}

unsigned char lcd_busy(void) //return value ==0,is idle ,==1,is busy status
{
    unsigned char ret = 0;
    DB2_PIN_IN();
    LCD_RSL();
    shortdel();
    LCD_RWH();
    shortdel();
    LCD_EH();
    shortdel();

    if (GET_DB2())
        ret = 1;

    LCD_EL();
    shortdel();
    DB2_PIN_OUT();
    return ret;
}

void lcd_write(unsigned char data, unsigned char op)
{
    unsigned char i;
    while (lcd_busy())
        ; //==1,as busy
    //lcd_delay(1);
    shortdel();
    if (op == 0)
    {
        LCD_RSL();
        shortdel();
    }
    else
    { //if operation status is  busy,and set run status
        LCD_RSH();
        shortdel();
    }
    LCD_RWL();
    LCD_EL();
    shortdel();
#if DBUS_BITS == 4 //if current transismission mode serial ,and ...., as parrall mode
    for (i = 0; i < 2; i++)
    {
#endif
        LCD_WDATA(data);
        shortdel();
        LCD_EH();
        shortdel();
        LCD_EL();
#if DBUS_BITS == 4
        data <<= 4;
    }
#endif
}

void WriteStr(unsigned char *s)
{
    while (*s > 0)
    {
        lcd_write(*s, 1);
        s++;
    }
}

void lcd_init(void)
{
    LCD_PORT_Create();
    LCD_REST_OUT();
    LCD_RESTL();
    lcd_delay(50);
    LCD_RESTH();
    lcd_delay(50);
    BACKLIGHT_ON();
    lcd_delay(5);
#if DBUS_BITS == 4
    lcd_write(0x28, 0);
    lcd_delay(5);
    LCD_EH();
    shortdel();
    LCD_EL();
    lcd_delay(5);
    lcd_write(0x28, 0);
#else
    lcd_write(0x38, 0);
#endif
    lcd_write(0x0C, 0);
    lcd_write(0x01, 0); // Turn on LCD and Cursor
    lcd_write(0x02, 0); // Turn on LCD and Cursor
    lcd_write(0x06, 0); // Entry Mode Set
}

void CursorSet(unsigned char pos)
{
    if (pos > 63)
        return;
    if (pos < 16)
        lcd_write(0x80 + pos, 0);
    else if (pos < 32)
        lcd_write(0x90 + pos - 16, 0);
    else if (pos < 48)
        lcd_write(0x88 + pos - 32, 0);
    else if (pos < 64)
        lcd_write(0x98 + pos - 48, 0);
}
/*
pos  16*4=64   �ܹ�������ʾ64 ���ַ�
��һ�У� 0~15
�ڶ���:  16~31
������:  32~47
������:  48~63
pos  ��4bit   ����
     ��4bit   ����
ע�� ����ռ�����ַ�����������ż��λ��ʼ��������ʾ����
*/
void lcd_display(unsigned char pos, char *str)
{
    unsigned char *p, *p1;
    unsigned char i, lenth;
    if (pos > 63)
        return;
    p = p1 = (unsigned char *)str;
    lenth = 0;
    while (*p1)
    {
        lenth++;
        p1++;
        if (lenth >= 64 - pos)
            break;
    }
    if ((pos % 16) != 0)
        CursorSet(pos);
    for (i = pos; i - pos < lenth; i++)
    {
        if (i == 0)
            lcd_write(0x80, 0);
        else if (i == 16)
            lcd_write(0x90, 0);
        else if (i == 32)
            lcd_write(0x88, 0);
        else if (i == 48)
            lcd_write(0x98, 0);
        lcd_write(*p++, 1);
    }
}

void LcdFill_Vertical()
{
    unsigned char x, y, ii;
#if DBUS_BITS == 4
    lcd_write(0x26, 0); //����ָ�� ��ͼ��ʾ
#else
    lcd_write(0x36, 0); //����ָ�� ��ͼ��ʾ
#endif
    for (ii = 0; ii < 9; ii += 8)
        for (y = 0; y < 0x20; y++)
            for (x = 0; x < 8; x++)
            {
                lcd_write(y + 0x80, 0);      //�е�ַ
                lcd_write(x + 0x80 + ii, 0); //�е�ַ
                lcd_write(0xCC, 1);          //д���� D15��D8
                lcd_write(0xCC, 1);          //д���� D7��D0
            }
#if DBUS_BITS == 4
    lcd_write(0x20, 0);
#else
    lcd_write(0x30, 0);
#endif
}
void LcdFill_Level()
{
    unsigned char x, y, ii;
    unsigned char k;
#if DBUS_BITS == 4
    lcd_write(0x26, 0); //����ָ�� ��ͼ��ʾ
#else
    lcd_write(0x36, 0); //����ָ�� ��ͼ��ʾ
#endif
    for (ii = 0; ii < 9; ii += 8)
        for (y = 0; y < 0x20; y++)
        {
            if (((y % 4) == 0) || ((y % 4) == 1))
                k = 0xff;
            else
                k = 0;
            for (x = 0; x < 8; x++)
            {

                lcd_write(y + 0x80, 0);      //�е�ַ
                lcd_write(x + 0x80 + ii, 0); //�е�ַ
                lcd_write(k, 1);
                lcd_write(k, 1);
            }
        }
#if DBUS_BITS == 4
    lcd_write(0x20, 0);
#else
    lcd_write(0x30, 0);
#endif
}

void LcdFill_REC()
{
    unsigned char x, y, ii;
#if DBUS_BITS == 4
    lcd_write(0x26, 0); //����ָ�� ��ͼ��ʾ
#else
    lcd_write(0x36, 0); //����ָ�� ��ͼ��ʾ
#endif
    for (ii = 0; ii < 9; ii += 8)
        for (y = 0; y < 0x20; y++)
            for (x = 0; x < 8; x++)
            {
                lcd_write(y + 0x80, 0);      //�е�ַ
                lcd_write(x + 0x80 + ii, 0); //�е�ַ
                if ((y / 8) % 2)
                {
                    lcd_write(0xFF, 1); //д���� D15��D8
                    lcd_write(0x00, 1); //д���� D7��D0
                }
                else
                {
                    lcd_write(0x00, 1); //д���� D15��D8
                    lcd_write(0xFF, 1); //д���� D7��D0
                }
            }
#if DBUS_BITS == 4
    lcd_write(0x20, 0);
#else
    lcd_write(0x30, 0);
#endif
}
