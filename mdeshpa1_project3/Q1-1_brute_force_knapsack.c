
/**
 * A brute force approach for 0/1 knapsack problem
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
				int id = 0;
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
				int idI = 0;            
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
 * Display Knapsack output
 */
 void displayKnapSackOutput(int maxWeight, int maxProfit, int maxNoOfItem, int maxItemKnapHold[])
 {


	if(maxProfit > 0)
	{
		fprintf(stdout, "a.\n");
		fprintf(stdout, "\t Maximum Profit : %d\n", maxProfit);
		fprintf(stdout, "\t Maximum Weight : %d\n", maxWeight);

		fprintf(stdout, "b.\n");  
		fprintf(stdout, "\t");
		for(int displayCounter = 0; displayCounter <= maxNoOfItem; displayCounter++)
		{
			if(maxItemKnapHold[displayCounter] != (-1))
			{
				if(displayCounter != 0)
				{
					fprintf(stdout, "\t");
				}
				fprintf(stdout, " Item Id : %d, Item Weight : %d, Item Profit : %d\n", itemDetails[maxItemKnapHold[displayCounter]].itemId, 
													itemDetails[maxItemKnapHold[displayCounter]].itemWeight,
													   itemDetails[maxItemKnapHold[displayCounter]].itemProfit);
			}		
		}
		fprintf(stdout, "\n");	

	}
	else
	{
		fprintf(stdout, "Not suitable items that Knapsack holds\n");
	}
 }

/**
 * A Brute force method to implement Knapsack
 */
 void bruteForceKnapSackMethod()
 {

	int totalSubset = pow(2, totalNoOfItems);

	int totalWeightSoFar = 0;
	int totalProfitSoFar = 0;	
	
	int maxItemKnapHold[totalSubset];
	int maxNoOfItem = 0;
	int maxProfit = 0;
	int maxWeight = 0;
	

	/**
	 * Derive max profit, weight and number of items using all the subsets with sets included
	 */
	for(int subset = 0; subset < totalSubset; subset++)	
	{
		totalWeightSoFar = 0;
		totalProfitSoFar = 0;
	
		int itemTakenIndex = 0;
		int itemHoldArray[totalNoOfItems];


		for(int set = 0; set < totalNoOfItems; set++)
		{
			if(subset & (1 << set))
			{
				int parWtSum = totalWeightSoFar + itemDetails[set].itemWeight;
				if(parWtSum <= totalKnapCapacity)
				{
					totalProfitSoFar = totalProfitSoFar + itemDetails[set].itemProfit;
					totalWeightSoFar = totalWeightSoFar + itemDetails[set].itemWeight;
					itemHoldArray[itemTakenIndex] = set;
					itemTakenIndex++;
				}
			}
		}


		if((maxWeight <= totalKnapCapacity) && (totalProfitSoFar > maxProfit))
		{
			maxWeight = totalWeightSoFar;
			maxProfit = totalProfitSoFar;

			maxNoOfItem = itemTakenIndex - 1;

			memset(maxItemKnapHold, -1, totalSubset);

			for(int itemCounter = 0; itemCounter < itemTakenIndex; itemCounter++)
			{
				maxItemKnapHold[itemCounter] = itemHoldArray[itemCounter];
			}
		}	
	}
	
	displayKnapSackOutput(maxWeight, maxProfit, maxNoOfItem, maxItemKnapHold);	
 } 

 
/**
 * main driver program
 */
int main(int argc, char *argv[])
{
	
	readKnapsackFile(argv[1]);		
	bruteForceKnapSackMethod();

	return 0;	
}

// end of main driver program
