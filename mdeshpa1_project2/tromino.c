
/**
 * The source file contains the code for Tromino Tiling algorithm.
 */

// standard header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Represents the tile cell
 */
int tileR;

// function prototypes 
void trominoTile(int boardSize, int R, int C, int xBoard, int yBoard, int tSize, int tileBoard[tSize][tSize]);
void displayTrominoTileMatrix(int boardSize, int tileBoard[boardSize][boardSize]);

// main entry function
int main(int argc, char *argv[])
{

	int K = atoi(argv[1]);		// input value of K
	int R = atoi(argv[2]);		// input value of x missing position
	int C = atoi(argv[3]);		// input value of y missing position
	if(K < 1)
	{
		fprintf(stdout, "Invalid K Input Size\n");
		exit(EXIT_FAILURE);
	}
	if(argc != 4)
	{
		fprintf(stdout, "Invalid Input Arguments\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		int boardSize = pow(2, K);
		tileR = 0;										// tile representative counter
		
		int tileBoard[boardSize][boardSize];							// tile board
		for(int firstCounter = 0; firstCounter < boardSize; firstCounter++)
			for(int secondCounter = 0; secondCounter < boardSize; secondCounter++)
				tileBoard[firstCounter][secondCounter] = 0;				// initialize 		


		R = R - 1;
		C = C - 1;
		tileBoard[R][C] = -1;									// missing hole
		
		trominoTile(boardSize, R, C, 0, 0, boardSize, tileBoard);				// tromino recursive function
		displayTrominoTileMatrix(boardSize, tileBoard);			
	}
	return 0;
}


/**
 * The function is used to perform tromino tile algorithm computation
 */
void trominoTile(int boardSize, int R, int C, int xBoard, int yBoard, int tSize, int tileBoard[tSize][tSize])
{
	if(boardSize == 2)
	{
		tileR++;
		for(int firstCounter = xBoard; firstCounter < (xBoard + boardSize); firstCounter++)	
			for(int secondCounter = yBoard; secondCounter < (yBoard + boardSize); secondCounter++)	
				if(!(firstCounter == R && secondCounter == C))
					tileBoard[firstCounter][secondCounter] = tileR;

		return;
	}
	
	tileR++;
	int divBoardSize = boardSize/2, xCenter, yCenter;
	int xUpperR, yUpperR, xUpperL, yUpperL, xLowerR, yLowerR, xLowerL, yLowerL;
	xCenter = xBoard + divBoardSize;
	yCenter = yBoard + divBoardSize;

	// checking hole in the first quadrant
	if(R < xCenter && C < yCenter)
	{
		tileBoard[xCenter - 1][yCenter] = tileBoard[xCenter][yCenter -1] = tileBoard[xCenter][yCenter] = tileR;
		xUpperL = R;
		yUpperL = C;

		xUpperR = xCenter - 1;
		yUpperR = yCenter;

		xLowerL = xCenter;
		yLowerL = yCenter - 1;

		xLowerR = xCenter;
		yLowerR = yCenter;
	
	}
	// checking hole in the second quadrant
	else if(R < xCenter && C >= yCenter)
	{
		tileBoard[xCenter - 1][yCenter - 1] = tileBoard[xCenter][yCenter -1] = tileBoard[xCenter][yCenter] = tileR;
                xUpperL = xCenter - 1;
                yUpperL = yCenter - 1;

                xUpperR = R;
                yUpperR = C;

                xLowerL = xCenter;
                yLowerL = yCenter - 1;

                xLowerR = xCenter;
                yLowerR = yCenter;

	}
	// checking hole in third quadrant
	else if(R >= xCenter && C < yCenter)
	{
		tileBoard[xCenter - 1][yCenter - 1] = tileBoard[xCenter - 1][yCenter] = tileBoard[xCenter][yCenter] = tileR;
                xUpperL = xCenter - 1;
                yUpperL = yCenter - 1;

                xUpperR = xCenter - 1;
                yUpperR = yCenter;

                xLowerL = R;
                yLowerL = C;

                xLowerR = xCenter;
                yLowerR = yCenter;

	}
	// checking hold in last quad
	else if(R >= xCenter && C >= yCenter)
	{
		tileBoard[xCenter - 1][yCenter - 1] = tileBoard[xCenter - 1][yCenter] = tileBoard[xCenter][yCenter - 1] = tileR;
                xUpperL = xCenter - 1;
                yUpperL = yCenter - 1;

                xUpperR = xCenter - 1;
                yUpperR = yCenter;

                xLowerL = xCenter;
                yLowerL = yCenter - 1;

                xLowerR = R;
                yLowerR = C;

	}		

	// recursive call to all four quadrants
	trominoTile(divBoardSize, xUpperL, yUpperL, xBoard, yBoard, tSize, tileBoard);
	trominoTile(divBoardSize, xUpperR, yUpperR, xBoard, yBoard + divBoardSize, tSize, tileBoard);
	trominoTile(divBoardSize, xLowerL, yLowerL, xBoard + divBoardSize, yBoard, tSize, tileBoard);
	trominoTile(divBoardSize, xLowerR, yLowerR, xBoard + divBoardSize, yBoard + divBoardSize, tSize, tileBoard);
}

/**
 * The function is used to display the tromino tiles representation
 */
void displayTrominoTileMatrix(int boardSize, int tileBoard[boardSize][boardSize])
{
	for(int firstCounter = 0; firstCounter < boardSize; firstCounter++) {		
		for(int secondCounter = 0; secondCounter < boardSize; secondCounter++)  {
			if(tileBoard[firstCounter][secondCounter] != (-1))
			{
				fprintf(stdout, "%d\t", tileBoard[firstCounter][secondCounter]);
			}
			else
			{
				fprintf(stdout, "X\t");
			}
		}
		fprintf(stdout, "\n");
	}						
	fprintf(stdout, "\n");
}

