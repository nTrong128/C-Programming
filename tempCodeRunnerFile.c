 || c<0 || c>=Cmax)
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
