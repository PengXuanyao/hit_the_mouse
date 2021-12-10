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
                   "     �����     "
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
 * չʾ��ǰ״̬��ָ����չʾ��Ϸ�ĵ�ǰ�����״̬�����磬������ֵ�λ�ú�״̬�����ܱ�
 * �������û�����
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void screenDisplay(void)
{
    uint8_t i;
    char text_buffer[BUFFERLENTH]; //�ַ�������������ʾ��Ӧ�ַ�
    // pos��������ŵ���λ�õ����飬���˶�̬�ڴ���Ϊ�˺����ܹ������޸ĵ����������
    // ����ı�cur_game_status.num���ܹ����ӵ��������������ά��
    volatile uint8_t *pos = (uint8_t *)malloc(cur_game_status.num * sizeof(uint8_t));
    // ��ȫ�ֱ����еĵ����λ����Ϣ���Ƶ������ɵĿռ���
    for (i = 0; i < cur_game_status.num; i++)
    {
        pos[i] = cur_game_status.pos[i]; // get the origin pos
        pos[i] = posTransfer(pos[i]);    // position after transfer
    }
    lcd_display(0, "  Hit The Mouse  ");
    // ��ַλ����Ϣ����ʾ
    /* ������ͼΪ
     *          # #  @  @  @  @  # #
     *          # #  @  @  @  @  # #
     *          # #  @  @  @  @  # #
     *          # #  @  @  @  @  # #
     * ���� @ Ϊ�����ܹ����ֵ�λ�ã�# # Ϊ�߽�
     * ��ʾ��ʽΪͨ�� *pos ��0~11����һ������Ӧ�ٵ�ͼ��
     * ����LCD�������Ķ�Ӧ��ϵ�е����⣬����Ϸ���������ת��
     * �μ�posTransfer����
     */
    for (i = 8; i < 32; i++)
    {
        if ((i % 8) < 2 || (i % 8) > 5)
        {
            //��ʾ�߽�
            lcd_display(i, "#");
        }
        else if (i == pos[0] || i == pos[1] || i == pos[2])
        {
            //��ʾ����
            lcd_display(i, "@");
        }
    }
    free(pos);
};
/**
 * @description: display the cur_status��you can add your function here
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
 * ����ת����������Ҫ����
 * 0~3  ---> 18~21  ��Ӧ�ڶ��е�@
 * 4~7  ---> 10~13  ��Ӧ�����е�@
 * 8~11 ---> 26~29  ��Ӧ�����е�@
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