//Project1 by Miclain keffeler
//This program determines how many of a word are in a file that the user 
//chooses at the command line
//Useful for searching large documents for total occurences of a word
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

int main(int argc, char **argv){
    printf("Welcome to the word picker by Miclain\n");
    FILE *fp = fopen(argv[1],"r");

    char *pick = argv[2];
    int i;
    for(i=0;i<=strlen(pick);i++){
        if(pick[i]>=65&&pick[i]<=90)
            pick[i]=pick[i]+32;
    }
    char *read = readToken(fp);
    int x = 0;
    int j;
    while (!feof(fp)){
        for(j=0;j<=strlen(read);j++){
            if(read[j]>=65&&read[j]<=90)
                read[j]=read[j]+32;
        }
        if (strcmp(read,pick)==0)
            x +=1;
        read= readToken(fp);
    }
    printf("I found  %d cases of this word, with no regard to case\n",x);

    return 0;
}
