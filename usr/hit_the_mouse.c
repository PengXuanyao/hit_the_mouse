/*
 * @Description: this is the main logic source file of the game
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-12-01 14:13:17
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-06 13:44:53
 */

#include "r_cg_userdefine.h"
uint8_t map[MAPHET][MAPWID] = {0};     // the map is decided by the screen size
Status cur_game_status = {HARD, NULL}; // current status
uint8_t diff = EAZY;                   // difficulty is set
uint8_t myrecord = 0;                  // initial record is 0
uint8_t score = 0;                     // current score
uint8_t time = 59;                     // 1 minute count
uint8_t timerflag = 0;                 // timer flag to start the timer,when first into game
// functions
/**
 * @description: clear the status map
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void initMap(void)
{
    uint8_t i, j;
    for (i = 0; i < MAPHET; i++)
    {
        for (j = 0; j < MAPWID; j++)
        {
            map[MAPHET][MAPWID] = 0;
        }
    }
}
/**
 * @description: back to home state
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void home(void)
{
    R_TAU0_Channel2_Stop();
    showHome();
    initMap();
    score = 0;
    timerflag = 0;
    time = 0;
}
/**
 * @description: game status is on
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
        score = 0;
        time = 60;
        R_TAU0_Channel2_Start();
    }
    detectIfHit();
    curDisplay();
    delay_ms(5);
    timerflag = 1;
}
/**
 * @description: show the record
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void record(void)
{
    R_TAU0_Channel2_Stop();
    showRecord(myrecord);
    timerflag = 0;
    time = 0;
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
    for (i = 0; i < cur_game_status.num; i++)
    {
        cur_game_status.pos[i] = 3;           // random 3 points
        cur_game_status.pos[i] = rand() % 12; // random 3 points
    }
    setStatusMap(&cur_game_status);
};
/**
 * @description: set the map
 * @param {Status} cur
 * @return {*}
 * @author: PengXuanyao
 */
void setStatusMap(Status *cur)
{
    uint8_t i;
    uint8_t *p = cur->pos;
    initMap();
    for (i = 0; i < cur->num; i++)
    {
        map[*(p) / 4][*(p) % 4] = 1;
        p++;
    }
}
/**
 * @description:
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void detectIfHit(void)
{
    uint8_t i;
    for (i = 0; i < cur_game_status.num; i++)
    {

        if ((num_keyboard - 5) == cur_game_status.pos[i]) // use the key 5-16 as the keyboard
        {
            score++;
            cur_game_status.pos[i] = 50; // set the position invalid
        }
    }
}
/**
 * @description:
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void end(void)
{
    R_TAU0_Channel2_Stop();
    char text_buffer[BUFFERLENTH];
    sprintf(text_buffer, "your score:%d   ", score);
    if (score >= myrecord)
    {
        myrecord = score;
    }
    lcd_display(0, text_buffer);
    sprintf(text_buffer, "your highest score:%d   ", myrecord);
    lcd_display(16, text_buffer);
    delay_ms(5);
}