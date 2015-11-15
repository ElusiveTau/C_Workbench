/* Given a string of characters, return the sum of the ascii value of each letter in the character string.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 20

int main(int argc, char** argv)
{
    char* userInput = (char *) malloc(WORD_LENGTH*sizeof(char)); 
    printf("Enter string: ...\n");
    strtok( fgets(userInput, WORD_LENGTH, stdin), "\n"); 
    
    // Meat of it  
    int i; 
    int runningSum = 0;
    for(i=0; i<strlen(userInput); i++)
    {
        printf("(%c,%d) ",*(userInput+i),*(userInput + i));
        runningSum += *(userInput + i);
    }
    printf("\nOriginal Word: %s\tASCII Sum:%d\n", userInput, runningSum); 
    
    free(userInput); 
    return 0; 
}