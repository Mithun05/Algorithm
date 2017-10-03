
/**
  The source file contains the code for Phone Directory.
  It implementes the functionalities such as creating,
  sorting, searching, inserting and deleting contact details
  from the phone directory.	 
 */

//standard header files
#define _GNU_SOURCE

#include <stdio.h>			// standard IO 	 - input/output ops	- header file
#include <stdlib.h>			// standard LIB  - systems library ops	- header file 
#include <string.h>			// standard STR  - string manipulation 	- header file
#include <limits.h>			// standard LIMIT- data type size info	- header file
#include <time.h> 			// standard time - time related 	- header file
#include <ctype.h>			// standard char - char conversion 	- header file

// preprocessor constants used throughout the program
#define MALLOC_ERROR "\nMalloc failed."		// malloc error
#define FILE_IO_ERROR "\nFile IO failed."	// io error
#define SIZE  500				// char array size	
#define DIRECTORY_SIZE 30000			// initial phone directory size


/**
  The following struct contains 
  Person's First Name
  Person's Last Name
  Person's Contact Number
*/
typedef struct personDetails {

	char person_first_name[SIZE];		// first name 
	char person_last_name[SIZE];		// last name
	char person_contact_phone[SIZE];	// phone number

} PhoneDirectory;

/**
  The follwing represents initial Phone Directory holding size information structure.
*/
PhoneDirectory phoneDirectory[DIRECTORY_SIZE];		// phone directory array


/** The follwing functions provides the main functionalities present in the project */


/**
  The function is used to create Phone directory from file
*/
void create(char *file_name);

/**
  The function is used to search contact name in phone directory
*/
void search(char *search_contact_name);

/**
  The function is used to sort primarily based on first name, then last name and then phone number otherwise.
*/
void sort_contact();

/**
  The function is used to insert new contact information into the phone directory.
*/
void insert(char *name, char *phone_number);

/**
  The function is used to delete contact information from the phone directory
*/
void delete(char *search_contact_to_delete);


/** The following functions are auxiliary functions which supports the main functions */

/**
  Trim the leading and trailing whitespaces within the string 
*/
char* trim(char *input_string);

/**
  Displays the phone directory information
*/
void display_phone_directory();

/**
  Counts the number of records present in the file
*/
int  count_record(char *file_name);

/**
  Swaps the two contact information based on search
*/
void swap_contact_details(PhoneDirectory *phone_directory_one, PhoneDirectory *phone_directory_two);

/**
  Quick sort to sort the directory based on contact's first, last name and phone number
*/
void quick_sort_phone_directory(PhoneDirectory *phone_directory, int left, int right);

/**
  Partial function is used in quick sort.
*/
int  divide(PhoneDirectory *phone_directory, int left, int right);


/**
  This is the current directory count which means at a real time how much data the directory contains
*/
int directory_count = 0;


/**
  Dynamic user input variables
*/
unsigned int length_max = 128;			// initial buffer for input
unsigned int current_size = 0;			// current size 


// main entry point
int main(int argc, char *argv[])
{
	create(argv[1]);			// create call
	int choice;				// user choice
	
	/**
  	  Main menu display call 
	*/
	do
	{
		printf("\n");
		printf("\n1) sort_contact");
		printf("\n2) search");
		printf("\n3) delete");
		printf("\n4) insert");
		printf("\nEnter the Choice\n");	// user input choice
		scanf("%d", &choice);		
		while(getchar() != '\n');

		switch(choice)
		{

			case 1: /* sort  */ 
				sort_contact();			
				break;
			case 2: ;
  				/* search */
				
				/**
				  Dynamic user input 
				*/
				fprintf(stdout,"\n%s", "Enter the Name -> ");
                                char *input_name = malloc(length_max);
                                current_size = length_max;
                                if(input_name != NULL)
                                {
                                        int ch = EOF;
                                        unsigned int count =0;
                                        while ((ch = getchar()) != '\n' && ch != EOF)
                                        {
                                                input_name[count++] = (char) ch;
                                                if(count == current_size)
                                                {
                                                        current_size = count + length_max;
                                                        input_name = realloc(input_name, current_size);
                                                }
                                        }
                                        input_name[count] = '\0';
                                }

                                search(input_name);	// search call
                                free(input_name);
                                input_name = NULL;
                                break;

			case 3: ;
				/* delete */
				
				/**
				  Dynamic user input
				*/
                                fprintf(stdout, "\n%s", "Enter the Name -> ");
                                char *input_name_to_delete = malloc(length_max);
                                current_size = length_max;
                                if(input_name_to_delete != NULL)
                                {
                                        int ch = EOF;
                                        unsigned int count =0;
                                        while ((ch = getchar()) != '\n' && ch != EOF)
                                        {
                                                input_name_to_delete[count++] = (char) ch;
                                                if(count == current_size)
                                                {
                                                        current_size = count + length_max;
                                                        input_name_to_delete = realloc(input_name_to_delete, current_size);
                                                }
                                        }
                                        input_name_to_delete[count] = '\0';
                                }

                                delete(input_name_to_delete);	// delete call
                                free(input_name_to_delete);
                                input_name_to_delete = NULL;
                                break;
		
		 case 4: ;
				/* insert */
				
				/**
				   Dynamic user input
				*/

                                char *input_name_to_insert = NULL;
                                char *person_name = NULL;
                                char *person_phone = NULL;

                                fprintf(stdout, "\n%s", "Enter the Name -> ");
                                input_name_to_insert = malloc(length_max);
                                current_size = length_max;
                                if(input_name_to_insert != NULL)
                                {
                                        int ch = EOF;
                                        unsigned int count =0;
                                        while ((ch = getchar()) != '\n' && ch != EOF)
                                        {
                                                input_name_to_insert[count++] = (char) ch;
                                                if(count == current_size)
                                                {
                                                        current_size = count + length_max;
                                                        input_name_to_insert = realloc(input_name_to_insert, current_size);
                                                }
                                        }
                                        input_name_to_insert[count] = '\0';
                                }

				/**
				  Divide the input into name and phone to insert 
  				*/
                                char *tokenize_input = NULL;
                                tokenize_input = strtok(input_name_to_insert, ",");
                                person_name = malloc(strlen(trim(tokenize_input)) + 1);
                                strcpy(person_name, tokenize_input);

                                tokenize_input = strtok(NULL, "\n");
                                person_phone = malloc(strlen(trim(tokenize_input)) + 1);
                                strcpy(person_phone, tokenize_input);

                                insert(person_name, person_phone);		// insert call

                                free(person_name);
                                free(person_phone);
				free(input_name_to_insert);
                                person_name = NULL;
                                person_phone = NULL;
				input_name_to_insert = NULL;
                                break;
		}

	} while(choice != 5); 

	return 0;
}
// end of main


/**
  insert new record into the directory
*/
void insert(char *input_name, char *input_phone)
{

  	  directory_count = directory_count + 1;	// new directory size
	  int new_record_counter = directory_count - 1; // new position to insert
	  /**
	    Divide input into name and phone	
	  */
 	  char *tokenize_input = NULL;	

  	  tokenize_input = strtok(input_name, " ");	
  	  strcpy(phoneDirectory[new_record_counter].person_first_name, tokenize_input);         // copy first name

  	  tokenize_input = strtok(NULL, "\n");
  	  strcpy(phoneDirectory[new_record_counter].person_last_name, trim(tokenize_input));	// copy last name

  	  strcpy(phoneDirectory[new_record_counter].person_contact_phone, input_phone);	        // copy contact phone			

	  /**
	    Sort phone directory based on new insertion to keep phone directory sorted	 
	   */ 
	  sort_contact();
}

/**
  Swap the contact information as per requirement
*/
void swap_contact_details(PhoneDirectory  *contact_details_par_one, PhoneDirectory *contact_details_par_two)
{
  		const PhoneDirectory tmp_contact_storage = *contact_details_par_one;
 		*contact_details_par_one = *contact_details_par_two;
 		*contact_details_par_two = tmp_contact_storage;
}

/**
  Randomized Quick sort 
*/
void quick_sort_phone_directory(PhoneDirectory *phoneDirectory, int start, int end)
{
 	int pivot;			// pivot element
 	if(start < end) 
 	{
 		pivot = divide(phoneDirectory, start, end);			// divide array based on pivot element
 		quick_sort_phone_directory(phoneDirectory, start, pivot - 1);	// sort lower half array
 		quick_sort_phone_directory(phoneDirectory, pivot + 1, end);     // sort higher half array
 	}
}

/**
  Pivot based partition of a directory
*/
int divide(PhoneDirectory *phoneDirectory, int start, int end) 	
{

 	 int pivotIndex = start + rand()%(end - start + 1); 		// random selection
	 int start_initial = start - 1;
	 int counter;

	 swap_contact_details(&phoneDirectory[pivotIndex],&phoneDirectory[end]);

	 pivotIndex = end;

	 for(counter = start; counter <= end - 1; counter++)
 	 {

		 int ret = strcmp(phoneDirectory[counter].person_first_name, phoneDirectory[pivotIndex].person_first_name);
 		 if (ret < 0)
 		 {
			 start_initial++;
 			 swap_contact_details(&phoneDirectory[start_initial], &phoneDirectory[counter]);
 		 }
 		 else if(ret == 0)
 		 {
 			int ret_one = strcmp(phoneDirectory[counter].person_last_name, phoneDirectory[pivotIndex].person_last_name);
 			if(ret_one < 0)
 			{
 				start_initial++;
 				swap_contact_details(&phoneDirectory[start_initial], &phoneDirectory[counter]);		
 			}
 			else if(ret_one == 0)
 			{
 				int ret_two = strcmp(phoneDirectory[counter].person_contact_phone, phoneDirectory[pivotIndex].person_contact_phone);
 				if(ret_two < 0)
 				{
 					start_initial++;
					 swap_contact_details(&phoneDirectory[start_initial], &phoneDirectory[counter]);
 				}
				 else if(ret_two == 0)
 				{
 				}			
 			}
 		}
	 }
 		swap_contact_details(&phoneDirectory[start_initial + 1], &phoneDirectory[pivotIndex]);
 		return start_initial + 1;
 }


/**
  Sort phone data
*/
 void sort_contact()
{
	/**
          Empty Directory Check 
	*/
	if(directory_count == 0)
        {
            fprintf(stdout, "\n%s", "Empty Phone Directory");
            exit(1);
        }

 	srand(time(NULL));	// initialization of randomization
	quick_sort_phone_directory(phoneDirectory, 0, directory_count - 1); // quick sort call
	/**
          Display phone directory information
	*/
	display_phone_directory();	
 } 


/**
  Create telephone directory from text file data  
 */
void create(char *input_file)
{
	int total_number_of_record = count_record(input_file);  // count total number of record

	if(total_number_of_record > DIRECTORY_SIZE)
	{
		#undef DIRECTORY_SIZE		
		#define DIRECTORY_SIZE (total_number_of_record*2)
	}

	FILE *fp;
	char *line = NULL;
	size_t length = 0;
	ssize_t line_count;
	char *tokenize_line = NULL;
	int record_counter = 0;		

	fp = fopen(input_file, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "%s", FILE_IO_ERROR);
		exit(1);
	}

	/** read file information */
	while ((line_count = getline(&line, &length, fp)) != -1) 
	{
		tokenize_line = strtok(line, " ");
		strcpy(phoneDirectory[record_counter].person_first_name, trim(tokenize_line));

		tokenize_line = strtok(NULL, ",");
		strcpy(phoneDirectory[record_counter].person_last_name, trim(tokenize_line));

		tokenize_line = strtok(NULL, "\n");
		strcpy(phoneDirectory[record_counter].person_contact_phone, trim(tokenize_line));

		record_counter++;
	}

	fclose(fp);

	directory_count = record_counter; // maintain directory count

	if (line)
	{
		free(line);
		line = NULL;
	}
}

/**
  Trim leading and trailing whitespaces
*/
char *trim(char *input_string)
{
	size_t length = 0;
	char *front_p = input_string;
	char *end_p = NULL;

	if(input_string == NULL) 
	{ 
		return NULL; 
	}

	if(input_string[0] == '\0') 
	{	 
		return input_string; 
	}

	length = strlen(input_string);
	end_p = input_string + length;

	/** leading whitespaces */
	while(isspace((unsigned char) *front_p)) 
	{ 
		++front_p; 
	}

	if(end_p != front_p)
	{
		while(isspace((unsigned char)*(--end_p)) && end_p != front_p) 
		{
		}
	}

	/** trailing whitespaces */
	if(input_string + length - 1 != end_p)
	{
		*(end_p + 1) = '\0';
	}
	else if(front_p != input_string &&  end_p == front_p)
	{
		*input_string = '\0';
	}

	end_p = input_string;
	if(front_p != input_string)
	{
		while(*front_p) 
		{ 
			*end_p++ = *front_p++; 
		}
		*end_p = '\0';
	}

	return input_string;	
}

/**
   Search contact data
   Binary Search Implementation
*/
void search(char *input_contact_details)
{

	if(directory_count == 0)
        {
            fprintf(stdout, "\n%s", "Empty Phone Directory");
            exit(0);
        }
	
  	int first = 0, middle = 0;
  	int last = directory_count - 1;


  	char *person_first_name_one = NULL;
  	char *person_last_name_one = NULL;
	char *tokenize_input_one = NULL;

	/** Divide data to search */
  	char *input_one = trim(input_contact_details);	// trim input data
  	tokenize_input_one = strtok(input_one, " ");
  	person_first_name_one = malloc(strlen(tokenize_input_one) + 1);
  	strcpy(person_first_name_one, tokenize_input_one);

  	tokenize_input_one = strtok(NULL, "\n");
  	person_last_name_one = malloc(strlen(trim(tokenize_input_one)) + 1);
  	strcpy(person_last_name_one, tokenize_input_one);


	/**
	  Binary search algorithm
	*/
  	while (first <= last) 
  	{
  		middle = (first + last)/2;

  		 if (strcmp(person_first_name_one, phoneDirectory[middle].person_first_name) == 0)
  		 {
			if(strcmp(person_last_name_one, phoneDirectory[middle].person_last_name) == 0)
			{
  			fprintf(stdout, "\n%s %s, %s", 
						phoneDirectory[middle].person_first_name, 
						phoneDirectory[middle].person_last_name, 
						phoneDirectory[middle].person_contact_phone);
  			break;
			}
			else if(strcmp(person_last_name_one, phoneDirectory[middle].person_last_name) > 0)
			{
			 	first = middle + 1;
			}
			else if(strcmp(person_last_name_one, phoneDirectory[middle].person_last_name) < 0)
			{
				last = middle - 1;			
			}
  		}
  		else if (strcmp(person_first_name_one, phoneDirectory[middle].person_first_name) > 0) 
  		{
  			first = middle + 1;
  		}
  		else if(strcmp(person_first_name_one, phoneDirectory[middle].person_first_name) < 0)
  		{
  			last = middle -1;
  		}

  	}

  	if(first > last)
  	{
  		fprintf(stdout, "\n%s", "Name not Found");
  	}

  		free(person_first_name_one);
  		free(person_last_name_one);

  		person_first_name_one = NULL;
  		person_last_name_one = NULL;
}	


/**
  Count total number of records in the file
*/
int count_record(char *input_file)
{

	FILE *fp = fopen(input_file, "r");
	int count_chars_in_line = 0;
	int total_lines_counter = 0;

	if (fp == NULL) 
	{
		return 0;
	}

	while (!feof(fp))
	{
		count_chars_in_line = fgetc(fp);
		if(count_chars_in_line == '\n')
		{
			total_lines_counter++;
		}
	}

	fclose(fp);
	return total_lines_counter;	
}

/**
  Delete data from directory
*/
void delete(char *input_details)
{
 
  		char *person_first_name = NULL;
   		char *person_last_name = NULL;
   		char *person_phone = NULL;
   		char *tokenize_input = NULL;
   		int  isFound = 0;	
   		int  foundPosition = 0;
   		int  checkComma = 0;

		/**
  		  Empty directory condition
		*/
   		if(directory_count == 0)
   		{	
   			fprintf(stdout, "\n%s", "Empty Phone Directory");
   			exit(0);
   		}

   		if(strchr(input_details, ','))
   		{
   			checkComma = 1;
   			tokenize_input = strtok(input_details, " ");
   			person_first_name = malloc(strlen(trim(tokenize_input)) + 1);
   			strcpy(person_first_name, tokenize_input);

   			tokenize_input = strtok(NULL, ",");
   			person_last_name = malloc(strlen(trim(tokenize_input)) + 1);
   			strcpy(person_last_name, tokenize_input);

   			tokenize_input = strtok(NULL, "\n");
   			person_phone = malloc(strlen(trim(tokenize_input)) + 1);
   			strcpy(person_phone, tokenize_input);

   		}
   		else
   		{
   			tokenize_input = strtok(input_details, " ");
   			person_first_name = malloc(strlen(trim(tokenize_input)) + 1);
   			strcpy(person_first_name, tokenize_input);

   			tokenize_input = strtok(NULL, "\n");
   			person_last_name = malloc(strlen(trim(tokenize_input)) + 1);
   			strcpy(person_last_name, tokenize_input);
   		}


		/** Linear search algorithm */
		int counter;
		for(counter = 0; counter < directory_count; counter++)
		{
			if(checkComma == 1)
			{
				if(strcmp(person_first_name, phoneDirectory[counter].person_first_name) == 0 && strcmp(person_last_name, phoneDirectory[counter].person_last_name) == 0 && strcmp(person_phone, phoneDirectory[counter].person_contact_phone) == 0)
				{
					isFound = 1;	
					foundPosition = counter;
					break;		
				}
			}
			else
			{
				if(strcmp(person_first_name, phoneDirectory[counter].person_first_name) == 0 && strcmp(person_last_name, phoneDirectory[counter].person_last_name) == 0)
				{
					isFound = 1;
					foundPosition = counter;
					break;	 
				}
			}
		}	

		if(isFound)
		{
			int count;
			int shift_data = 0;			

			for(count = 0; count < directory_count; ++count)
			{
				if(count == foundPosition || shift_data == 1)
				{
					strcpy(phoneDirectory[count].person_first_name, phoneDirectory[count + 1].person_first_name);
                                        strcpy(phoneDirectory[count].person_last_name, phoneDirectory[count + 1].person_last_name);
                                        strcpy(phoneDirectory[count].person_contact_phone, phoneDirectory[count + 1].person_contact_phone);
					shift_data = 1;
				}
				
			}

			directory_count = directory_count - 1;
			display_phone_directory();
		}	

		if(isFound == 0)
		{
			fprintf(stderr,"\n%s", "Name not Found");
		}

		free(person_first_name);
		person_first_name = NULL;
		free(person_last_name);
		person_last_name = NULL;				
		if(checkComma == 1)
		{		
			free(person_phone);		 
			person_phone = NULL;
		}
}


/**
  Display the phone directory data
*/
void display_phone_directory()
{
	int display_counter;
	for(display_counter = 0; display_counter < directory_count; ++display_counter)
	{
		fprintf(stdout, "\n%s %s, %s", phoneDirectory[display_counter].person_first_name, phoneDirectory[display_counter].person_last_name, phoneDirectory[display_counter].person_contact_phone);
	}
}
