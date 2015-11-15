/** 
 * What happens when we pass null to strtok()?
 * 
 * This is with regards to Weather Vane's concern: 
 * http://stackoverflow.com/questions/33178883/printf-prints-string-arguments-out-of-order?noredirect=1#33179478
 * 
 **/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define test 1

int stringSize = 100; 

int main(int argc, char** argv) {

    #if test == 0
    //HOW STRTOK() WORKS
    char* testStr = (char*) malloc(stringSize*sizeof(char)); 
    char* p1, *p2, *p3, *p4; 
    
    strcpy(testStr, "Hi Melis****sa =)"); //Expect: {Hi Meli}{****}{a =)}
    printf("String:%s\n", testStr);
    
    p1 = strtok(testStr, "s"); // p1 <= Hi Melis
    p2 = strtok(NULL, "s");    // p2 <= ****
    p3 = strtok(NULL, "s");    // p3 <= sa =)     Stopped because EOL reached
    p4 = strtok(NULL, "s");    // p4 <= NULL    strtok() looked for 's' but reached EOL so it returns NULL ptr
    
    printf("String (After tokenizing):%s\n", testStr);
    assert(p1 != NULL);
    printf("p1:%s\n",p1); 
    assert(p2 != NULL);
    printf("p2:%s\n",p2);
    assert(p3 != NULL);
    printf("p3:%s\n",p3); 
    assert(p4 != NULL);   
    printf("p4:%s\n",p4); 
    
    
    
    #elif test == 1
    
    /**
     *  Input is a textfile with the literal single text line:
     * 
     *  Hi\0
     * 
     *  Notice there are no \n after Hi
     *  Q1. So how does strtok behave?
     * */
    
    char* buf = (char*) malloc(stringSize*sizeof(char));
    FILE* fp = fopen(argv[1], "r"); 
    
    fgets(buf, stringSize, fp);     // buf <= Hi fgets stops reading when it encounters \0
    while(buf != NULL) {            
        printf("Found:%s\t",buf);   // Prints out "Found:Hi    "
        buf = strtok(buf,"\n");     // buf <= Hi\0 since the delimiter doesn't exist in the string, it uses the EOF or the \0 as the delimiter and returns the last token it retrieves
                                    // strtok(arr,"\n") does not mo
        buf = strtok(NULL,"\n");    // 
        printf("buf (after tok):%s\n", buf); 

    }
    
    
    #endif
    
    
    return 0; 
}