//Project2 by Miclain Keffeler
//This program takes command line arguments and reads a file
// then conforms the text to your preferences in both characters per line and
// justification on the line.
//argv[1]=file argv[2]=max character length of line argv[3]="right","center",or "left" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "scanner.h"
//Declare my three alignments
void left(FILE *fp, int maxlength);
void right(FILE *fp, int maxlength);
void center(FILE *fp, int maxlength);

int main(int argc, char **argv){
    //Make sure we have everything we need 
    if (argc<4){
        fprintf(stderr, "You need at least 3 command line arguments\n");
        exit(1);
    }
    //Define what each command line arg. is = to.
    char *alignment1 = argv[3];
    FILE *fp = fopen(argv[1],"r");
    int maxlength = atoi(argv[2]);
    printf("Welcome to the formatter by Miclain.\n\n");
    
    //Tells which function to run based on justification
    if(strcmp(alignment1,"left")==0){
        printf("I will be running the %s file with %s justification.\n\n",argv[1],alignment1);
        printf("The following is your text: \n");
        left(fp,maxlength);
    }
    else if (strcmp(alignment1,"right")==0){
        printf("I will be running the %s file with %s justification.\n\n",argv[1],alignment1);
        printf("The following is your text: \n");
        right(fp,maxlength);
    }
    else if (strcmp(alignment1,"center")==0){
        printf("I will be running the %s file with %s justification.\n\n",argv[1],alignment1);
        printf("The following is your text: \n");
        center(fp,maxlength);
    }
    else 
    printf("There was an invalid input, please try again\n");
    return 0;
}

void right(FILE *fp,int maxlength){
    //If invalid line length, terminate the program
    if(maxlength<=0 || maxlength <0)
        printf("Invalid input, please try again\n");
    //Set size of line, start reading
    char *line= malloc(sizeof(char) * (maxlength+1));
    int linelength = strlen(line);
    char *neww = readToken(fp);
    while(!feof(fp)&& maxlength !=0){
        if (linelength + strlen(neww) < maxlength)
        { 
            //Adds the word to the line, and a space
            strcat(line,neww);
            strcat(line," ");
            //sets new linelength to confirm we don't go over maxlength
            linelength = strlen(line);

        }
        else if (linelength +strlen(neww) == maxlength)
        {
            //Adds new word, and prints it
            strcat(line,neww);
            printf("%s\n",line);
            //Reset line and linelength for next word to start over with
            line[0] = '\0';
            linelength = 0;
        }
        else if (linelength + strlen(neww) > maxlength)
        {
            //Adds spaces before because it is right justified. 
            //Fills remaining space less than maxlength with spaces
            int x;
            for(x=0;x<=(maxlength-linelength);x++){
                printf(" ");
            }
            //Prints line and resets
            printf("%s\n",line);

            line[0] = '\0';
            linelength = 0;
            //Adds remaining word and a space, then starts over
            strcat(line,neww);
            strcat(line," ");
            linelength = strlen(line);
        }
        //Reads new token and then starts again.
        neww = readToken(fp);
    }
    //Have to add spaces before last word, print it.
    int r = strlen(line);
    for(r=0;r<=(maxlength-linelength);r++){
        printf(" ");
    }
    printf("%s\n",line);

    return;
}
void left(FILE *fp,int maxlength){
    //Logic is essentially the same, with removal of for loop that adds spaces
    //Left justified requires no spaces to be added.
    if(maxlength<=0)
        printf("Invalid input, please try again\n");
    char *line= malloc(sizeof(char) * (maxlength+1));
    int linelength = strlen(line);
    char *neww = readToken(fp);
    while(!feof(fp)&& maxlength !=0){
        if (linelength + strlen(neww) < maxlength)
        { strcat(line,neww);
            strcat(line," ");
            linelength = strlen(line);

        }
        else if (linelength +strlen(neww) == maxlength)
        {
            strcat(line,neww);
            printf("%s\n",line);
            line[0] = '\0';
            linelength = 0;
        }
        else if (linelength + strlen(neww) > maxlength)
        {
            printf("%s\n",line);

            line[0] = '\0';
            linelength = 0;
            strcat(line,neww);
            strcat(line," ");
            linelength = strlen(line);
        }
        neww = readToken(fp);
    }
    printf("%s\n",line);

    return;

}
void center(FILE *fp, int maxlength){
    if(maxlength== -1 || maxlength == 0)
        printf("Invalid input, please try again\n");
    char *line= malloc(sizeof(char) * (maxlength+1));
    int linelength = strlen(line);
    char *neww = readToken(fp);
    while(!feof(fp)&& maxlength !=0){
        if (linelength + strlen(neww) < maxlength)
        { strcat(line,neww);
            strcat(line," ");
            linelength = strlen(line);

        }
        else if (linelength +strlen(neww) == maxlength)
        {
            strcat(line,neww);
            printf("%s\n",line);
            line[0] = '\0';
            linelength = 0;
        }
        else if (linelength + strlen(neww) > maxlength)
        {
            int x;
            //Adds a space before and after the text in line to center
            for(x=0;x<=(maxlength-linelength);x++){
                printf(" ");
                strcat(line," ");
                x++;
            }

            printf("%s\n",line);

            line[0] = '\0';
            linelength = 0;
            strcat(line,neww);
            strcat(line," ");
            linelength = strlen(line);
        }
        neww = readToken(fp);
    }
    int r = strlen(line);
    for(r=0;r<=(maxlength-linelength);r++){
        printf(" ");
        strcat(line," ");
        r++;
    }
    printf("%s\n",line);

    return;
}

