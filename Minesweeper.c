#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 5
#define N 5
#define MINE -1

int MapOfMines[M][N];
int Status[M][N];

void Init();
void PrintMap1();
void PrintMap2();
void CountMines();
void Open_cell_1(int r, int c);
int Count_remain();
void openAll();

int main()
{
    srand(time(0));
    int i;
    int k = 2;
    int r,c;
    Init();
    CountMines();
    while(1)
    {
        PrintMap2();
        printf("Choose your cell(Row-> Column): ");
            scanf("%d%d", &r, &c);
        if(MapOfMines[r][c] == MINE)
        {
            openAll();
            PrintMap2();
            printf("\n#---------- GAME OVER ----------#\n");
            break;
        }
        else
        {
            Open_cell_1(r,c);
        }
        if(Count_remain() == k)
        {
            printf("\n#---------- CopyCongratulations ----------#\n#---------- YOU WIN ----------#\n");
            break;
        }

    }

    return 0;
}

void Init()
{
    int i,j;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++) {
            MapOfMines[i][j] = 0;
            Status[i][j] = 0;
        }
    }
    MapOfMines[1][2] = MINE;
    MapOfMines[3][1] = MINE;
}

void PrintMap1()
{
    int i,j;
    printf("  ");
    for(j=0;j<M;j++)
        printf("%d ",j);
    printf("\n");
    for(i = 0; i < M; i++)
    {
        printf("%d ",i);
        for (j = 0; j < N; j++)
        {
            if(MapOfMines[i][j] == MINE)
                printf("x ");
            else if(MapOfMines[i][j] == 0)
                printf(". ");
            else printf("%d ", MapOfMines[i][j]);
        }
        printf("\n");
    }
}

void PrintMap2()
{
    int i,j;
    printf("  ");
    for(j=0;j<M;j++)
        printf("%d ",j);
    printf("\n");
    for(i=0;i<M;i++)
    {
        printf("%d ",i);
        for(j=0;j<N;j++)
        {
            if(Status[i][j] == 0)
                printf("# ");
            else if(MapOfMines[i][j] == MINE)
                printf("x ");
            else if(MapOfMines[i][j] == 0)
                printf(". ");
            else printf("%d ", MapOfMines[i][j]);
        }
        printf("\n");
    }
}

void CountMines()
{
    int i,j;

    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            if(MapOfMines[i][j]==MINE)
            {
                
                if(Inside_MapOfMines_Check(i-1,j-1)) MapOfMines[i-1][j-1]++;
                if(Inside_MapOfMines_Check(i-1,j)) MapOfMines[i-1][j]++;
                if(Inside_MapOfMines_Check(i-1,j+1)) MapOfMines[i-1][j+1]++;
                if(Inside_MapOfMines_Check(i,j-1)) MapOfMines[i][j-1]++;
                if(Inside_MapOfMines_Check(i,j+1)) MapOfMines[i][j+1]++;
                if(Inside_MapOfMines_Check(i+1,j-1)) MapOfMines[i+1][j-1]++;
                if(Inside_MapOfMines_Check(i+1,j)) MapOfMines[i+1][j]++;
                if(Inside_MapOfMines_Check(i+1,j+1)) MapOfMines[i+1][j+1]++;
                
            }
        }
    }
}

void Open_cell_1(int r, int c)
{
    if(Status[r][c] == 0)
        Status[r][c] = 1;
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

int Inside_MapOfMines_Check(int i,int j){
    if((0<=i && i<=M)&&(0<=j&&j<=N)) return 1;
    return 0;
}