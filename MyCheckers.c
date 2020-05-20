/*
Machine Project for CCDSTRU

ALBA, Axel
NOVEDA, Denver
TAN, Christian
*/
#include <stdio.h>
#include <stdlib.h>

#define MAXROW 8
#define MAXCOL 8


struct coord
{
	int x;
	int y;
};

void printBoard(char board[][MAXCOL])
{
	int i, j;
	
	printf("\n");
	printf("  ");
	for(j = 0; j < MAXCOL; j++)
		printf("%d", j + 1);
		
	printf("\n");	
	for(i = 0; i < MAXROW; i++)
	{
		printf ("%d ", i + 1);
		for(j = 0; j < MAXCOL; j++)
		{
			if (board[i][j]=='X')
			{
				printf("\xDB");
			}
			else printf("%c", board[i][j]);
		}
		printf("\n");
	}
	
}

int check(struct coord prev, struct coord next, char board[][MAXCOL], int aTurn)
{	
	int valid = 1;
	
	if(next.x - prev.x > 1 || prev.x - next.x > 1) // Players may only move one space from previous position 
		valid =  0;
	if(next.y - prev.y > 1 || prev.y - next.y > 1) // Players may only move one space from previous position
		valid =  0;	
	if(board[prev.x][prev.y] == board[next.x][next.y]) // Previous and next coordinates should not be the same
		valid = 0;		
	if(board[prev.x][prev.y] == 'A' && next.x < prev.x ) // Alpha cannot go back upwards 
		valid = 0;
	if(board[prev.x][prev.y]== 'B' && next.x > prev.x) // Beta cannot go back downwards
		valid = 0;		
	if(board[prev.x][prev.y] == 'A' && board[next.x][next.y]== 'A') // Player cannot move to spaces with allied pieces  
		valid = 0;													    
	if(board[prev.x][prev.y] == 'B' && board[next.x][next.y]== 'B') // Player cannot move to spaces with allied pieces
		valid = 0;	
	if(aTurn == 1 && board[prev.x][prev.y] == 'B') // Beta cannot move while it is Alpha's turn
		valid = 0;
	if(aTurn == 0 && board[prev.x][prev.y] == 'A') // Alpha cannot move while it is Beta's turn
		valid = 0;
	if(board[next.x][next.y] == 'X') // Players cannot move on X spaces
		valid = 0;
		
	return valid;
}

int main()
{
	struct coord prev;
	struct coord next;
	char board[MAXROW][MAXCOL] = {{'X','A','X','A','X','A','X','A'},
								  {'A','X','A','X','A','X','A','X'},
								  {'X','A','X','A','X','A','X','A'},
								  {' ','X',' ','X',' ','X',' ','X'},
								  {'X',' ','X',' ','X',' ','X',' '},
								  {'B','X','B','X','B','X','B','X'},
								  {'X','B','X','B','X','B','X','B'},
								  {'B','X','B','X','B','X','B','X'}};	
	
	int over = 0;
	int ok = 0;
	int aTurn = 1;
	int nAlpha = 12;
	int nBeta = 12;	
	
	while(over == 0)//over == 0 means game is still on going, while over == 1 means game over
	{
		
		//changes color depending on who's turn is it, would only clear screen if the move is valid
		if(aTurn == 1) 
		{
			if (ok == 1) system ("cls");
			system ("COLOR F1");
			printf("Remaining A pieces: %d \n", nAlpha);
			printf("Remaining B pieces: %d \n", nBeta);
			printf("\nAlpha's Turn\n");
		}
		else 
		{
			if (ok == 1) system ("cls");
			system ("COLOR F4");
			printf("Remaining A pieces: %d \n", nAlpha);
			printf("Remaining B pieces: %d \n", nBeta);
			printf("\nBeta's Turn\n");
		}
		
		printBoard(board);
		
		printf("\nEnter previous row coordinate: ");
		scanf("%d", &prev.x);
		prev.x--;
		printf("Enter previous column coordinate: ");
		scanf("%d", &prev.y);
		prev.y--;
		printf("\nEnter next row coordinate: ");
		scanf("%d", &next.x);
		next.x--;
		printf("Enter next column coordinate: ");
		scanf("%d", &next.y);
		next.y--;
		
		if(check(prev, next, board, aTurn) == 0)
		{
			printf("\nINVALID MOVE!\n");	
			ok = check(prev, next, board, aTurn);
		}
		else ok = check(prev, next, board, aTurn); //line 126 & 128 updates the "ok" if it is valid or not.
		
			
			
		if(ok && aTurn && (board[next.x][next.y] == ' ' || board[next.x][next.y] == 'B'))
		{
			board[prev.x][prev.y] = ' ';
			if (board[next.x][next.y] == 'B') 
			{	
				if (board[next.x + 1][next.y-1] == 'B' || board[next.x + 1][next.y+1] == 'B' || next.x == 7) aTurn = 1; // this is for combo 
				else aTurn = 0;//if alpha ate beta but no combo after
				
				nBeta--;
			}
			else if (board[next.x][next.y] == ' ') aTurn = 0; //if free space
			board[next.x][next.y] = 'A'; // this one updates the move of alpha visually	
		}
		
		else if(ok && !aTurn && (board[next.x][next.y] == ' ' || board[next.x][next.y] == 'A'))
		{
			board[prev.x][prev.y] = ' '; 
			
			if (board[next.x][next.y] == 'A') 
			{
				if (board[next.x - 1][next.y-1] == 'A' || board[next.x - 1][next.y+1] == 'A' || next.x == 0) aTurn = 0; // this is for combo 
				else aTurn = 1; //if beta ate alpha but no combo after
				
				nAlpha--;
			}
			
			else if (board[next.x][next.y] == ' ') aTurn = 1; //if free space
			board[next.x][next.y] = 'B'; // this one updates the move of beta visually
		}
		
		if(nAlpha == 0 || nBeta == 0) // for pawn pieces
		{
			over = 1;
			printf("Game Over!!!!\n");
			
			if(nBeta == 0)
				printf("Alpha Wins!\n");
			if(nAlpha == 0)
				printf("Beta Wins!\n");
		
		}
	}	
	
	return 0;
}
