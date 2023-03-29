/******************************************************************************
Bingo - Aniv Surana

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int search2D(int c[5][5],int x);
int search1D(int a[],int x);
void printCard(int c[5][5]);
char getLetter(int x);
int findrow(int c[5][5],int x);
int findcol(int c[5][5],int x);
int bingoRow(int c[5][5]);
int bingoCol(int c[5][5]);
int bingoDiag(int c[5][5]);
void fillCard(int c[5][5]);
int Generate(); 


int main(void)
{ 
    int card[5][5];
    fillCard(card);
    
    int BINGO = 0;
    int i=0;
    int nlist[75];
    while(bingoRow(card)!=1 && bingoCol(card)!=1 && bingoDiag(card)!=1 && i<75)
    {
        printf("\n\n");
        printCard(card);
        nlist[i] = Generate();
        while(search1D(nlist,nlist[i])!=i)
        {
            nlist[i] = Generate();
        }
        printf("\nThe next number is %c%d \n\n",getLetter(nlist[i]),nlist[i]);
        printf("Do you have it? (Y/N) ");
        char p;
        scanf(" %c",&p);
        //p='Y';
        if(p=='Y')
        {
            if((search2D(card,nlist[i])==1))
            {
                printf("You got it!\n\n");
                int foundr = findrow(card,nlist[i]);
                int foundc = findcol(card,nlist[i]);
                if(foundr>-1 && foundc>-1)
                {
                    card[foundr][foundc] = 0; //implying that it is been marked off
                }
                
            }
            else 
            {
                printf("That value is not on your BINGO card - are you trying to cheat??\n\n");
            }
        }
        i++;
        
    }
    
    printCard(card);
    if(bingoRow(card) == 1 && bingoCol(card) == 1)
    {
        printf("\n\nYou filled out a row and a column! BINGO!\n\n");
    }
    else if(bingoRow(card) == 1)
    {
        printf("\n\nYou filled out a row! BINGO!\n\n");
    }
    else if(bingoCol(card) == 1)
    {
        printf("\n\nYou filled out a column! BINGO!\n\n");
    }
    else if(bingoDiag(card) == 1)
    {
        printf("\n\nYou filled out a diagonal! BINGO!\n\n");
    }
    else
    {
        printf("\nAll 75 numbers have been called out! And unfortunately you haven't won. Maybe you made a mistake? :(\n");
    }
    
    return 0;
}

void fillCard(int c[5][5])
{

    srand(time(0));
    for (int i = 0; i < 5; i++)
    { 
        for(int j = 0; j < 5; j++)
        {
            int num=(rand() % 15) + 1 +(i*15);
            int check = search2D(c,num);
            if(check==0)
            {
                c[j][i]=num;
            }
            else
            {
                j--; //makes the program get a new number, rather than creating a while loop
            }
        }
    }
    c[2][2] = 0;
}

int search2D(int c[5][5],int x)
{
    int f = 0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(x==c[i][j])
            {
                f=1;
            }
        }
    }
    return f;
}
int search1D(int a[],int x)
{
    int f=-1;
    for(int i=0;i<75;i++)
    {
        if(a[i]==x && f==-1) // searching for the first occurrence of the number
        {    
            f=i;
        }
    }
    return f;
}

void printCard(int c[5][5])
{
    printf("%8c %8c %8c %8c %8c\n",'B','I','N','G','O');
    printf("  ----------------------------------------------\n");
    for(int i=0;i<5;i++)
    {
        printf(" %2c",'|');
        for(int j=0;j<5;j++)
        {
            if(c[i][j]>0)
            {
                printf("%5d %3c", c[i][j],'|');
            }
            else
            {
                printf("%5c %3c",'X','|');
            }
            
        }
        printf("\n");
        printf("  ----------------------------------------------\n");
    }
}

char getLetter(int x)
{
    if(x<=15)
    {
        return 'B';
    }
    else if(x<=30)
    {
        return 'I';
    }
    else if(x<=45)
    {
        return 'N';
    }
    else if(x<=60)
    {
        return 'G';
    }
    else 
    {
        return 'O';
    }
}
int findrow(int c[5][5],int x)
{
    if(search2D(c,x)==0)
    {
        return -1;
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
            {
                if(c[i][j]==x)
                return i;
            }
        }
    }
}
int findcol(int c[5][5],int x)
{
    int r=findrow(c,x);
    if(r>=0)
    {
        for(int i=0;i<5;i++)
        {
            if(c[r][i]==x)
                return i;
        }
    }
    else
    {
        return -1;
    }
}
int bingoRow(int c[5][5])
{
    int f=0;
    for(int i=0;i<5;i++)
    {
        int count = 0;
        for(int j=0;j<5;j++)
        {
            if(c[i][j]==0)
            {
                count++;
            }
        }
        if(count == 5)
            f=1;
    }
    return f;
}

int bingoCol(int c[5][5])
{
    int f=0;
    for(int i=0;i<5;i++)
    {
        int count = 0;
        for(int j=0;j<5;j++)
        {
            if(c[j][i]==0)
            {
                count++;
            }
        }
        if(count == 5)
            f=1;
    }
    return f;
}

int bingoDiag(int c[5][5]) 
{
    int f=0;
    int count1=0;
    int count2=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(i==j && c[i][j]==0)
            {
                count1++;
            }
            if(i+j==4 && c[i][j]==0)
            {
                count2++;
            }
        }
        if(count1 == 5 || count2==5)
            f=1;
    }
    return f;
}



int Generate()
{
    int x = (rand() % 75) +1;
    return x;
}








