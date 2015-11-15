/* Takes a string given by the user, tokenizes it, and returns each token separately*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charLimit = 100; 
char* strBuf;
char* token = NULL; 
char delimiters[] = " ";

int main(int argc, char* argv[])
{
    strBuf = (char*) malloc(charLimit*sizeof(char));    
    
    printf(">>Enter a string. Press enter when done.\n"); 
    fgets(strBuf, charLimit, stdin); 
    printf(">>You entered:%s>>Tokenizing...\n", strBuf); 
    
    // Tokenize the string
    int i = 0; 
    token = strtok(strBuf, delimiters);
    if(token != NULL)
    {
        i++;
        printf("Token %d >>%s\n",i, token); //Get the first token and print it.
    }
    
    while(token != NULL)
    {
        token = strtok(NULL, delimiters); //Get the next token
        if(token != NULL)
        {
            i++;
            printf("Token %d >>%s\n",i,token);  //Print token
        }
    }
    
    
    free(strBuf); 
    
    return 0; 
}