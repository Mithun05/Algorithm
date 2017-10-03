
/**
 * The source file contains the code for Standard Multiplication 
 * and Strassens matrix multiplication algorithm.
 */

// standard header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/**
 * Holding extra dimensions if not power of 2 : variable declaration
 */
int tempS;

/**
 * Matrix struct representation
 */
typedef struct MatrixData {
	int N;					// Dimension
	float array[50][50];  		        // Matrix Elements
} MatrixData;


/**
 * The function is used to create random matrix within the specified range
 */
MatrixData createMatrix(int inputSize, MatrixData inputMatrix)
{
        int firstCounter, secondCounter;
        int maxRange = 5.0, minRange = -5.0;

	inputMatrix.N = inputSize;	// set matrix dimension	

        for(firstCounter = 0; firstCounter < inputSize; firstCounter++)
                for(secondCounter = 0; secondCounter < inputSize; secondCounter++) {
			if(firstCounter >= tempS || secondCounter >= tempS) {
				inputMatrix.array[firstCounter][secondCounter] = 0;
			} else {
				 inputMatrix.array[firstCounter][secondCounter] = (maxRange - minRange) * ((float)rand() / RAND_MAX) + minRange; // generate random values
			}
		}

	return inputMatrix;
}

/** 
 * The function is used to display the matrix data
 */
void displayMatrix(int inputSize, MatrixData inputMatrix)
{
        int firstCounter, secondCounter;
	if(tempS < inputSize)
	{
		inputSize = tempS;
	}
        for(firstCounter = 0; firstCounter < inputSize; firstCounter++) {
                for(secondCounter = 0; secondCounter < inputSize; secondCounter++) {
                                fprintf(stdout, "% .2f\t", floor((inputMatrix.array[firstCounter][secondCounter])*100)/100); 
		}
        			fprintf(stdout, "\n");
	}
	fprintf(stdout, "\n");
}

/**
 * The function is used to multiply two matrices using standard algorithm
 */
MatrixData standardMultiplication(int inputSize, MatrixData A, MatrixData B, MatrixData C)
{
	int firstCounter, secondCounter, thirdCounter;
	float finalResult = 0;
	for(firstCounter = 0; firstCounter < inputSize; firstCounter++) {	
		for(secondCounter = 0; secondCounter < inputSize; secondCounter++) {
			for(thirdCounter = 0; thirdCounter < inputSize; thirdCounter++) {
				finalResult += (A.array[firstCounter][thirdCounter] * B.array[thirdCounter][secondCounter]);
			}
			C.array[firstCounter][secondCounter] = finalResult;
			finalResult = 0;
		}
	}
	
	return C;		
}

/**
 * Divide the matrix multiplier and multiplicand data 8 parts each time from strassen method
 */
MatrixData divide(MatrixData inputOne, MatrixData inputTwo, int varOne, int varTwo)
{
	int firstCounter, secondCounter, thirdCounter, fourthCounter;
        for(firstCounter = 0, secondCounter = varOne; firstCounter < inputTwo.N; firstCounter++, secondCounter++)
             for(thirdCounter = 0, fourthCounter = varTwo; thirdCounter < inputTwo.N; thirdCounter++, fourthCounter++)
                                inputTwo.array[firstCounter][thirdCounter] = inputOne.array[secondCounter][fourthCounter];

	return inputTwo;
}

/**
 * Addition of the elements of given matrices from strassen method 
 */
MatrixData add(MatrixData inputOne, MatrixData inputTwo)
{
        int n = inputOne.N;
        MatrixData result = {0};
        result.N = n;

        for(int firstCounter = 0; firstCounter < n; firstCounter++) 
           for(int secondCounter = 0; secondCounter < n; secondCounter++) 
                 result.array[firstCounter][secondCounter] = inputOne.array[firstCounter][secondCounter] + inputTwo.array[firstCounter][secondCounter];

        return result;
}

/**
 * Substraction of the elements of given matrices from strassen method
 */
MatrixData sub(MatrixData inputOne, MatrixData inputTwo)
{
        int n = inputOne.N;
        MatrixData result = {0};
        result.N = n;
	
        for(int firstCounter = 0; firstCounter < n; firstCounter++)
            for(int secondCounter = 0; secondCounter < n; secondCounter++) 
                  result.array[firstCounter][secondCounter] = inputOne.array[firstCounter][secondCounter] - inputTwo.array[firstCounter][secondCounter];

        return result;

}

/**
 * Copy final elements of matrices into the result matrix from strassen method
 */
MatrixData copy(MatrixData inputOne, MatrixData inputTwo, int varOne, int varTwo)
{
	int firstCounter, secondCounter, thirdCounter, fourthCounter;
        for(firstCounter = 0, secondCounter = varOne; firstCounter < inputOne.N; firstCounter++, secondCounter++)
            for(thirdCounter = 0, fourthCounter = varTwo; thirdCounter < inputOne.N; thirdCounter++, fourthCounter++)
                      inputTwo.array[secondCounter][fourthCounter] = inputOne.array[firstCounter][thirdCounter];
                   
	return inputTwo;
}

/**
 * Actual strassen method computation call
 */
MatrixData strassen(MatrixData inputOne, MatrixData inputTwo)
{

	int n = inputOne.N;
	MatrixData result = {0};
	result.N = n;
	
	if((n%2 != 0) && (n != 1))
        {
                MatrixData a1 = {0};
		MatrixData b1 = {0}; 
		MatrixData c1 = {0};
                int n1 = n + 1;
                a1.N = n1;
                b1.N = n1;
                c1.N = n1;

                for(int i = 0; i < n; i++)
                     for(int j = 0; j < n; j++) {
                          a1.array[i][j] = inputOne.array[i][j];
                          b1.array[i][j] = inputTwo.array[i][j];
                     }

                c1 = strassen(a1, b1);

                for(int i = 0; i < n; i++)
                        for(int j = 0; j < n; j++)
                                result.array[i][j] = c1.array[i][j];

                return result;
        }

	if(n == 1)
	{
		result.array[0][0] = inputOne.array[0][0] * inputTwo.array[0][0];
	}
	else
	{
			MatrixData A11 = {0};
			MatrixData A12 = {0}; 
			MatrixData A21 = {0}; 
			MatrixData A22 = {0};
			MatrixData B11 = {0};
			MatrixData B12 = {0}; 
			MatrixData B21 = {0}; 
			MatrixData B22 = {0};

			A11.N = n/2;
			A12.N = n/2;
			A21.N = n/2;
			A22.N = n/2;
			B11.N = n/2;
			B12.N = n/2;
			B21.N = n/2;
			B22.N = n/2;
	

			A11 = divide(inputOne, A11, 0 , 0);
			A12 = divide(inputOne, A12, 0 , n/2);
			A21 = divide(inputOne, A21, n/2, 0);
			A22 = divide(inputOne, A22, n/2, n/2);

			B11 = divide(inputTwo, B11, 0 , 0);
			B12 = divide(inputTwo, B12, 0 , n/2);
			B21 = divide(inputTwo, B21, n/2, 0);
			B22 = divide(inputTwo, B22, n/2, n/2);		

			MatrixData P1 = strassen(add(A11, A22), add(B11, B22));
			MatrixData P2 = strassen(add(A21, A22), B11);
			MatrixData P3 = strassen(A11, sub(B12, B22));
			MatrixData P4 = strassen(A22, sub(B21, B11));
			MatrixData P5 = strassen(add(A11, A12), B22);
			MatrixData P6 = strassen(sub(A21, A11), add(B11, B12));
			MatrixData P7 = strassen(sub(A12, A22), add(B21, B22));

			MatrixData C11 = add(sub(add(P1, P4), P5), P7);
                        MatrixData C12 = add(P3, P5);
                        MatrixData C21 = add(P2, P4);
                        MatrixData C22 = add(sub(add(P1, P3), P2), P6);
		
		 	result = copy(C11, result, 0 , 0);
			result = copy(C12, result, 0 , n/2);
			result = copy(C21, result, n/2, 0);
			result = copy(C22, result, n/2, n/2);
			
	}	
	return result;	
}


/**
 * The function is used to perform matrix multiplication using Strassens's Method and acts as a wrapper
 */

void strassensMultiplication(int inputSize, MatrixData A, MatrixData B)
{
        MatrixData finalResult = {0};
        finalResult = strassen(A, B);  	        // call to recursive strassens computation method
        displayMatrix(inputSize, finalResult);	// display the strassen matrix multiplication result
}

// main function entry

int main(int argc, char *argv[])
{
	// read command line input 

	int inputSize, tempVar;
	inputSize = atoi(argv[1]);
	if(inputSize < 0 || inputSize == 0)
	{
		fprintf(stderr, "Matrix dimesion is Invalid : %d\n", inputSize);	// set error code
		exit(EXIT_FAILURE);	
	}

	tempS = inputSize;

	// for odd value make it to the power of 2
	if(inputSize & inputSize - 1 != 0) {
       	       tempVar = log(inputSize)/log(2);
               inputSize = pow(2, tempVar+1);
	}
	
	srand(1);									// initialize random generator
	MatrixData A = {0};								// input matrix
	MatrixData B = {0}; 								// input matrix
	MatrixData C = {0};								// output matrix

	A = createMatrix(inputSize, A);							// create first input matrix
	B = createMatrix(inputSize, B);							// create second input matrix
	C = createMatrix(inputSize, C);							// create output matrix

	fprintf(stdout, "Matrix A:\n");
	displayMatrix(inputSize, A); 							// display first matrix
	fprintf(stdout, "Matrix B:\n");
	displayMatrix(inputSize, B);							// display second matrix

	fprintf(stdout, "Strassen's Multiplication Output:\n");
	strassensMultiplication(inputSize, A, B);					// call to strassens wrapper function

	fprintf(stdout, "Standard Multiplication Output:\n");
	C = standardMultiplication(inputSize, A, B, C);					// call to standard multiplication function
	displayMatrix(inputSize, C);							// display output matrix

	return 0;

}

// end of the main

