/*
 * @Description: initial pages of the game
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-12-04 18:14:09
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-05 23:45:58
 */
#include "r_cg_userdefine.h"
/**
 * @description: 
 * @param {uint16_t} s
 * @return {*}
 * @author: PengXuanyao
 */
void delay_ms(uint16_t s)
{
    uint16_t i;
    for (s; s > 0; s--)
    {
        for (i = 32000; i > 0; i++)
            ;
    }
}
/**
 * @description: show the home page
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void showHome(void)
{
    CLEAN_SCREEN();
    lcd_display(0, "  Hit The Mouse  "
                   "     ´òµØÊó     "
                   "1.Home 2.Start "
                   " 3.Record");
    delay_ms(10);
}
/**
 * @description: use the segment led show scores, 0-99
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void scoreDisplay(void)
{
    displayNum(time, score);
};
/**
 * @description: use the lcd to display cur_status
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void screenDisplay(void){};
/**
 * @description: display the cur_status
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void curDisplay(void)
{
    scoreDisplay();  //use the segment led
    screenDisplay(); //use the lcd
};
/**
 * @description: show record on the screen
 * @param {uint8_t} cur_record
 * @return {*}
 * @author: PengXuanyao
 */
void showRecord(uint8_t cur_record)
{
    static uint8_t highest_record = 0;
    if (cur_record > highest_record)
    {
        highest_record = cur_record;
    }
    //LCD_show
}