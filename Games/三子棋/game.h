#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 3  //使用define定义，这样如果以后需要更改棋盘的行
#define COL 3 //列数，就可以直接在这里修改，而不用每一处都修改

//初始化棋盘
void InitBoard(char board[ROW][COL],int row,int col) 
{
    int i = 0;
    int j = 0;
    for(i = 0;i < row;i++)
    {
        for(j = 0;j < col;j++)
        {
            board[i][j] = ' ';
        }
    }
}

//打印棋盘
void DisplayBoard(char board[ROW][COL],int row,int col) 
{
    int i = 0;
    for(i=0;i<row;i++)
    {
        //打印数据
        int j = 0;
        for(j=0;j<col;j++) //使棋盘大小根据ROW和COL的大小改变而改变
        {
            printf(" %c ",board[i][j]);
            if(j<col-1)
                printf("|");
        }
        printf("\n");
        //打印分割信息
        if(i<row-1)
        {
            for(j=0;j<row;j++) //使棋盘大小根据ROW和COL的大小改变而改变
            {
                printf("---");
                if(j<col-1)
                    printf("|");
            }
            printf("\n");
        }
    };
}

//玩家下棋
void PlayerMove(char board[ROW][COL],int row,int col)
{
    int x = 0;
    int y = 0;
    printf("玩家下棋:>\n");
    while(1)
    {
        printf("请输入坐标:>\n");
        scanf("%d %d",&x,&y);
        //坐标范围合法的判断
        if(x>=1 && x<=row && y>=1 && y<=row)
        {
            if(board[x-1][y-1] == ' ') //不能要求玩家懂得数组的底层逻辑，所以数组中的0行必须表示为1行，因而用x—1和y—1
            {
                board[x-1][y-1] = '*';
                break;
            }
            else
            {
                printf("坐标被占用，不能下棋，请选择其他位置\n");
            }
        }
        else
        {
            printf("坐标非法，请重新输入\n");
        }
    }
}

//电脑下棋
//找没有下过棋的位置随机下
void ComputerMove(char board[ROW][COL],int row,int col)
{
    printf("电脑下棋:>\n");
    int x = 0;
    int y = 0;
    while(1)
    {
        x = rand() % row; //0~2
        y = rand() % col; //0~2
        if(board[x][y] == ' ')
        {
            board[x][y] = '#';
            break;
        }
    }
}

//如果满了就返回1，没满就返回0
int IsFull(char board[ROW][COL],int row,int col)
{
    int i = 0;
    int j = 0;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}
//判断输赢
char IsWin(char board[ROW][COL],int row,int col)
{
    int i = 0;
    int j = 0;
    //行
    for(i=0;i<row;i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][1]!=' ')
        {
            return board[i][1];
        }
    }
    //列
    for(i=0;i<col;i++)
    {
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[1][i]!=' ')
        {
            return board[1][i];
        }
    }
    //对角线
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[1][1]!=' ')
    {
        return board[1][1];
    }
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[1][1]!=' ')
    {
        return board[1][1];
    }
    //没有人赢，平局
    if(IsFull(board,row,col))
    {
        return 'Q'; //平局（棋盘已满）
    }
    return 'C'; //继续
}