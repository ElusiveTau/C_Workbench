#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WORD_LENGTH 100	// Max number of characters per word

struct data1{
   int numRows;         // What's the total number of words?
   int maxWordSize;     // What's the number of characters in the longest word?
   char* biggestWord;   // What's the longest word? (number of characters
}; //Container for info about dictionary text file; preprocess() initializes it
struct word{
   int size; 
   int val; 
   char* word; 
   int freq[]; 
} //Container for each word: size = number of characters, val = hashed value, word = the actual string, freq[] = frequency of each character

struct data1 preprocess(char* fileName, int debugPrint); //Returns basic info about the file; Currently: Number of words, max word size, and the largest word

int main(int argc, char* argv[]){
   
   //Run through textfile, find number of words, the biggest word, the biggest word; Will print if debugPrint == 1
   preprocess(argv[1], 1); 
   //Init
   
   
   return 0; 
}

struct data1 preprocess(char* fName, int debugPrint) {

   static struct data1 textFile = {.numRows = 0, .maxWordSize = 0}; //Initialize data1 struct
   textFile.biggestWord = (char*)malloc(WORD_LENGTH*sizeof(char));                   //Initalize data1 struct
   char* str = (char*) malloc(WORD_LENGTH*sizeof(char)); //Malloc() buffer where fgets() stores the retrieved string
   
   FILE* fp = fopen(fName, "rt"); //Open file
   while( fgets(str, WORD_LENGTH, fp) != NULL) {
      str = strtok(str, "\r\n");    //Removes the carriage return, linefeed character
      if(str == NULL) //Makes code more robust to single-line '\r\n' inputs, where strtok() returns NULL, causing seg. fault in strlen(str)
         break;
      assert(str != NULL); 
      if( strlen(str) > textFile.maxWordSize) {
         textFile.maxWordSize = strlen(str); //Update biggest word size 
         strcpy(textFile.biggestWord, str);  //Update biggest word 
      }
      textFile.numRows++; 
      assert(str != NULL); 
   }  //Go through text input linearly, update data1 struct
   fclose(fp); //Close file
   
   if(debugPrint) {
      printf("PREPROCESS RESULTS:\n");
      printf("=====================\n");
      printf("Total Words:%d\n", textFile.numRows);
      printf("Biggest Word:%s\n", textFile.biggestWord);
      printf("Biggest Word Len:%d\n", textFile.maxWordSize); 
      printf("=====================\n");
   }
   
   free(str); 
   return textFile; 
}


