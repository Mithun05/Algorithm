
/**
 * Source code to implement 0/1 Knapsack problem using Dynamic Programming Approach 
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>


/**
 * An error handling 
 */
 extern int errno;

 /**
  * A Max total number of items 
  */
 #define MAXITEM 20 


 /**
  * An items details structure
  */
 typedef struct ItemDetails {

        int itemId;
        int itemWeight;
        int itemProfit;

 } ItemDetails;


 /**
  * A static array to max number of items
  */
 ItemDetails itemDetails[MAXITEM];

 /**
  * A total number of items
  */
 int totalNoOfItems;

 /**
  * A total capacity
  */
 int totalKnapCapacity;

 /**
  * Knapsack table
  */
 int knapSackTable[MAXITEM][MAXITEM];

/**
 * Read Knapsack text file
 */

 void readKnapsackFile(char *fileName)
 {
        FILE *filp = NULL;
        char *bufStore = NULL;
        size_t bufSize = 0;
        ssize_t lineRead;
        int err;
        int lineNo = 0;

        filp = fopen(fileName, "r");
        if(filp == NULL)
        {
                err = errno;
                fprintf(stderr, "Error opening file: %s\n", strerror(err));
                exit(EXIT_FAILURE);
        }

        while((lineRead = getline(&bufStore, &bufSize, filp)) != -1)
        {
                switch(lineNo)
                {
                        case 0:
                                totalNoOfItems = atoi(bufStore);
                                lineNo++;
                                break;
                        case 1: ;
                                int id = 1;
                                char *line = NULL;
                                line = strtok(bufStore, ",");
                                while(line)
                                {
                                        itemDetails[id].itemId = id;
                                        itemDetails[id].itemWeight = atoi(line);
                                        id++;
                                        line = strtok(NULL, ",");
                                }
                                lineNo++;
                                break;
                        case 2: ;
                                int idI = 1;
                                char *lineI = NULL;
                                lineI = strtok(bufStore, ",");
                                while(lineI)
                                {
                                        itemDetails[idI].itemProfit = atoi(lineI);
                                        idI++;
                                        lineI = strtok(NULL, ",");
                                }
                                lineNo++;
                                break;
                        case 3: ;
                                totalKnapCapacity =atoi(bufStore);
                                break;
                        default:
                                fprintf(stderr, "File empty\n");
                                break;

                }
        }

        fclose(filp);

        if(bufStore)
            free(bufStore);
}


/**
 * A function returns a maximum of two integers
 */ 
 int max(int maxOne, int maxTwo)
 {
	return (maxOne > maxTwo) ? maxOne : maxTwo;
 }


 /**
  * Dislay finalKnapsack Output
  */
 void displayKnapSackOutput()
 {
	int n = totalNoOfItems;
	int w = totalKnapCapacity;
	int maxWeight = 0;

	while((n > 0) && (w > 0))
	{
        	if(knapSackTable[n][w] != knapSackTable[n - 1][w])
		{
			    maxWeight += itemDetails[n].itemWeight;	
 			    fprintf(stdout, "\t\t Item Id : %d Item Weight : %d Item Profit : %d \n", n, itemDetails[n].itemWeight, itemDetails[n].itemProfit);
  			    w -= itemDetails[n].itemWeight;
			    n--;
        	}
        	else 
		{
            		    n--;
         	}
    	}

	fprintf(stdout, "\n");
    	fprintf(stdout, "\t\t Maximum Weight : %d\n", maxWeight);
 
 }

/**
 * Dynamic programming algorithm to solve 0/1 knapsack problem 
 * and returns maximum profit
 */
 void dynProgKnapSackMethod()
 {
	/**
	 * Initialization of an array
	 */

	for(int i = 0; i <= totalKnapCapacity; i++)
                knapSackTable[0][i] = 0;
 
	for(int i = 1; i <= totalNoOfItems; i++)
		knapSackTable[i][0] = 0;
	
	/**
	 * Build up knapsack table in bottom up manner
	 */	
 	for(int i = 1; i <= totalNoOfItems; i++) 
		for(int j = 1; j <= totalKnapCapacity; j++)
			if(itemDetails[i].itemWeight <= j)
				if((itemDetails[i].itemProfit + knapSackTable[i - 1][j - itemDetails[i].itemWeight]) > knapSackTable[i - 1][j])
					knapSackTable[i][j] = itemDetails[i].itemProfit + knapSackTable[i - 1][j - itemDetails[i].itemWeight]; 
				else			
					knapSackTable[i][j] = knapSackTable[i - 1][j];
			else 
				knapSackTable[i][j] = knapSackTable[i - 1][j];

        fprintf(stdout, "\t\t Maximum Profit : %d\n", knapSackTable[totalNoOfItems][totalKnapCapacity]);

	displayKnapSackOutput();
 }
 

/**
 * main driver program
 */
int main(int argc, char *argv[])
{

        readKnapsackFile(argv[1]);
 	dynProgKnapSackMethod();	
        
	return 0;
}

// end of main driver program


