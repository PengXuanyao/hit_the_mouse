/*
 * @Description: this is the main logic source file of the game
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-12-01 14:13:17
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-10 23:09:42
 */

#include "r_cg_userdefine.h"
Status cur_game_status; // current status
uint8_t diff = EAZY;    // difficulty is set
uint8_t myrecord = 0;   // initial record is 0
uint8_t score = 0;      // current score
uint8_t time = 59;      // 1 minute count
uint8_t timerflag = 0;  // timer flag to start the timer,when first into game
// functions
/**
 * @description: back to home state
 * ��ҳ���棬���й��ܰ�����չʾ
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void home(void)
{
    R_TAU0_Channel2_Stop(); //ֹͣ����������
    showHome();             //չʾhome����
    score = 0;
    timerflag = 0;
    time = 60;
}
/**
 * @description: game status is on
 * ��Ϸ��ʼģʽ������ˢ��״̬����ʾ
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void game(void)
{
    // uint8_t time
    // used to fresh the status
    if (timerflag == 0)
    {
        //��һ�ν����ʼ��ʱ��������÷�
        score = 0;
        //ʱ��Ϊ60s
        time = 60;
        //�򿪶�ʱ��
        R_TAU0_Channel2_Start();
    }
    //����Ƿ��е��󱻴�
    detectIfHit();
    //չʾ��ǰ����
    curDisplay();
    //ˢ��Ƶ�ʴ����С��1000 / 5 = 200Hz
    delay_ms(5);
    // ��ʱ��־��λ���´β��ٿ�ʼ���¼�ʱ
    timerflag = 1;
}
/**
 * @description: show the record
 * չʾ��߼�¼
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void record(void)
{
    char text_buffer[BUFFERLENTH];                              //�ַ�����
    timerflag = 0;                                              //��ʱ��־���㣬�Ա���һ�ν���game��
    time = 60;                                                  //ʱ���ʼ����λ60
    R_TAU0_Channel2_Stop();                                     //�رն�ʱ��
    sprintf(text_buffer, "your highest score:%d   ", myrecord); //�����ַ���
    lcd_display(16, text_buffer);                               //��ʾ�ַ�
    delay_ms(5);
}
/**
 * @description:��ʾ��������
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void end(void)
{
    char text_buffer[BUFFERLENTH];
    timerflag = 0;
    R_TAU0_Channel2_Stop();
    //��ʾ�÷�
    sprintf(text_buffer, "your score:%d   ", score);
    lcd_display(0, text_buffer);
    if (score >= myrecord)
    {
        //��¼��߷�
        myrecord = score;
    }
    //��ʾ��߷�
    sprintf(text_buffer, "your highest score:%d   ", myrecord);
    lcd_display(16, text_buffer);
    delay_ms(5);
}
/**
 * @description: use to fresh the status
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void freshStatus(void)
{
    uint8_t i;
    //��¼��һ��÷�
    static uint8_t last_score;
    //�������������
    for (i = 0; i < cur_game_status.num; i++)
    {
        cur_game_status.pos[i] = rand() % 12; // random 3 points
    }
    //�Ƚϵõ���һ��÷֣�ͨ��LED��ʾ
    switch (score - last_score)
    {
    case 0:
        LED_ALL_OFF();
        break;
    case 1:
        LED_ALL_OFF();
        L1_ON();
        break;
    case 2:
        LED_ALL_OFF();
        L1_ON();
        L2_ON();
        break;
    case 3:
        LED_ALL_OFF();
        L1_ON();
        L2_ON();
        L3_ON();
        break;
    }
    last_score = score;
};
/**
 * @description:����Ƿ��е��󱻴���
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void detectIfHit(void)
{
    uint8_t i;
    //���ÿһ�������λ��
    for (i = 0; i < cur_game_status.num; i++)
    {
        //�����������ֵֵ�͵�ǰ����ֵ���Ƚ�
        //�����Ϸ�ΧΪ5~16��ʵ������Ϊ0~11��������-5����ת��
        if ((num_keyboard - 5) == cur_game_status.pos[i]) // use the key 5-16 as the keyboard
        {
            score++;
            cur_game_status.pos[i] = 50; // set the position invalid
        }
    }
}
