#include <stdio.h>
#include <stdlib.h>

#define DEF_STRINGSIZE 100

struct emptyList{} emptyList; 

struct primTypeList{
    char someChar;      //1
    char* someCharPtr;  //8
    int someNum;        //4
    int* someNumPtr;    //8
} primTypeList; 

int main(int argc, char** argv){
    
    char* userInput = malloc(DEF_STRINGSIZE*sizeof(char));

    printf("sizeof char: %lu\n", sizeof(char));  
    printf("sizeof *char: %lu\n", sizeof(char*));
    printf("sizeof char[10]: %lu\n", sizeof(char[10]));
    printf("sizeof char*[10]: %lu\n", sizeof(char*[10]));
    printf("sizeof userInput (malloced char*): %lu\n", sizeof userInput); //Checked google: There is no way to check for size of malloced() memory block
    
    printf("\n"); 
    printf("sizeof int: %lu\n", sizeof(int));
    printf("sizeof int*: %lu\n", sizeof(int*));
    printf("sizeof int[10]: %lu\n", sizeof(int[10]));
    printf("sizeof int*[10]: %lu\n", sizeof(int*[10]));
    
    printf("sizeof primTypeList: %lu\n", sizeof primTypeList); 
    //http://stackoverflow.com/questions/119123/why-isnt-sizeof-for-a-struct-equal-to-the-sum-of-sizeof-of-each-member    

}