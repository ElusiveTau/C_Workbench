/** 
 * Does malloc() have scopes?
 **/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NAME_LENGTH 100

typedef struct person{  
    char* name; 
    int age; 
} person; 

static person** group1; //Group1 is the iterator for an array of pointers-to-(person)struct

void initGroup();
void setPersonInfo(person* p, char* name);
void dump(); 

int main(int argc, char** argv) {
    
    initGroup(); 
    dump(); 
    
    return 0; 
}

void initGroup() {
    
    int numberPeople = 10; //Group size is set here, in this function
    
    //Malloc() an array of person-struct pointers, call the iterator group1
    //group1 points to the first person-struct pointer. We may iterate through (numberPeople-1) person-structs pointers
    //  i.e., group1[0] ... group[numberPeople-1] are each valid person-struct pointers
    group1 = (person**)malloc(numberPeople*sizeof(person*));
    
    //For each person-struct pointer, we need to allocate memory for a person-struct
    int i=0; 
    for(i=0; i<numberPeople; i++) {
        group1[i] = (person*)malloc(sizeof(person)); //memory allocated for a single person-struct 
        group1[i]->age = 0; //Initialize age; 
        group1[i]->name = (char*)malloc(NAME_LENGTH*sizeof(char));  //memory allocated for that struct's name-field
        strcpy(group1[i]->name, ""); //Initialize the character string to empty string
        assert(group1[i]->name != NULL); //Check that it isn't NULL
    }
    
    //Run a check that all names are initalized
    for(i=0;i<numberPeople;i++) {
        assert(group1[i]->name != NULL);
    }
    
    int counter = 0; 
    while(counter < numberPeople) { //Goes from 0 to 9
        printf("Counter=%d\n",counter);
        assert( (group1[counter]->name) != NULL);
        setPersonInfo(group1[counter], "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz"); 
        counter++; 
    }
    
}

void setPersonInfo(person* p, char* n) {
 
    assert(p != NULL);  //Check that the struct* isn't NULL
    assert(p->name != NULL); //Check that char* isn't NULL 
    
    p->age = 1; 
    strcpy(p->name, n); 
}


void dump() {
    
    int i=0; 
    for(i=0; i<10; i++)
        printf("%d)%s\n", i+1, group1[i]->name); 
}