#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define WORD_LENGTH 100 //Max word length is actually 100-2, not counting carriage return

typedef struct word {
    int k; //Number of letters in the word
    int val; //Ascii sum value, interpreted as anagram class
    char* str; //The actual string
    int freq[26]; //Letter-frequency content (freq[0] is the number of the letter 'a' in the word)
} word; 

//File-Reading Related
int readFile(char* fName); // Reads in and creates a struct for each word, returns the number of structs created 
int countNumLines(char* fName); //Returns the number of lines in the file
void createStruct(word* loc, char* str); //Creates a struct word for the passed string, at the passed struct-pointer location; initializes k,val,str
void setFreq(word* loc, char* str); //Initializes the passed struct with the letter-frequency content of the passed string (loc's str field should be initalized; str is used to verify)

//Algorithm-Related
int isAnagram(char* s1, char* s2); //Returns 1 if they are anagrams, otherwise 0
int asciiSum(char* s); //Return the sum of the ascii value of each character of the passed argument string

//Debugging-Related
void dumpwordList(word** list, int numStructs); //Prints out each struct that was created and all of its attributes


static word** wordList; //The list of all words, initalized in readFile()

int main(int argc, char** argv) {
    
    if(argc != 1) {
        printf("Reading file ... ");
        int wordCount = 0;
        wordCount = readFile(argv[1]); //Read in the contents of the file 
        assert(wordCount != -1);
        dumpwordList(wordList, wordCount); //DEBUG: Print every struct generated
        printf("Done reading file.\n"); 
    }
    else
        printf("No text-file input provided. Call executable with text file name as first arg.\n");
        
    
    //Free wordList!
    return 0; 
}

int readFile( char* fName) {
    
    int i=0, j=0, structCount=0, lineCount=0; //for-loop iterator
    char* buf = (char*)malloc(WORD_LENGTH*sizeof(char)); //Buffer for fgets()
    
    //Count the number of lines in the file
    lineCount = countNumLines(fName); 
    printf("Found %d lines.\n", lineCount);
    
    //Allocate memory for each pointer-to-(word)struct, wordList is the iterator through multiple pointers-to-structs
    wordList = (word**)malloc(lineCount*sizeof(word*)); 
    //Allocate memory for each struct, then allocate memory for the character string in each struct
    for(i=0; i<lineCount; i++) {
        wordList[i] = (word*)malloc(sizeof(word));
        wordList[i]->k = 0; 
        wordList[i]->val = 0; 
        for(j=0;j<26;j++)
            wordList[i]->freq[j] = 0; 
        //wordList[i]->str = (char*)malloc(WORD_LENGTH*sizeof(char)); 
        //strcpy(wordList[i]->str, ""); 
        //assert(wordList[i] != NULL); 
        printf("Done Mallocing for struct#%d.\n", i);
    } //Outside of this for loop, wordList[]->str seems to be uninitialized
    printf("Done Malloc()ing and wordList Initialization\n");
    
    printf("lineCount=%d\n", lineCount); 
    for(j=0; j<lineCount; j++) {
        printf("Mallocing wordList[%d]\n",j);
        wordList[j]->str = (char*)malloc(WORD_LENGTH*sizeof(char)); 
    }
    
    if(lineCount == 0) {
        printf("\tERROR 0: Text file contains 0 words.\n");
        printf("\tFreeing allocated memory for wordList...\n"); 
        printf("\tCall to readFile() returns -1...\n");
        //free wordlist!
        return -1; 
    } //If lineCount = 0, free(wordList,buf), return -1 
    
    int k=0; 
    for(k=0; k<lineCount; k++)
        assert(wordList[k]->str != NULL);
    
    
    //Create a struct for each word 
    FILE* fp = fopen(fName, "rt"); 
    while( fgets(buf, WORD_LENGTH, fp) != NULL ) {
         printf("0 Before assert, structCount=%d\n", structCount);
        //  if(structCount == 18)
        //     wordList[structCount]->str = (char*)malloc(WORD_LENGTH*sizeof(char)); 
        //  if(structCount == 19)
        //     wordList[structCount]->str = (char*)malloc(WORD_LENGTH*sizeof(char)); 
         //assert( (wordList[structCount]->str) != NULL);
         if(buf[0] != '\n') { //Do not put empty lines (lines with just \r\n or \n) into wordList
            printf("1 This while cycle, structCount=%d\n",structCount);
            buf = strtok(buf, "\r\n"); //Warning: Returns a NULL if a line contains just \r\n 
            printf("2 Creating struct with structCount=%d\n",structCount);
            createStruct(wordList[structCount], buf); //Creates a struct, initialize k,val,str. 
            structCount++; //Update structCount 
            printf("3 while cycle end structCount=%d\n",structCount);
         }
         else if(buf[0] == '\n')
            printf("**Empty Line, skipping.**\n");
    }
    fclose(fp);
    
    printf("\treadFile(%s) completed.\n", fName);

    free(buf);
    return structCount; 
}

int countNumLines( char* fName) {
    char* buf = (char*)malloc(WORD_LENGTH*sizeof(char));
    int c = 0; 
    
    FILE* fp = fopen(fName, "rt");
    while(fgets(buf,WORD_LENGTH,fp) != NULL) {
        if(buf[0] != '\n') //Exclude empty lines (lines with just \r\n)
            c++; 
    }
    fclose(fp);
    
    free(buf); 
    return c; 
}

void createStruct( word* loc, char* w) {
    
    assert( w != NULL);
    assert( loc != NULL); 
    assert( loc->str != NULL);
    
    printf("\tCreating struct for %s.\n", w);
    //Initialize 'k'
    loc->k = strlen(w); 
    //Initialize 'val'
    loc->val = asciiSum(w); 
    //Initalize 'str'
    printf("\tw,val inited.\n");
    strcpy(loc->str, w);    //This line causes segfault on line input 18
    printf(">>string copied:%s\n>>string copied:%s<<<\n", w, loc->str);
    //Initialize freq[]
    setFreq(loc, w); 
}

void setFreq( word* loc, char* str) {
    
    int i = 0; 
    for( i=0; i<strlen(str); i++) //Initialize freq to default value 0
        loc->freq[i] = 0; 
        
    for( i=0; i<strlen(str); i++) {
        loc->freq[*(str+i)-97] += 1; 
    }
    /** *(str+i) iterates through each letter of the word
     *  *(str+i)-97 refers to an index between 0-25, inclusive, of freq; Each index corresponds to a letter between a=z and
     *  the element at each array location is a counter for the number of each corresponding letter that appears in the passed string
     *  freq[*(str+i)-97] adds 1 to the counter at that location
     **/
}

int isAnagram( char* s1, char* s2) {
  
  return 0;  
}

int asciiSum(char* string) {
    
    int i = 0, val = 0; 
    if(string == NULL) //If passed a NULL string, return 0
        return 0; 
    for(i=0; i<strlen(string); i++)
        val += *(string+i); //Sum of the first character, second, etc... via pointer arithmetic 
        
    return val;
}

void dumpwordList(word** list, int c) {
    printf("\tDEBUG: Dumping list ... \n");
    int i=0, j=0; 
    for(i=0; i<c; i++) {
        printf( "%d) %s", i+1, list[i]->str);
        printf( "\t# Letters:%d\tAsciiSum:%d\n", list[i]->k, list[i]->val);
        for(j=0;j<26;j++)
            printf("%c[%d] ",j+97,list[i]->freq[j]);
        printf("\n\n");
    }
    printf("\tDEBUG: Dump Complete.\n");
}