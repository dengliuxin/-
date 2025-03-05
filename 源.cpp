
#define _CRT_SECURE_NO_WARNINGS
#include "snake.h"



//初始化蛇
void init_snake() {
    snake.size = 2;
    snake.body[0].x = WIDE / 2;
    snake.body[0].y = HIGH / 2;
    snake.body[1].x = WIDE / 2 - 1;
    snake.body[1].y = HIGH / 2;
}
//初始化界面
void initUI()
{
    COORD coord = { 0 }; //设置光标位置
    //画蛇

    for (size_t i = 0; i < snake.size; i++)
    {
        coord.X = snake.body[i].x;
        coord.Y = snake.body[i].y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        if (i == 0)
            putchar('@');
        else
            putchar('*');
    }
    //去除蛇尾
    coord.X = lastx;
    coord.Y = lasty;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    putchar(' ');
    //这里如果不画食物，光标后会输出请任意。。。。会覆盖之前画的蛇的身子
    //不过也可以移走光标
    //画食物
    coord.X = food.x;
    coord.Y = food.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    putchar('#');

}

//食物初始化
void init_food() {

    food.x = rand() % WIDE;
    food.y = rand() % HIGH;
}
void playgame()
{
    char key = 'd';
    //判断蛇撞墙
    while (snake.body[0].x >= 0 && snake.body[0].x < WIDE && snake.body[0].y >= 0 && snake.body[0].y < HIGH)
    {

        //更新蛇
        initUI();
        //接受用户输入
        if (_kbhit()) //为真时表示有键盘输入
        {
            key = _getch();
        }
        switch (key)
        {
        case 'w':
            kx = 0;
            ky = -1;
            break;
        case 's':
            kx = 0;
            ky = 1;
            break;
        case 'a':
            kx = -1;
            ky = 0;
            break;
        case 'd':
            kx = 1;
            ky = 0;
            break;
        }
        //判断蛇撞自己
        for (size_t i = 1; i < snake.size; i++)
        {
            if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
            {
                return;//结束游戏
            }
        }
        //判断蛇吃食物
        if (snake.body[0].x == food.x && snake.body[0].y == food.y)
        {   //食物消失并重新生成
            init_food();
            //蛇身体增长
            snake.size++;
            //分数增加
            score = score + 10;
            //速度增加
            sleeptime = sleeptime - 30;
            if (sleeptime < MIN_SLEEP_TIME) {
                sleeptime = MIN_SLEEP_TIME;
                break;
            }
        }
        lastx = snake.body[snake.size - 1].x;
        lasty = snake.body[snake.size - 1].y;
        //蛇移动
        for (size_t i = snake.size - 1; i > 0; i--)
        {
            snake.body[i].x = snake.body[i - 1].x;
            snake.body[i].y = snake.body[i - 1].y;
        }
        snake.body[0].x += kx;
        snake.body[0].y += ky;
        //清屏
        Sleep(sleeptime);


    }
}



// 加载最高分
void load_high_score() {
    FILE* file = fopen("highscore.txt", "r");
    if (file) {
        // 尝试从文件中读取最高分
        if (fscanf(file, "%d", &highScore) != 1) {
            // 如果读取失败，可能是文件为空或格式错误，将highScore初始化为0
            printf("ook");
            highScore = 0;
        }
        fclose(file);  // 关闭文件
    }
    else {
        // 如果文件不存在，将highScore初始化为0
        printf("oo");
        highScore = 0;
    }
}

// 保存最高分
void save_high_score() {
    // 检查当前分数是否高于已保存的最高分
    if (score > highScore) {
        FILE* file = fopen("highscore.txt", "w");
        if (file) {
            // 更新最高分
            highScore = score;
            // 将新的最高分写入文件
            if (fprintf(file, "%d", highScore) < 0) {
                printf("Error: Failed to write high score to file.\n");
            }
            fclose(file);  // 关闭文件
        }
        else {
            printf("Error: Unable to open or create highscore.txt\n");
        }
    }
}
void initwall()
{
    for (size_t i = 0; i <= HIGH; i++)
    {
        for (size_t j = 0; j <= WIDE; j++)
        {
            if (j == WIDE)
            {
                printf("|");
            }
            else if (i == HIGH)
            {
                printf("-");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    printf("\n");
}
void printscore()
{
    COORD coord; //设置光标位置
    //将光标移动到不干扰游戏的位置
    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("Game Over\n");
    printf("分数：%d\n", score);
    printf("最高分：%d\n", highScore);
}
int main()

{

    //隐藏光标
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = sizeof(cursor_info);
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

    srand((unsigned int)time(NULL));
    init_snake();
    init_food();
    initwall();
    initUI();

    playgame();
    save_high_score(); 
    load_high_score();
    printscore();
   
    system("pause");
    return EXIT_SUCCESS;

}

