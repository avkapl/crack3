#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"


// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	// open file for reading
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	// Allocate memory for an array of strings (arr).
	// make initial allocation of capacity strings
	int capacity = 10;
	char **arr = malloc(capacity * sizeof(char *));

	// set size to 0
	*size = 0;

	// buffer string
	char str[1000];

	// Read the file line by line.
	// uses fgets to read the line into buffer string
	while (fgets(str, 1000, in) != NULL)
    {
        // trim newline
        char *nl = strchr(str, '\n');
        if(nl) *nl = '\0';

		// check capacity
		// Expand array if necessary (realloc).
		if (*size >= capacity)
		{
			capacity += 10;
			arr = realloc(arr, capacity * sizeof(char *));
		}

		// Allocate memory for the string (str).
		arr[*size] = malloc(strlen(str) + 1);

		//   Copy each line into the string (use strcpy).
		strcpy(arr[*size], str);

		// The size should be the number of entries in the array.
		(*size)++;
            
    }

	fclose(in);

	// Return pointer to the array of strings.
	return arr;
}


// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (strstr(lines[i], target) != NULL)
		{
			return lines[i];
		}
	}

	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		free(arr[i]);
	}

	free(arr);
}
