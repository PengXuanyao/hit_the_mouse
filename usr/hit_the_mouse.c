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
 * 首页界面，进行功能按键的展示
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void home(void)
{
    R_TAU0_Channel2_Stop(); //停止计数器计数
    showHome();             //展示home界面
    score = 0;
    timerflag = 0;
    time = 60;
}
/**
 * @description: game status is on
 * 游戏开始模式，用于刷新状态下显示
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
        //第一次进入后开始计时，并清零得分
        score = 0;
        //时间为60s
        time = 60;
        //打开定时器
        R_TAU0_Channel2_Start();
    }
    //检查是否有地鼠被打
    detectIfHit();
    //展示当前界面
    curDisplay();
    //刷新频率大概略小于1000 / 5 = 200Hz
    delay_ms(5);
    // 计时标志置位，下次不再开始重新计时
    timerflag = 1;
}
/**
 * @description: show the record
 * 展示最高记录
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void record(void)
{
    char text_buffer[BUFFERLENTH];                              //字符容器
    timerflag = 0;                                              //计时标志清零，以便下一次进入game打开
    time = 60;                                                  //时间初始，置位60
    R_TAU0_Channel2_Stop();                                     //关闭定时器
    sprintf(text_buffer, "your highest score:%d   ", myrecord); //生成字符串
    lcd_display(16, text_buffer);                               //显示字符
    delay_ms(5);
}
/**
 * @description:显示结束界面
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void end(void)
{
    char text_buffer[BUFFERLENTH];
    timerflag = 0;
    R_TAU0_Channel2_Stop();
    //显示得分
    sprintf(text_buffer, "your score:%d   ", score);
    lcd_display(0, text_buffer);
    if (score >= myrecord)
    {
        //记录最高分
        myrecord = score;
    }
    //显示最高分
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
    //记录上一秒得分
    static uint8_t last_score;
    //随机生成三个点
    for (i = 0; i < cur_game_status.num; i++)
    {
        cur_game_status.pos[i] = rand() % 12; // random 3 points
    }
    //比较得到上一秒得分，通过LED显示
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
 * @description:检测是否有地鼠被打中
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void detectIfHit(void)
{
    uint8_t i;
    //检查每一个地鼠的位置
    for (i = 0; i < cur_game_status.num; i++)
    {
        //将地鼠的坐标值值和当前键盘值作比较
        //键盘上范围为5~16，实际坐标为0~11；即做了-5操作转换
        if ((num_keyboard - 5) == cur_game_status.pos[i]) // use the key 5-16 as the keyboard
        {
            score++;
            cur_game_status.pos[i] = 50; // set the position invalid
        }
    }
}
