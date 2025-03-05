#pragma once


#ifndef __SNACK_H__
#define __SNACK_H__
#define MIN_SLEEP_TIME 50 // ��С˯��ʱ��
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


#define WIDE 60 //���
#define HIGH 20 //�߶�



//�����߶���
struct BODY {
    int x;
    int y;
};
struct SNAKE {
    struct BODY body[WIDE * HIGH]; //body[0]--��ͷ
    int size;
}snake;

//����ʳ�����
struct FOOD {
    int x;
    int y;
}food;

int score = 0; //����
int kx = 0, ky = 0; //�û�����asdw����һ���������õ�������ֵ
int lastx = 0;//��β����
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