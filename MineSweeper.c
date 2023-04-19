//hagi pinkasovich 208065284

#include "mineSweeper.h"
#include "colorPrint.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


bool initBoard (GameBoard * g, int rows, int cols, int level) //function that init the game
{
  g->cols = cols;
  g->rows = rows;
  Tile **initBoard = NULL;
  initBoard = (Tile **) malloc (rows * sizeof (Tile *));
  if (initBoard == NULL)
    return FALSE;
  for (int i = 0; i < rows; i++)
    {
      initBoard[i] = (Tile *) malloc (cols * sizeof (Tile));
      if (initBoard[i] == NULL)
	return FALSE; //if this dosnt work return false
    }
  for (int i = 0; i < rows; i++) //init all the tiles in the board
    {
      for (int j = 0; j < cols; j++)
	{
	  initBoard[i][j].isFlagged = FALSE;
	  initBoard[i][j].isMine = FALSE;
	  initBoard[i][j].isVisible = FALSE;
	  initBoard[i][j].numOfMines = 0;
	}
    }
  g->board = initBoard;
  g->isMineClicked = FALSE;
  g->hiddenTiles = g->rows * g->cols; 
  populateMines (g, level); //put mines on the board
  markNumbers (g); //mark the num of mines
}

void populateMines (GameBoard * g, int level) //put mines on the board
{
  int mines = 0;
  if (level == EASY)
    mines = EASY_LEVEL_PERCENT * g->hiddenTiles;
  if (level == MEDIUM)
    mines = MEDIUM_LEVEL_PERCENT * g->hiddenTiles;
  if (level == HARD)
    mines = HARD_LEVEL_PERCENT * g->hiddenTiles;

  mines = mines / 100;
  g->totalMines = mines;
  while (mines > 0) //randomly puts mines
    {
      //    srand(time(NULL));
      int x = rand () % g->rows;
      int y = rand () % g->cols;
      if (g->board[x][y].isMine == FALSE)
	{
	  g->board[x][y].isMine = TRUE;
	  g->board[x][y].numOfMines = -1;
	  mines--;
	}
    }
}

void markNumbers (GameBoard * g) //mark the num of the mines near the tile 
{

  for (int i = 0; i < g->rows; i++)
    {
      for (int j = 0; j < g->cols; j++)
	{
	  if (g->board[i][j].isMine == TRUE)
	    {
	      if ((i - 1) >= 0)
		{
		  if (g->board[i - 1][j].isMine == FALSE)
		    g->board[i - 1][j].numOfMines++;	// up 
		  if ((j - 1) >= 0)
		    {
		      if (g->board[i - 1][j - 1].isMine == FALSE)
			g->board[i - 1][j - 1].numOfMines++;	//up left
		    }
		  if ((j + 1) < g->cols)
		    {
		      if (g->board[i - 1][j + 1].isMine == FALSE)
			g->board[i - 1][j + 1].numOfMines++;	//up right
		    }
		}
	      if ((i + 1) < (g->rows))
		{
		  if (g->board[i + 1][j].isMine == FALSE)
		    g->board[i + 1][j].numOfMines++;	//down
		  if ((j + 1) < g->cols)
		    {
		      if (g->board[i + 1][j + 1].isMine == FALSE)
			g->board[i + 1][j + 1].numOfMines++;	//down right
		    }
		  if ((j - 1) >= 0)
		    {
		      if (g->board[i + 1][j - 1].isMine == FALSE)
			g->board[i + 1][j - 1].numOfMines++;	//down left
		    }
		}
	      if ((j + 1) < g->cols)
		{
		  if (g->board[i][j + 1].isMine == FALSE)
		    g->board[i][j + 1].numOfMines++;	//right
		}
	      if ((j - 1) >= 0)
		{
		  if (g->board[i][j - 1].isMine == FALSE)
		    g->board[i][j - 1].numOfMines++;	//left
		}
	    }
	}
    }
}

void clickTile (GameBoard * g, int row, int col) //function that do the click on the tile
{
  if ((g->board[row][col].isVisible == FALSE)
      && (g->board[row][col].isFlagged == FALSE)) //if not Visible and not Flagged
    {
      g->board[row][col].isVisible = TRUE;

      if ((g->board[row][col].isMine == TRUE))	//if the player clicked on mine
	{
	  g->isMineClicked = TRUE;
	}
      else if (g->board[row][col].numOfMines > 0)
	{
	  g->hiddenTiles--;	//we discovered a new tile 
	}
      else			//num of mine is 0
	{
	  g->board[row][col].isVisible = TRUE;

	  //if the down tile is covered AND it s not a mine AND it s possible to go down
	  if ((row < (g->rows - 1)) && (g->board[row + 1][col].isMine != TRUE)	//down
	      && (g->board[row + 1][col].isVisible != TRUE))
	    {
	      clickTile (g, row + 1, col);
	    }
	  if ((row > 0) && (g->board[row - 1][col].isMine != TRUE)	//up
	      && (g->board[row - 1][col].isVisible != TRUE))
	    {
	      clickTile (g, row - 1, col);
	    }
	  if ((col < (g->cols - 1)) && (g->board[row][col + 1].isMine != TRUE)	//right
	      && (g->board[row][col + 1].isVisible != TRUE))
	    {
	      clickTile (g, row, col + 1);
	    }
	  if ((col > 0) && (g->board[row][col - 1].isMine != TRUE)	//left
	      && (g->board[row][col - 1].isVisible != TRUE))
	    {
	      clickTile (g, row, col - 1);
	    }
	    //
	    
	    	  if ((col > 0) && (row > 0) && (g->board[row-1][col - 1].isMine != TRUE)	//up left
	      && (g->board[row-1][col - 1].isVisible != TRUE))
	    {
	      clickTile (g, row -1 , col - 1);
	    }
	       
	    	  if ((col < (g->cols - 1)) && (row > 0) && (g->board[row-1][col + 1].isMine != TRUE)	//up right
	      && (g->board[row-1][col + 1].isVisible != TRUE))
	    {
	      clickTile (g, row -1 , col + 1);
	    }

          if ((col < (g->cols - 1)) && (row < (g->rows - 1)) && (g->board[row+1][col + 1].isMine != TRUE)
	      && (g->board[row+1][col + 1].isVisible != TRUE)) //down right
	    {
	      clickTile (g, row+1, col + 1);
	    }
	    
	            if ((col >0) && (row < (g->rows - 1)) && (g->board[row+1][col - 1].isMine != TRUE)
	      && (g->board[row+1][col - 1].isVisible != TRUE)) //down left
	    {
	      clickTile (g, row+1, col - 1);
	    }
	  g->hiddenTiles--;
	}
    }
}

void flagTile (GameBoard * g, int row, int col) //function that flag a tile 
{
  if (g->board[row][col].isVisible == TRUE)
    return;
  if (g->board[row][col].isFlagged == TRUE)
    {
      g->board[row][col].isFlagged = FALSE;
      return;
    }
  g->board[row][col].isFlagged = TRUE;
}

void printBoard (GameBoard * g, int cursorCoords[2]) //function that print the board with pointer
{
  for (int i = 0; i < g->rows; i++)
    {
      for (int j = 0; j < g->cols; j++)
	{
	  if (j != 0)
	    printf (" "); //if we not in the first 
	  if (g->board[i][j].isVisible == TRUE
	      && g->board[i][j].numOfMines != -1) //if its visable and not mine print the numOfMines in white on blue
	    {
	      char s[1000] = "";
	      int num = g->board[i][j].numOfMines;
	      sprintf (s, "%d", num);
	       if(num<10)
	      strcat (s, " ");
	      if (i == cursorCoords[0] && j == cursorCoords[1]) //if its the pointer back is yellow
		colorPrint (FG_White, BG_Yellow, ATT_Scratch, s);
	      else
		colorPrint (FG_White, BG_Blue, ATT_Scratch, s);
	      continue;
	    }
	  if (g->board[i][j].isFlagged == TRUE)//if its flag white on red
	    {
	      if (i == cursorCoords[0] && j == cursorCoords[1])//if its the pointer back is yellow
		colorPrint (FG_White, BG_Yellow, ATT_Def, "F ");
	      else
		colorPrint (FG_White, BG_Red, ATT_Def, "F ");
	      continue;
	    }
	  if (g->board[i][j].isVisible == FALSE) //if its not visable so print "  " on blue
	    {
	      if (i == cursorCoords[0] && j == cursorCoords[1])
		colorPrint (FG_Blue, BG_Yellow, ATT_Def, "  ");	//pointer in yellow
	      else
		colorPrint (FG_Blue, BG_Blue, ATT_Def, "  ");	//blue not seen
	      continue;
	    }
	}
      printf ("\n\n"); //down line
    }
}