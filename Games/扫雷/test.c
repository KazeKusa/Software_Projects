#include "game.h"
void menu()
{
    printf("********************\n");
    printf("*****  1.play  *****\n");
    printf("*****  0.exit  *****\n");
    printf("********************\n");
}
void game()
{
    char mine[ROWS][COLS] = {0}; //存放布置好的雷的信息
    char show[ROWS][COLS] = {0}; //存放排查出的雷的信息
    //初始化数组的内容为指定的内容
    //mine数组在没有布置雷的时候都是'0'
    InitBoard(mine, ROWS, COLS,'0');
    //show数组在没有布置雷的时候都是'*'
    InitBoard(show, ROWS, COLS,'*');
    // 设置雷
    SetMine(mine, ROW, COL);
    DisplayBoard(show, ROW, COL); //虽然这里使用了ROW和COL，但是输入的mine和show仍然是11阶方阵，只是待回答打印棋盘时i和j需要用到9这个数字以满足只打印中间部分
    //排查雷
    FindMine(mine, show, ROW, COL);
}
int main()
{
    int input = 0;
    //设置随机数生成的起点
    srand((unsigned int)time(NULL));
    do
    {
        menu();
        printf("请选择:>");
        scanf("%d", &input);
        switch(input)
        {
        case 1:
            game();
            break;
        case 0:
            printf("退出游戏\n");
            break;
        default:
            printf("选择错误\n");
            break;
        }
    } while (input);
    return 0;
}
