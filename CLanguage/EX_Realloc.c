#include <stdio.h>
#include <stdlib.h>

#define DEF_STRINGSIZE 10
#define REALLOC_SIZE 20

void dump(char* s){
    printf("You entered:%s",s); 
}

int main(int argc, char** argv){

    char* userInput = malloc(DEF_STRINGSIZE*sizeof(char));    
    printf("Enter string of size <10...");
    fgets(userInput,10,stdin); //Remember ... fgets() include the \n. Used to terminate the fgets() input
    dump(userInput); 
    
    
    //Realloc for userInput <20 char
    userInput = realloc(userInput, REALLOC_SIZE); 
    printf("Realloc(). Enter string size <20...");
    fgets(userInput,20,stdin); 
    dump(userInput); 
    
}

