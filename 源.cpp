
#define _CRT_SECURE_NO_WARNINGS
#include "snake.h"



//��ʼ����
void init_snake() {
    snake.size = 2;
    snake.body[0].x = WIDE / 2;
    snake.body[0].y = HIGH / 2;
    snake.body[1].x = WIDE / 2 - 1;
    snake.body[1].y = HIGH / 2;
}
//��ʼ������
void initUI()
{
    COORD coord = { 0 }; //���ù��λ��
    //����

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
    //ȥ����β
    coord.X = lastx;
    coord.Y = lasty;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    putchar(' ');
    //�����������ʳ��������������⡣�������Ḳ��֮ǰ�����ߵ�����
    //����Ҳ�������߹��
    //��ʳ��
    coord.X = food.x;
    coord.Y = food.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    putchar('#');

}

//ʳ���ʼ��
void init_food() {

    food.x = rand() % WIDE;
    food.y = rand() % HIGH;
}
void playgame()
{
    char key = 'd';
    //�ж���ײǽ
    while (snake.body[0].x >= 0 && snake.body[0].x < WIDE && snake.body[0].y >= 0 && snake.body[0].y < HIGH)
    {

        //������
        initUI();
        //�����û�����
        if (_kbhit()) //Ϊ��ʱ��ʾ�м�������
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
        //�ж���ײ�Լ�
        for (size_t i = 1; i < snake.size; i++)
        {
            if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y)
            {
                return;//������Ϸ
            }
        }
        //�ж��߳�ʳ��
        if (snake.body[0].x == food.x && snake.body[0].y == food.y)
        {   //ʳ����ʧ����������
            init_food();
            //����������
            snake.size++;
            //��������
            score = score + 10;
            //�ٶ�����
            sleeptime = sleeptime - 30;
            if (sleeptime < MIN_SLEEP_TIME) {
                sleeptime = MIN_SLEEP_TIME;
                break;
            }
        }
        lastx = snake.body[snake.size - 1].x;
        lasty = snake.body[snake.size - 1].y;
        //���ƶ�
        for (size_t i = snake.size - 1; i > 0; i--)
        {
            snake.body[i].x = snake.body[i - 1].x;
            snake.body[i].y = snake.body[i - 1].y;
        }
        snake.body[0].x += kx;
        snake.body[0].y += ky;
        //����
        Sleep(sleeptime);


    }
}



// ������߷�
void load_high_score() {
    FILE* file = fopen("highscore.txt", "r");
    if (file) {
        // ���Դ��ļ��ж�ȡ��߷�
        if (fscanf(file, "%d", &highScore) != 1) {
            // �����ȡʧ�ܣ��������ļ�Ϊ�ջ��ʽ���󣬽�highScore��ʼ��Ϊ0
            printf("ook");
            highScore = 0;
        }
        fclose(file);  // �ر��ļ�
    }
    else {
        // ����ļ������ڣ���highScore��ʼ��Ϊ0
        printf("oo");
        highScore = 0;
    }
}

// ������߷�
void save_high_score() {
    // ��鵱ǰ�����Ƿ�����ѱ������߷�
    if (score > highScore) {
        FILE* file = fopen("highscore.txt", "w");
        if (file) {
            // ������߷�
            highScore = score;
            // ���µ���߷�д���ļ�
            if (fprintf(file, "%d", highScore) < 0) {
                printf("Error: Failed to write high score to file.\n");
            }
            fclose(file);  // �ر��ļ�
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
    COORD coord; //���ù��λ��
    //������ƶ�����������Ϸ��λ��
    coord.X = 0;
    coord.Y = HIGH + 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("Game Over\n");
    printf("������%d\n", score);
    printf("��߷֣�%d\n", highScore);
}
int main()

{

    //���ع��
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

