#include <stdio.h>
#include <string.h> 
#include <stdlib.h> // For free(), malloc(), atoi()

void tokenize(char* stringInput, char** arrayTokens, int* numToks); // Returns an array of tokens
void dump(char**, int);

char delimiters[] = " "; // Delimiter list for strtok(), used by tokenize() 
int tokenLimit = 100;    // Set max number of tokens/words to allot mem for per line retrieved by fgets()
int tokenSize = 30;      // Set max number of letters per word to allot mem for

int charLimit = 100;  // Used by fgets(), which reads an entire line and retrieves 'charLimit' number of characters up to or until EOF or '\n' is found
char* linebuffer;    // Location where fgets() stores the string it retrieves



int main(int argc, char* argv[])
{
    linebuffer = (char*) malloc(charLimit*sizeof(char));
    
    printf("Opening file: %s\n", argv[1]);
    FILE* fp = fopen(argv[1], "r"); // Open file specified by argv[1] for reading
    
    //Read and process text file, by line, until EOF reached
    while(fgets(linebuffer, charLimit, fp) != NULL)
    {
        int numTokens = 0; // Counts the number of tokens/words in the line
        char** tokenList = (char**) malloc(tokenLimit*sizeof(char*)); // malloc() for each pointers to different tokens (words per line)
        printf("Tokenizing:%s",linebuffer); 
        
        //Tokenize the line: Put tokens into tokenList
        tokenize(linebuffer, tokenList, &numTokens); 
        printf("Finished tokenizing. Found %d tokens.\n",numTokens);
        dump(tokenList, numTokens); // Print token list. 
        
        /*int j;
        for(j=0; j<numTokens;j++)
            free(tokenList[j]); */  //C Doesn't like me to free memory this way
        free(tokenList); //Evidently this is sufficient
    }    

    fclose(fp);  // Close the file
    free(linebuffer); // Free the space for other programs

    return 0; 
}

void tokenize(char* strInput, char** tokens, int* numToks)
{

    int i = 0; 
    char* tok; // Buffer for tokens
    *numToks = 0; // Iterator & Reset counter for the number of tokens(words) found
    for(i=0; i<tokenSize; i++){ tokens[i] = (char*) malloc(tokenSize*sizeof(char));} // For each Pointer to strings, malloc() for each word

    tok = strtok(strInput, delimiters); // Get the first token
    tokens[(*numToks)++] = tok;            // Store first token
    while((tok=strtok(NULL, delimiters)) != NULL)
    {
        tokens[(*numToks)] = tok; 
        (*numToks)++; 
    }
    //printf("Done tokenizing. Found %d tokens.\n", *numToks);

} 

void dump(char** str, int nToks)
{
    int i; 
    for(i=0;i<nToks; i++)
        printf("Token %d:%s\n", i+1, str[i]);
}