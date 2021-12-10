/*
 * @Description: initial pages of the game
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-12-04 18:14:09
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-10 22:40:01
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
                   "     打地鼠     "
                   "1.Home 2.Start "
                   " 3.Record 4.End");
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
 * @description: use the lcd to display cur_status.
 * 展示当前状态是指的是展示游戏的当前地鼠的状态，例如，地鼠出现的位置和状态，可能被
 * 打掉或者没被打掉
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void screenDisplay(void)
{
    uint8_t i;
    char text_buffer[BUFFERLENTH]; //字符容器，用于显示相应字符
    // pos是用来存放地鼠位置的数组，用了动态内存是为了后期能够方便修改地鼠的数量，
    // 如果改变cur_game_status.num，能够增加地鼠的数量，方便维护
    volatile uint8_t *pos = (uint8_t *)malloc(cur_game_status.num * sizeof(uint8_t));
    // 将全局变量中的地鼠的位置信息复制到新生成的空间里
    for (i = 0; i < cur_game_status.num; i++)
    {
        pos[i] = cur_game_status.pos[i]; // get the origin pos
        pos[i] = posTransfer(pos[i]);    // position after transfer
    }
    lcd_display(0, "  Hit The Mouse  ");
    // 地址位置信息的显示
    /* 整个地图为
     *          # #  @  @  @  @  # #
     *          # #  @  @  @  @  # #
     *          # #  @  @  @  @  # #
     *          # #  @  @  @  @  # #
     * 其中 @ 为地鼠能够出现的位置，# # 为边界
     * 显示方式为通过 *pos （0~11）的一个数对应再地图上
     * 由于LCD的驱动的对应关系有点问题，因此上方这里做了转换
     * 参见posTransfer函数
     */
    for (i = 8; i < 32; i++)
    {
        if ((i % 8) < 2 || (i % 8) > 5)
        {
            //显示边界
            lcd_display(i, "#");
        }
        else if (i == pos[0] || i == pos[1] || i == pos[2])
        {
            //显示地鼠
            lcd_display(i, "@");
        }
    }
    free(pos);
};
/**
 * @description: display the cur_status，you can add your function here
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void curDisplay(void)
{
    screenDisplay(); // use the lcd
};

/**
 * @description: position transfer
 * 坐标转换函数，主要将：
 * 0~3  ---> 18~21  对应第二行的@
 * 4~7  ---> 10~13  对应第三行的@
 * 8~11 ---> 26~29  对应第四行的@
 * @param {uint8_t} pos
 * @return {*}
 * @author: PengXuanyao
 */
uint8_t posTransfer(uint8_t pos)
{
    if ((pos >= 0) && (pos < 4))
    {
        pos = pos + 18; // the lcd display is not setted as the custom order, so we have to transfer the position
    }
    else if ((pos >= 4) && (pos < 8))
    {
        pos = pos + 6; // the lcd display is not setted as the custom order, so we have to transfer the position
    }
    else if ((pos >= 8) && (pos < 12))
    {
        pos = pos + 18; // the lcd display is not setted as the custom order, so we have to transfer the position
    }
    return pos;
}