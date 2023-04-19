//hagi pinkasovich 208065284

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "mineSweeper.h"
#include "colorPrint.h"
#include "getch.h"

int main()
{
    srand(time(NULL));
    printf("enter rows\n");
    int rows=0;
    scanf("%d",&rows); 
    printf("enter cols\n");
    int cols=0;
    scanf("%d",&cols); 
    if(rows>MAX_BOARD_DIM)
    rows=MAX_BOARD_DIM;
    if(cols>MAX_BOARD_DIM)
    cols=MAX_BOARD_DIM;
    if(rows<=0)
    rows=4;
    if(cols<=0)
    cols=4;
    printf("enter difficulty\n");
    int difficulty=0;
    scanf("%d",&difficulty);
    if(difficulty>HARD)
    difficulty=HARD;
    if(difficulty<EASY)
    difficulty=EASY;
	GameBoard g;
	if (initBoard(&g, rows, cols, difficulty) == FALSE)
	{
		printf("eror");
		return 1;
	}
	int pointer[]={0,0} ;
	char click = 'p';
	click=getch();
    while(TRUE)
    {
    clearScreen();
    printf("\nenter move q to exit\n");
    printBoard(&g,pointer);
    click=getch();
    if(click==QUIT)
    {
    printf("game quit");
    break;
    }
    if(click==FLAG_TILE)
    {
        flagTile(&g,pointer[0],pointer[1]);
        continue;
    }
    if(click==CLICK_TILE)
    {
        clickTile(&g,pointer[0],pointer[1]);
        if(g.isMineClicked==TRUE)
        {
            printf("game over");
            break;
        }
        if(g.totalMines==g.hiddenTiles)
        {
            clearScreen();
            printBoard(&g,pointer);
            printf("game win");
            break;
        }
    }
    if(click==UP)
    {
        if((pointer[0]-1)>=0)
        pointer[0]=pointer[0]-1;
        continue;
    }
     if(click==DOWN)
    {
        if((pointer[0]+1)<g.rows)
        pointer[0]=pointer[0]+1;
        continue;
    }
    if(click==RIGHT)
    {
        if((pointer[1]+1)<g.cols)
        pointer[1]=pointer[1]+1;
        continue;
    }
     if(click==LEFT)
    {
        if((pointer[1]-1)>=0)
        pointer[1]=pointer[1]-1;
        continue;
    }
    }
    
    
    //free all the arrays
	for (int i = 0; i < g.cols; i++)
	{
		free(g.board[i]);
	}
	free(g.board);
    return 0;
}
