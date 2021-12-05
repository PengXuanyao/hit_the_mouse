/*
 * @Description: this is the main logic source file of the game
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-12-01 14:13:17
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-05 23:41:05
 */

#include "r_cg_userdefine.h"
uint8_t map[MAPHET][MAPWID] = {0};     //the map is decided by the screen size
Status cur_game_status = {EAZY, NULL}; //current status
uint8_t mode = HOME;                   //the initial mode is home
uint8_t diff = EAZY;                   //difficulty is set
uint8_t myrecord = 0;                  //initial record is 0
uint8_t score = 0;                     //current score
uint8_t time = 60;                     //1 minute count
uint8_t timerflag = 0;                 //timer flag to start the timer,when first into game
//functions
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
    initStatus();
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
    //used to fresh the status
    if (timerflag == 0)
    {
        R_TAU0_Channel2_Start();
        time = 60;
    }
    detectIfHit();
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
 * @description: back to home page and initialize the parament 
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void restartGame(void)
{
    mode = HOME;
};
/**
 * @description: init the status
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void initStatus(void)
{
    cur_game_status.num = HARD;
    cur_game_status.pos = NULL;
};
/**
 * @description: use to fresh the status
 * @param {*}
 * @return {*}
 * @author: PengXuanyao
 */
void freshStatus(void)
{
    uint8_t i;
    uint8_t *curpos = (uint8_t *)malloc(cur_game_status.num * sizeof(uint8_t));
    cur_game_status.pos = curpos;
    for (i = 0; i < cur_game_status.num; i++)
    {
        *curpos = rand() % 12;
        curpos++;
    }
    setStatusMap(&cur_game_status);
    free(cur_game_status.pos);
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
    for (i = 1; i <= cur_game_status.num; i++)
    {

        if ((num_keyboard - 4) == cur_game_status.pos[i]) //use the key 5-16 as the keyboard
        {
            score++;
        }
    }
}
