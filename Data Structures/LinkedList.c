#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{false, true} bool; 

typedef struct
{
    struct Link* nLink;  
    struct Link* pLink; 
    char* word; 
} Link; 

int numLinks = 0; // Number of Links/words counter in text file 

int lineLength = 500; // Specifies how many characters fgets() will allocate memory for
char* lineBuffer;     // Location where fgets() stores the line it retrieves

int numWords = 100; // Specifies how many pointers to words/char* to allocate memory for
int numLets = 100;  // Specifies how many chars to allocate memory for per word


int countWords(FILE* txtfilePointer, int* counterVariable); 
void makeLinkedList(FILE* txtfilePointer, Link* LinkedListOfWordsToPopulate, int numLinks);  
void toTokens(char* inputString, char** tokenListToPopulate, int* numTokens); // Tokenizes a string of text and returns an array of words and the number of words tokenized

int main(int argc, char** argv)
{
    Link* wordLinkedList; 
    FILE* fp = fopen(argv[1], "r");         // Open file for reading
        numLinks = countWords(fp, &numLinks);          // Go through text file and return the number of words/tokens found to allocate mem for
        printf("Done counting number of words. Found:%d\n",numLinks);
        makeLinkedList(fp, wordLinkedList, numLinks); // Make a linked list out of the words in the opened text files
    fclose(fp); 

    //Sort the LinkedList, alphabetically, by using insertion sort algorithm
    
    return 1; 
}

int countWords(FILE* fp, int* counter)
{
    char* tok; // Buffer for strtok()
    char delim[] = " "; 
    
    lineBuffer = (char*) malloc(lineLength*sizeof(char));       // malloc() for new line of text
    while( fgets(lineBuffer,lineLength,fp) != NULL )  // Get new line of text; must terminate with NULL; by default fgets() stops when it retrieves \n so lineBuffer retrieves \n
    {
        int tokenOnLine = 0; // Report the number of tokens found on the line
        strtok(lineBuffer, "\n"); // Prune the \n that fget() retrieved
        printf("%s",lineBuffer);
        
        
        if( ((tok = strtok(lineBuffer,delim)) != NULL) && (tok != "\n") && (tok != "\0")) {printf("Triggered");(*counter)++; tokenOnLine++;} // Count the first token
        while( tok != NULL ) // Go through each token, count iff not \n
        {
            tok = strtok(NULL,delim); // Get next token
            if( (tok != NULL) && (tok != "\n")) (*counter)++; // Increment counter if token is not null
            if( (tok != NULL) && (tok != "\n")) tokenOnLine++; 
        }
        printf("\t>>NUMBER TOKENS:%d<<\n",tokenOnLine);
            
    }
    
    free(lineBuffer); // Clear the line buffer for the next line 
    return *counter; 
}

void makeLinkedList(FILE* fp, Link* wl, int nL) 
{
    lineBuffer = (char*) malloc(lineLength*sizeof(char));   // Malloc() to get space to store each line of text; will throw segfault if not used
    while( fgets(lineBuffer,lineLength,fp) != NULL )        // Get new line of text
    {
        printf("%s",lineBuffer); 
        
    }
    
    free(lineBuffer); // Clear the line buffer for the next line 
}

