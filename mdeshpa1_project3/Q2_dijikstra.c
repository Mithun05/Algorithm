
/**
 *  Source code to implement Dijikstra's Algorithm
 */

 /**
  * Standard header files
  */
  #define _GNU_SOURCE   
  #include <stdio.h>
  #include <stdbool.h>
  #include <limits.h>
  #include <stdlib.h>
  #include <string.h>
  #include <errno.h>
  #include <stddef.h>	
	
 /**
  * Max number of vertices in a Graph
  */	
 #define MAX 20  

 /**
  * Typedefed int data type
  */
 typedef int MatrixBaseType;

 /**
  * Assign max integer value to the variable for the semantic meaning
  */ 
 int INFINITE = INT_MAX;

 /** 
  * Input Graph data details structure
  */

 typedef struct Matrix {
	
  	MatrixBaseType noOfVertices;
	MatrixBaseType inputGraph[MAX][MAX];
	MatrixBaseType shrtDistFrmSrc[MAX];
	MatrixBaseType shrtPathTree[MAX];
	MatrixBaseType visitedVertices[MAX];
	
 } Matrix; 


 /**
  * Matrix Data global variable
  */
  Matrix matrix;

 /**
  * Initialize short distance matrix to INFINITE and
  * path tree array to false
  */
  void initialize(int sourceNode)	
  {
	for(int i = 0; i < matrix.noOfVertices; i++)
	{
		matrix.shrtDistFrmSrc[i] = INFINITE;
		matrix.shrtPathTree[i] = -1;
		matrix.visitedVertices[i] = 0;
	}	

	/**
         * Distance of source node to itself is 0
         */            
         matrix.shrtDistFrmSrc[sourceNode] = 0;

  }

 /**
  * Upgrade distance from the selected vertex in the adjacency matrix 
  */
  void updateDistFrmPickedVertex(int processedVertex)
  {
	for(int i = 0; i < matrix.noOfVertices; i++)
		if(matrix.inputGraph[processedVertex][i] >= 0)
			if (matrix.shrtDistFrmSrc[processedVertex] + matrix.inputGraph[processedVertex][i] < matrix.shrtDistFrmSrc[i]) {
					matrix.shrtDistFrmSrc[i] = matrix.shrtDistFrmSrc[processedVertex] + matrix.inputGraph[processedVertex][i];
					matrix.shrtPathTree[i] = processedVertex;
				}	
  }


 /** 
  * Display the shortest path from source to dest
  */
  void outputShrtPath(int target)
  {
        if(matrix.shrtPathTree[target] != -1)
        {
                outputShrtPath(matrix.shrtPathTree[target]);
        }
        fprintf(stdout, "%d ", target);
  }

  /**
   * Display the shortest path produced
   */
  void outputShrtDistances()
  {
	int sourceNode = 0;
	fprintf(stdout, "Distance from source to all node is as follows : \n");
	for(int i = 0; i < matrix.noOfVertices; i++)
		fprintf(stdout, "%d --> %d \t\t %d\n", sourceNode, i, matrix.shrtDistFrmSrc[i]);	

	fprintf(stdout, "\n");
	for(int i = 0; i < matrix.noOfVertices; i++) 
	{
                fprintf(stdout, "The Path for : %d  =  ", i);
                outputShrtPath(i);
                fprintf(stdout, "\n");
        }
	fprintf(stdout, "\n");
  }

 /**
  * Find the shortest path
  */	
  void findShrtPath()
  {
		int minimumDistance;
		
		for(int i = 0; i < matrix.noOfVertices; i++)
		{
			/**
			 * Find the shortest distance which is not present in the path tree
			 */
			minimumDistance = -1;
		
			for(int i = 0; i < matrix.noOfVertices; i++)
				if(!matrix.visitedVertices[i] && ((minimumDistance == -1) || (matrix.shrtDistFrmSrc[i] < matrix.shrtDistFrmSrc[minimumDistance]))) 
						minimumDistance = i;

			/**
			 * The vertex is processed
			 */
			matrix.visitedVertices[minimumDistance] = 1;

			updateDistFrmPickedVertex(minimumDistance);		 
		}
	
		outputShrtDistances();
  }
 

 /**
  * Dijikstra's Shortest Path Algorithm Implementation
  */
 void dijikstraAlgorithm(int sourceNode)
 {
	 initialize(sourceNode);	
	 findShrtPath();	 
 }

 /**
  * Store the data into the graph file
  */
  void readInputGraphFile(char *fileName)
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
                        default: ;
                                int idD = 0;
                                char *lineD = NULL;
                                lineD = strtok(bufStore, ",");
                                while(lineD)
                                {
                                        matrix.inputGraph[lineNo][idD] = atoi(lineD);
                                        idD++;
                                        lineD = strtok(NULL, ",");
                                }
                                lineNo++;
                                break;
                }
        }

        matrix.noOfVertices = lineNo;

        fclose(filp);

        if(bufStore)
            free(bufStore);
 }


  
 /**
  * Main entry 
  */
  int main(int argc, char *argv[])
  {

	readInputGraphFile(argv[1]);	
	dijikstraAlgorithm(0);	// by default 0 is the source vertex
	
	return 0;
  } 


