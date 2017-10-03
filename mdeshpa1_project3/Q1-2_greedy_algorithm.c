

/**
 * Greedy algorithm to implement 0/1 Knapsack problem 
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
 * Greedy algorithm 1
 */
 void greedyMethodOne()
 {
	fprintf(stdout, "Greedy Algorithm 1\n");
	/**
	 * sort by benefit
	 */
	for(int i = 0; i < totalNoOfItems; i++)
	{
		for(int j = i + 1; j < totalNoOfItems; j++)
		{
			if(itemDetails[i].itemProfit < itemDetails[j].itemProfit)
			{
				int tempP = itemDetails[i].itemProfit;	
				itemDetails[i].itemProfit = itemDetails[j].itemProfit;
				itemDetails[j].itemProfit = tempP;

				int tempW = itemDetails[i].itemWeight;
				itemDetails[i].itemWeight = itemDetails[j].itemWeight;
				itemDetails[j].itemWeight = tempW;
			}			
		}
	}


	int maxProfit = 0;
	int maxWeight = 0;


	fprintf(stdout, "Selected Items : \n");
	for(int i = 0; i < totalNoOfItems; i++)
	{
		if((maxWeight + itemDetails[i].itemWeight) > totalKnapCapacity)
			break;

		maxProfit = maxProfit + itemDetails[i].itemProfit;
		maxWeight = maxWeight + itemDetails[i].itemWeight;

		fprintf(stdout, "Item Id : %d Item Weight : %d Item Profit : %d\n", i, itemDetails[i].itemWeight, itemDetails[i].itemProfit);
	}
	
	fprintf(stdout, "\n");
	fprintf(stdout, "Maximum Profit : %d\n", maxProfit);
	fprintf(stdout, "Maximum Weight : %d\n", maxWeight);

	fprintf(stdout, "\n");
 }

 /**
  * Greedy algorithm 3
  */
  void greedyMethodThree()
  {
	fprintf(stdout, "Greedy Algorithm 3\n");
	/**
         * sort by weight
         */
        for(int i = 0; i < totalNoOfItems; i++)
        {
                for(int j = i + 1; j < totalNoOfItems; j++)
                {
                        if(itemDetails[i].itemWeight < itemDetails[j].itemWeight)
                        {
                                int tempP = itemDetails[i].itemProfit;  
                                itemDetails[i].itemProfit = itemDetails[j].itemProfit;
                                itemDetails[j].itemProfit = tempP;

                                int tempW = itemDetails[i].itemWeight;
                                itemDetails[i].itemWeight = itemDetails[j].itemWeight;
                                itemDetails[j].itemWeight = tempW;
                        }                       
                }
        }


	int maxProfit = 0;
        int maxWeight = 0;


        fprintf(stdout, "Selected Items : \n");
        for(int i = 0; i < totalNoOfItems; i++)
        {
                if((maxWeight + itemDetails[i].itemWeight) > totalKnapCapacity)
                        break;

                maxProfit = maxProfit + itemDetails[i].itemProfit;
                maxWeight = maxWeight + itemDetails[i].itemWeight;

		fprintf(stdout, "Item Id : %d Item Weight : %d Item Profit : %d\n", i, itemDetails[i].itemWeight, itemDetails[i].itemProfit);
        }
        
        fprintf(stdout, "\n");
        fprintf(stdout, "Maximum Profit : %d\n", maxProfit);
        fprintf(stdout, "Maximum Weight : %d\n", maxWeight);	

	fprintf(stdout, "\n");
  }

/**
  * Greedy algorithm 2
  */
  void greedyMethodTwo()
  {
        fprintf(stdout, "Greedy Algorithm 2\n");
        /**
         * sort by weight
         */
        for(int i = 0; i < totalNoOfItems; i++)
        {
                for(int j = i + 1; j < totalNoOfItems; j++)
                {
                        if(itemDetails[i].itemWeight > itemDetails[j].itemWeight)
                        {
                                int tempP = itemDetails[i].itemProfit;
                                itemDetails[i].itemProfit = itemDetails[j].itemProfit;
                                itemDetails[j].itemProfit = tempP;

                                int tempW = itemDetails[i].itemWeight;
                                itemDetails[i].itemWeight = itemDetails[j].itemWeight;
                                itemDetails[j].itemWeight = tempW;
                        }
                }
        }


        int maxProfit = 0;
        int maxWeight = 0;


        fprintf(stdout, "Selected Items : \n");
        for(int i = 0; i < totalNoOfItems; i++)
        {
                if((maxWeight + itemDetails[i].itemWeight) > totalKnapCapacity)
                        break;

                maxProfit = maxProfit + itemDetails[i].itemProfit;
                maxWeight = maxWeight + itemDetails[i].itemWeight;

		fprintf(stdout, "Item Id : %d Item Weight : %d Item Profit : %d \n", i, itemDetails[i].itemWeight, itemDetails[i].itemProfit);
        }

        fprintf(stdout, "\n");
        fprintf(stdout, "Maximum Profit : %d\n", maxProfit);
        fprintf(stdout, "Maximum Weight : %d\n", maxWeight);

        fprintf(stdout, "\n");
  }

 /**
  * Greedy algorithm 4
  */
  void greedyMethodFour()
  {	
	fprintf(stdout, "Greedy Algorithm 4\n");
	
	int maxBen[MAXITEM];

	for(int i = 0; i < totalNoOfItems; i++)
	{
		maxBen[i] =  itemDetails[i].itemProfit / itemDetails[i].itemWeight;   
	}

	/**
	 * Sort by max benefit per unit
	 */
	for(int i = 0; i < totalNoOfItems; i++)
        {
                for(int j = i + 1; j < totalNoOfItems; j++)
                {
                        if(maxBen[i] < maxBen[j])
                        {
				int tempB = maxBen[i];
				maxBen[i] = maxBen[j];
				maxBen[j] = tempB;
			

                                int tempP = itemDetails[i].itemProfit;
                                itemDetails[i].itemProfit = itemDetails[j].itemProfit;
                                itemDetails[j].itemProfit = tempP;

                                int tempW = itemDetails[i].itemWeight;
                                itemDetails[i].itemWeight = itemDetails[j].itemWeight;
                                itemDetails[j].itemWeight = tempW;
                        }
                }
        }


	int maxProfit = 0;
        int maxWeight = 0;


        fprintf(stdout, "Selected Items : \n");
        for(int i = 0; i < totalNoOfItems; i++)
        {
                if((maxWeight + itemDetails[i].itemWeight) > totalKnapCapacity)
                        break;

                maxProfit = maxProfit + itemDetails[i].itemProfit;
                maxWeight = maxWeight + itemDetails[i].itemWeight;

		fprintf(stdout, "Item Id : %d Item Weight : %d Item Profit : %d \n", i, itemDetails[i].itemWeight, itemDetails[i].itemProfit);
        }

        fprintf(stdout, "\n");
        fprintf(stdout, "Maximum Profit : %d\n", maxProfit);
        fprintf(stdout, "Maximum Weight : %d\n", maxWeight);

        fprintf(stdout, "\n");
  }



/**
 * main driver program
 */
int main(int argc, char *argv[])
{

        readKnapsackFile(argv[1]);
        greedyMethodOne();
	greedyMethodTwo();
	greedyMethodThree();
	greedyMethodFour();

        return 0;
}

// end of main driver program




