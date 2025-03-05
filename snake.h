#pragma once


#ifndef __SNACK_H__
#define __SNACK_H__
#define MIN_SLEEP_TIME 50 // 最小睡眠时间
#define BLOCK_SIZE 20



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<easyx.h>
#include <graphics.h>


#define WIDE 60 //宽度
#define HIGH 20 //高度



//定义蛇对象
struct BODY {
    int x;
    int y;
};
struct SNAKE {
    struct BODY body[WIDE * HIGH]; //body[0]--蛇头
    int size;
}snake;

//定义食物对象
struct FOOD {
    int x;
    int y;
}food;

int score = 0; //分数
int kx = 0, ky = 0; //用户按下asdw任意一个按键所得到的坐标值
int lastx = 0;//蛇尾坐标
int  lasty = 0;
int sleeptime = 400;
int highScore = 0;

void init_snake();
void init_food();
void initUI();
void playgame();
void initwall();
void printscore();
void load_high_score();
void save_high_score();

#endif