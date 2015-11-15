#include <stdio.h>
#include <stdlib.h> //For atoi()
#include <string.h>

#define USE_METHOD 3

// METHOD 1
#define numStrings 5
#define maxStringLength 10 

//int size;         // Causes 'error: variably modified 'strL' at file scope. See note [0] 
//char* strL[size]; // ^ 

int main(int argc, char* argv[])
{
   // METHOD 1 - 2D Array of Characters
   /*
    This assumes the size and number of strings in the initializer match up with
    your array dimensions. In this case, the contents of each string literal
    (which is itself a zero-terminated array of char) are copied to the memory 
    allocated to stringList. The problem with this approach is the possibility of 
    internal fragmentation; if you have 99 strings that are 5 characters or 
    less, but 1 string that's 20 characters long, 99 strings are going to have 
    at least 15 unused characters; that's a waste of space.
    */
    
   #if USE_METHOD == 1
   char stringList[numStrings][maxStringLength]; 
   strcpy(stringList[0], "HelloWorl");  //String literals are \0 terminated
   strcpy(stringList[1], "Thisisok1");
   strcpy(stringList[2], "Thisisok2");
   strcpy(stringList[3], "Thisisok3");
   strcpy(stringList[4], "Thisisok4"); //This will be overwritten
   strcpy(stringList[4], "wasted"); //This is wasteful. 4 unused characters
   
   int i; 
   for(i=0;i<numStrings;i++)
      printf("%s\n", stringList[i]); 
   #endif
   
   #if USE_METHOD == 2
    // METHOD 2 - 1D Array of Pointers to Chars (Supposedly the same as char** since the array name resolves to a pointer to char*)
    
    
    printf("How many words shall I store?\n");

    int size = 1; 
    char* stringList2[size];
    
    #endif
    
    #if USE_METHOD == 3
    // METHOD 3 - Pointers to Pointers to Char: 1 Char* for each word
    
    char delimiters[] = " "; // Delimiters for strtok()
    int tokSize = 50;  // Number of characters per token (effectively number of letters allowed per word)
    char* tok;         // Buffer variable for each token we strtok() 
    int numTokens = 0; // Counter for the number of tokens encountered
    
    int lineSize = 100; // The number of words/tokens per line
    char** sPtr; // Points to the array that stores each token
    
    char testString[] = "Hello I'm Minh. I am learning how to tokenize strings."; 
    
    int i; 
    sPtr = (char**) malloc(lineSize*sizeof(char*)); // Allocate memory for each char* (each word) 
    for(i=0; i<lineSize;i++)                        // Allocate memory for each character of a word/token
        sPtr[i] = (char*) malloc(tokSize*sizeof(char)); 
    
    
    //Tokenize the string and store each token into array of 
    i = 0; // Index for the token list
    tok = strtok(testString, delimiters);  //Get the first token, store token into token list, update i=1
    sPtr[i] = tok; 
    i++; 
    while(tok != NULL) // Get & Store subsequent tokens
    {
        tok = strtok(NULL, delimiters); 
        sPtr[i] = tok; 
        i++; 
        numTokens++; 
    }
    printf("Done tokenizing and storing. Found %d tokens.\n", numTokens); 
    
    // Print stored tokens
    printf("Printing out token list...\n");
    int j; 
    for(j=0;j<numTokens;j++)
    {
        printf("Token %d:%s\n",j+1,sPtr[j]);  // j+1 since people like to start counting at 1. 
    }
    
    printf("Done METHOD 3\n"); 
    free(sPtr); // Free space for other programs.
    #endif 
    
    
    return 0; 
}