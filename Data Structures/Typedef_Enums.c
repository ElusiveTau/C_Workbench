#include <stdio.h>

typedef enum{false, true} bool; //0/1 <-> true/false

bool flirt(bool* statement)
{
    printf("Bool Passed:%d\n", *statement);
    return *statement; 
}



int main(int argc, char** argv)
{
    bool MelissaIsCute = true; 

    if( flirt(&MelissaIsCute) )
        printf(":)\n");
    else
        printf(":(\n");
    
    return 0; 
}