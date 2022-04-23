#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define MINE -1

void PrintMap(int Rmax, int Cmax, int M[][Cmax], int S[][Cmax]);     // Print map //

void CountMines(int Rmax, int Cmax, int M[][Cmax]);                  // Check around //

void Open_cell(int Rmax, int Cmax, int r, int c, int M[][Cmax], int S[][Cmax]);          // Open cell //

int Count_remain(int Rmax, int Cmax,int S[][Cmax]);                // Check the empty cells //

void openAll(int Rmax, int Cmax, int S[][Cmax]);                    // Open all cells //

int Open_check(int Cmax, int r, int c, int S[][Cmax]);                        // Check cell's status //

void Init_mines(int Rmax, int Cmax, int k, int M[][Cmax], int S[][Cmax]);          // Create mines //

int main()
{
    int Rmax,Cmax,k;
    int Mod;
    printf("Game Mode\n1. Easy(Type 1)\n2. Medium(Type 2)\n3. Hardcore(Type 3)\n");
    scanf("%d",&Mod);
    switch (Mod)
    {
    case 1:
        Rmax=9;
        Cmax=9;
        k=10;
        break;
    
    case 2:
        Rmax=15;
        Cmax=15;
        k=15;
        break;

    case 3:
        Rmax=25;
        Cmax=15;
        k=75;
        break;
    }
    int M[Rmax][Cmax];
    int S[Rmax][Cmax];
    int r,c;
    Init_mines(Rmax, Cmax, k, M, S);
    CountMines(Rmax, Cmax, M);
    while(1)
    {
        PrintMap(Rmax, Cmax, M, S);
        do {
            do {
                fflush(stdin);
                printf("Choose your cell(Row-> Column): ");
                scanf("%d%d", &r, &c);
            }
            while(Open_check(Cmax, r, c, S)==1);
        }
        while(r>Rmax-1 || r<0 || c>Cmax-1 || c<0);

        if(M[r][c] == MINE) {
            openAll(Rmax, Cmax, S);
            PrintMap(Rmax, Cmax, M, S);
            printf("\n#---------- YOU FK NOOBBBBBBBBBBBB ----------#\n      #---------- GAME OVER ----------#\n");
            break;
        }
        Open_cell(Rmax, Cmax, r, c, M, S);
        if(Count_remain(Rmax, Cmax, S) == k)
        {
            openAll(Rmax, Cmax, S);
            PrintMap(Rmax, Cmax, M, S);
            printf("\n#---------- Congratulations ----------#\n    #---------- YOU WIN ----------#\n");
            break;
        }
    }
    getch();
    return 0;
}

void PrintMap(int Rmax, int Cmax, int M[][Cmax], int S[][Cmax])
{
    int i,j;
    printf("   ");
    for(j=0;j<Cmax;j++)
        printf("%2d ",j);
    printf("\n");
    for(i=0;i<Rmax;i++)
    {
        printf("%2d ",i);
        for(j=0;j<Cmax;j++)
        {
            if(S[i][j]==0) printf(" # ");
            else if(S[i][j]==1 && M[i][j]==0) printf(" . ");
            else if(S[i][j]==1 && M[i][j]!=MINE) printf(" %d ",M[i][j]);
            else if(S[i][j]==1 && M[i][j]==MINE) printf(" x ");
        }

        printf("\n");
    }
}

void CountMines(int Rmax, int Cmax,int M[][Cmax])
{
    int i,j;

    for(i=0;i<Rmax;i++)
    {
        for(j=0;j<Cmax;j++)
        {
            if(M[i][j]!=MINE)
            {
                int cnt=0;
                if(i-1>=0 && j-1>=0 && M[i-1][j-1] == MINE)
                    cnt++;
                if(i-1>=0  && M[i-1][j] == MINE)
                    cnt++;
                if(i-1>=0 && j+1<Cmax && M[i-1][j+1] == MINE)
                    cnt++;
                if( j-1>=0 && M[i][j-1] == MINE)
                    cnt++;
                if(j+1<Cmax && M[i][j+1] == MINE)
                    cnt++;
                if(i+1<Rmax && j-1>=0 && M[i+1][j-1] == MINE)
                    cnt++;
                if(i+1<Cmax && M[i+1][j] == MINE)
                    cnt++;
                if(i+1<Cmax && j+1<Rmax && M[i+1][j+1] == MINE)
                    cnt++;
                M[i][j]=cnt;
            }
        }
    }
}

void openAll(int Rmax, int Cmax, int S[][Cmax])
{
    int i,j;
    for(i=0;i<Rmax;i++)
    {
        for(j=0;j<Cmax;j++)
        {
            S[i][j] = 1;
        }
    }
}

int Count_remain(int Rmax, int Cmax, int S[][Cmax])
{
    int cnt = 0;
    int i,j;
    for(i=0;i<Rmax;i++)
    {
        for(j=0;j<Cmax;j++)
        {
            if(S[i][j] == 0)
                cnt++;
        }
    }
    return cnt;
}

int Open_check(int Cmax, int r, int c, int S[][Cmax])
{
    if(S[r][c] == 1)
        return 1;
    else return 0;
}

void Open_cell(int Rmax, int Cmax, int r, int c, int M[][Cmax], int S[][Cmax]) 
{
    if(r<0 || r>=Rmax || c<0 || c>=Cmax)
        return;
    if(S[r][c] == 1)
        return;
    S[r][c] = 1;
    if(M[r][c] > 0)
    {
        S[r][c] = 1;
        return;
    }
    else if(M[r][c] == 0)
    {
        Open_cell(Rmax, Cmax,r-1, c-1, M, S);
        Open_cell(Rmax, Cmax,r-1, c, M, S);
        Open_cell(Rmax, Cmax, r-1, c+1, M, S);
        Open_cell(Rmax, Cmax, r, c-1, M, S);
        Open_cell(Rmax, Cmax, r, c+1, M, S);
        Open_cell(Rmax, Cmax, r+1, c-1, M, S);
        Open_cell(Rmax, Cmax, r+1, c, M, S);
        Open_cell(Rmax, Cmax, r+1, c+1, M, S);
    }

}

void Init_mines(int Rmax, int Cmax, int k, int M[][Cmax], int S[][Cmax])
{
    srand(time(0));
    int i,j;
    for(i=0;i<Rmax;i++)
    {
        for(j=0;j<Cmax;j++)
        {
            M[i][j]=0;
            S[i][j]=0;
        }
    }
    int cnt=0;
    for(i=0;i<k;i++)
    {
        int r= rand()%Rmax;
        int c =rand()%Cmax;
        if(M[r][c] == 0)
        {
            M[r][c] = MINE;
            cnt++;
        }
    }
    return;
}
