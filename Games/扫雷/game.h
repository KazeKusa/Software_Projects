#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROW 9
#define COL 9
#define ROWS ROW+2  //虽然需要9x9的棋盘，但为了防止边缘元素在计算周围雷的个数时发生越界，需要定义11行的数组
#define COLS COL+2
#define EASY_COUNT 10

void InitBoard(char board[ROWS][COLS], int rows, int cols,char set)
{
    int i, j = 0;
    for (i = 0; i < rows;i++)
    {
        for (j = 0; j < cols;j++)
        {
            board[i][j] = set;
        }
    }
}

void DisplayBoard(char board[ROWS][COLS],int row,int col)
{
    int i, j = 0;
    printf("-----扫雷游戏-----\n");
    for (j = 0; j <= col;j++) //为棋盘添上列数，从0开始
    {
        printf("%d ", j);
    }
    printf("\n");
    for (i = 1; i <= row; i++) // 从1开始，以去掉用于防止数组越界的边缘行，只打印棋盘部分
    {
        printf("%d ", i); //为棋盘添上行数，从1开始
        for (j = 1; j <= col; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("-----扫雷游戏-----\n");
}

void SetMine(char board[ROWS][COLS],int row,int col)
{
    int count = EASY_COUNT;
    while(count)
    {
        int x = rand() % row + 1;
        int y = rand() % row + 1;
        if(board[x][y] == '0')
        {
            board[x][y] = '1';
            count--;
        }
    }
}

int  get_mine_count(char board[ROWS][COLS],int x,int y)
{
    return (board[x - 1][y] +
            board[x - 1][y - 1] +
            board[x - 1][y + 1] +
            board[x][y - 1] +
            board[x][y + 1] +
            board[x + 1][y - 1] +
            board[x + 1][y] +
            board[x + 1][y + 1] - 8 * '0'); //字符'1'和数字1是不一样的，前者对应的ASSCI码值是48，而后者是49，要实现二者之间的转换只需减去'0'，即'1'-'0'=1
}
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col)
{
    int x, y = 0;
    int win = 0; //找到非雷的个数
    while(win<row*col-EASY_COUNT)
    {
        printf("请输入要排查的坐标:>");
        scanf("%d %d", &x, &y);
        if(x>=1 && x<=row && y>=1 && y<=col)
        {
            if(show[x][y] != '*')
            {
                printf("该坐标被排查过了，不能重复排查\n");
            }
            else
            {
                if(mine[x][y] == '1')//如果是雷
                {
                    printf("很遗憾，你被炸死了\n");
                    DisplayBoard(mine, ROW, COL);
                    break;
                }
                else//如果不是雷
                {
                    win++;
                    //统计mine数组中x,y坐标周围有几个雷
                    int count = get_mine_count(mine, x, y);
                    show[x][y] = count + '0';//加上'0'转换成数字字符
                    DisplayBoard(show, ROW, COL);
                }
            }
        }
        else
        {
            printf("输入的坐标非法，请重新输入\n");
        }
    }
    if(win == row*col-EASY_COUNT)
    {
        printf("恭喜你，排雷成功\n");
        DisplayBoard(mine, ROW, COL);
    }
}

//待实现的更多功能:
//1.标记功能
//2.展开一片的功能