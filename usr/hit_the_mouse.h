/*
 * @Description: the header of the logic soucre
 * @Version: 2.0
 * @Autor: PengXuanyao
 * @Date: 2021-12-01 14:27:25
 * @LastEditors: PengXuanyao
 * @LastEditTime: 2021-12-05 23:20:40
 */
#ifndef __HIT_THE_MOUSE__
#define __HIT_THE_MOUSE__

//macro definition
#define MAPWID 4 //map width
#define MAPHET 3 //map height
#define DISAPP 0 //mouse dis appear
#define APPEAR 1 //mouse appear
#define GETMOU 2 //hit the mouse successfully
#define MISMOU 2 //miss the mouse
#define NULL 0
//mode
#define MODENUM 3
#define HOME 1   //show home mode
#define GAME 2   //game mode
#define RECORD 3 //show record mode
//difficulty
#define EAZY 1
#define NORMAL 2
#define HARD 3
//data structure definition
typedef struct Status //status shows the num and position of mouse
{
    /* data */
    uint8_t num;
    uint8_t *pos;
} Status;
//global variables
extern Status cur_state;
extern uint8_t mode;
extern uint8_t diff;
extern uint8_t myrecord;
extern uint8_t score;
extern uint8_t time;
extern uint8_t timerflag; 
//function statement
extern void initMap(void);
extern void home(void);
extern void game(void);
extern void record(void);
extern void restartGame(void);
extern void initStatus(void);
extern void freshStatus(void);
extern void setStatusMap(Status *cur);
extern void detectIfHit(void);
#endif