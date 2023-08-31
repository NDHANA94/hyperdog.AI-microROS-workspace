#include <stdio.h>
#include <string.h>



int main(){

    char* str;
    char msg[500];
    str = msg;
    
    // strcpy(msg, "hello\n");

    strcat(msg, "world\n");

    printf("%s, len %ld", str, strlen(str));


    return 0;
}