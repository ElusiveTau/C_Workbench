#include <stdio.h>
#include <stdlib.h>
#include <string.>

#define MAX_STRING_SIZE 100

int main(int argc, char** argv) {
    
    char* str = malloc(MAX_STRING_SIZE*sizeof(char)); 
    
    FILE* fp = fopen(argv[1], "r");
    
    
    
    return 0; 
}
