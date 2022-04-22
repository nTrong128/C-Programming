#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define M 7
#define N 7
#define MINE -1
int Map[M][N];
int Status[M][N];
void PrintMap(); // In bang do boom //
void CountMines(); // Kiem tra so luong boom xung quanh //
void Open_cell(int r, int c); // Mo o duoc chon va xung quanh //
int Count_remain(); // Kiem tra so o khong chua boom con lai //
void openAll(); // Mo tat ca o //
int Open_check(int r, int c); // Kiem tra trang thai o //
void Init_mines(int k); // Tao boom //

int main()
{
    int k = 9; //  So luong boom //
    Init_mines(k);
    int r,c;
    CountMines();
    while(1)
    {
        PrintMap();
        do {
            do {
                fflush(stdin);
                printf("Choose your cell(Row-> Column): ");
                scanf("%d%d", &r, &c);
            }
            while(Open_check(r,c)==1);
        }
        while(r>M-1 || r<0 || c>N-1 || c<0);

        if(Map[r][c] == MINE) {
            openAll();
            PrintMap();
            printf("\n#---------- GAME OVER ----------#\n");
            break;
        }
        Open_cell(r,c);
        if(Count_remain() == k)
        {
            openAll();
            PrintMap();
            printf("\n#---------- Congratulations ----------#\n    #---------- YOU WIN ----------#\n");
            break;
        }
    }
    getch();
    return 0;
}

void PrintMap()
{
    int i,j;
    printf("  ");
    for(j=0;j<N;j++)
        printf(" %2d ",j);
    printf("\n");
    for(i=0;i<M;i++)
    {
        printf("  +---+---+---+---+---+---+---+\n");
        printf("%d |",i);
        for(j=0;j<N;j++)
        {
            if(Map[i][j] ==MINE && Status[i][j] ==1)
                printf(" x |");
            else if(Map[i][j] !=0 && Status[i][j] ==1)
                printf("%2d |", Map[i][j]);
            else if(Status[i][j] == 0)
                printf(" # |");
            else if(Map[i][j] == 0)
                printf(" . |");
            else printf("%2d ", Map[i][j]);
        }

        printf("\n");
    }
    printf("  +---+---+---+---+---+---+---+\n");
}

void CountMines()
{
    int i,j;

    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            if(Map[i][j]!=MINE)
            {
                int cnt=0;
                if(i-1>=0 && j-1>=0 && Map[i-1][j-1] == MINE)
                    cnt++;
                if(i-1>=0  && Map[i-1][j] == MINE)
                    cnt++;
                if(i-1>=0 && j+1<N && Map[i-1][j+1] == MINE)
                    cnt++;
                if( j-1>=0 && Map[i][j-1] == MINE)
                    cnt++;
                if(j+1<N && Map[i][j+1] == MINE)
                    cnt++;
                if(i+1<M && j-1>=0 && Map[i+1][j-1] == MINE)
                    cnt++;
                if(i+1<M && Map[i+1][j] == MINE)
                    cnt++;
                if(i+1<M && j+1<N && Map[i+1][j+1] == MINE)
                    cnt++;
                Map[i][j]=cnt;
            }
        }
    }
}

void openAll()
{
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            Status[i][j] = 1;
        }
    }
}

int Count_remain()
{
    int cnt = 0;
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            if(Status[i][j] == 0)
                cnt++;
        }
    }
    return cnt;
}
int Open_check(int r, int c)
{
    if(Status[r][c] == 1)
        return 1;
    else return 0;
}

void Open_cell(int r, int c) {
    if(r<0 || r>=M || c<0 || c>=N)
        return;
    if(Status[r][c] == 1)
        return;
    Status[r][c] = 1;
    if(Map[r][c] > 0)
    {
        Status[r][c] = 1;
        return;
    }
    else if(Map[r][c] == 0)
    {
        Open_cell(r-1,c-1);
        Open_cell(r-1,c);
        Open_cell(r-1,c+1);
        Open_cell(r,c-1);
        Open_cell(r,c+1);
        Open_cell(r+1,c-1);
        Open_cell(r+1,c);
        Open_cell(r+1,c+1);
    }

}

void Init_mines(int k)
{
    srand(time(0));
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            Map[i][j]=0;
        }
    }
    int cnt=0;
    for(i=0;i<k;i++)
    {
        int r= rand()%M;
        int c =rand()%N;
        if(Map[r][c] == 0)
        {
            Map[r][c] = MINE;
            cnt++;
        }
    }
    return;
}