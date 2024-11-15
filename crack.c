#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size;
    char **hashes = loadFileAA(argv[1], &size);
    
    // CHALLENGE1: Sort the hashes using qsort.
    
    // TODO
    // Open the password file for reading.
    FILE *passFile = fopen(argv[2], "r");

    // prints error message if file isn't open
    if (!passFile)
    {
        printf("Can't open %s file for reading\n", argv[2]);
        exit(1);
    }

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    // CHALLENGE1: Use binary search instead of linear search.

    char password[PASS_LEN];
    int passwordsFound = 0;

    while (fgets(password, PASS_LEN, passFile))
    {
        // trim newline
        char *nl = strchr(password, '\n');
        if(nl) *nl = '\0';

        char *hash = md5(password, strlen(password));

        char *found = substringSearchAA(hash, hashes, size);
		if (found)
        {
            printf("%s %s\n", password, hash);
            passwordsFound++;
        }
		free(hash);
    }

    // TODO
    // When done with the file:
    //   Close the file
    fclose(passFile);
    //   Display the number of hashes found.
    printf("Number of hashes found: %d\n", passwordsFound);
    //   Free up memory.
    freeAA(hashes, size);
}
