/* Q1. Does fgets() include newline? 
    -> fgets() returns a string with the \n character appended */

/* Q2. Suppose you only allocate enough space for a single character and newline, does the newline get dropped or does the \0 get dropped? 
       What if you only allocate enough space for 1 character? 
       
    -> If 3: <char>\n\0         If 2: <char>\0     If 1 or 0: \n   
       */
    
/* Q3. How to deallocate array of pointers to pointers to char? */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Q 2

int main(int argc, char** argv)
{
    int i = 0; // for-loop iterator
    int charLimit = 10; // Number of characters that fgets() will retrieve
    int charLimit2 = 0; // Try 0, 1, 2, 3;     If 3: <char>\n\0         If 2: <char>\0     If 1 or 0: \n
    int numWords = 100; 
    int numChars = 100; 
    char** sentence = (char**) malloc(numWords*sizeof(char*));                  // Free space for some number of pointers to chars
    for(i=0; i<numWords; i++) sentence[i] = (char*) malloc(numChars*sizeof(char));  // Free space for some number of chars for each char pointers.
    
    #if Q==1
    //Q1.
    printf("Write something.\n");
    fgets(sentence[0],charLimit,stdin);
    printf("%s",sentence[0]);  // This is with \n still appended
    //printf("%s",strtok(sentence[0],"\n")); //strtok() removes the \n
    #endif
    
    #if Q==2
    //Q2. 
    printf("Write a letter and press enter.\n"); 
    fgets(sentence[1],charLimit2,stdin);  //if charLimit2 = 2, then sentence[1] contains a letter and \0. The \n seems to be omitted
    printf("%s",sentence[1]); 
    #endif
    
    #if Q==3
    //Q3.
    int j,k;
    for(j=0;j<numWords;j++)
            free(sentence[j]);
    #endif
    
    return 0; 
}