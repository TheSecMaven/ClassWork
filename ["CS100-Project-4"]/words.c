#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "scanner.h"

//Declare 5 Functions 
//Prints the resultant matrix
void Print(int x);
//Solves the puzzle for left to Right
int LefttoRight(int x,int n,int t,char*read);
//Solves the puzzle for Right to Left
int RightoLeft(int x,int n,int t,char*read);
//Solves the puzzle for Up to Down
int UptoDown(int x,int n,int t,char*read);
//Solves the puzzle for Down to Up
int DowntoUp(int x,int n,int t,char*read);
//Global Matrixes to play with in each function easily
char ult[100][100];
char new[100][100];
int main(int argc, char **argv){
    //X is my puzzle length and width
    int x =atoi(argv[1]) +1;
    //Open file that contains puzzle
    FILE *fp = fopen(argv[2],"r");
    //I and J traverse the matrix
    int i = 0;
    int j = 0;
    int r = 100;
    int d= 100;
    //Assigns every spot in new to a '.'
    while (r>=0){
        new[r][d]='.';
        d--;
        if (d==0){
            d=100;
            r--;
        }}
        //Assigns all the letters in the file to ult in their respective spot
        while (j<=x){
            ult[j][i] = readRawChar(fp);
            if (i == x-1){
                i = 0;
                j++;
            }
            else{
                i++;
            }
        }
        i=0;
        j=0;
        //Converts all the letters to lowercase
        while (j<=x){
            if (ult[j][i] >=65 && ult[j][i] <=90){
                ult[j][i] = ult[j][i]+32;
                if (i == x-2){
                    j++;
                    i=0;
                }
                else{
                    i++;

                }
            }

            else{
                if (i == x-2){
                    j++;
                    i=0;
                }
                else{
                    i++;
                }
            }}
        j=0;
        i=0;
        //Prints the puzzle
        printf("The puzzle is:\n");
        while (j<=x-2){
            printf("%c",ult[j][i]);
            if (i == x-1){
                i = 0;
                j++;
            }
            else{
                i++;
            }
        }
        printf("\n");
        printf("Enter a word to find in the puzzle : ");
        printf("\n");
        //read is the word being searched for and n is the length of that word
        char *read = readToken(stdin);
        int n = strlen(read);
        int t =0;
        int total =0;
        //Calls all my functions
        //Adds the total times found to int total
        total+=   LefttoRight(x,n,t,read);
        total+= RightoLeft(x,n,t,read);
        total+= UptoDown(x,n,t,read);
        total+= DowntoUp(x,n,t,read);
        printf("\nthe word %s was found a total of %d times\n",read,total);
        //prints the resultant, solution puzzle
        printf("The end puzzle is\n");

        Print(x);

        //While the user doesn't enter 'zzz'
        while(strcmp(read,"zzz")!=0){
            printf(" Enter another word to find in the puzzle or 'zzz' to exit : ");
            printf("\n");
            scanf("%s",read);
            t=0;
            total=0;
            int n = strlen(read);
            //Checks to make sure read is not 'zzz'
            if(strcmp(read,"zzz")==0){
                printf("The program has ended\n");
            }
            //Calls the functions again with the new word
            else{
                total+=   LefttoRight(x,n,t,read);
                total+= RightoLeft(x,n,t,read);
                total+= UptoDown(x,n,t,read);
                total+= DowntoUp(x,n,t,read);
                printf("\nthe word %s was found a total of %d times\n",read,total);
                printf("The end puzzle is\n");
                Print(x);
            }

        }
        return 0;
}
int LefttoRight(int x,int n,int t,char*read){
    //I and J traverse the puzzle
    int i=0;
    int j=0;
    //Found is how many times you find the word
    int found =0;
    //F stores the position of I when it finds a matching letter
    int f= 0;
    //Q and G are used to represent the string length
    int q = n;
    int g = n;
    //A and B are the comparing letters
    char a = ult[j][i];
    char b = read[t];
    //While there are still rows to be read
    while (j<=x){
        a=ult[j][i];
        b=read[t];
        //If the letters are the same
        if (a==b){
            //Check to make sure that we don't have a repeating first letter

            if (ult[j][i+1]==b){
                g--;
                //If we do, go to the next letter and go to the next letter
                if (g+1==n){
                    t++;
                    i++;
                }
                //Otherwise, just go to the next letter in the word and check
                else{

                    t++;
                }


            }
            //Otherwise, just take one away from my stringlength and go to the next letter
            else{
                f=i;
                g--;
                t++;
            }}
        //If you have found the word (G will only equal 0 if it found the word for sure
        if (g==0 ){
            //While the stringlength is not 0
            while (q>0){
                //Assigns the letter to the global matrix new
                new[j][i] = ult[j][i];
                i--;
                q--;
            }
            //Resets everything for the next word
            q=n;
            i=f-1;
            found++;
            g=n;
            t=0;

        }
        //If you are at the end of the row
        if (i==x-1){
            i=0;
            j++;
            t=0;
            g=n;
        }
        //If none of these conditions are fulfilled, put a '.' there and go to the next letter
        else {
            new[j][i] = '.';
            i++;


        }
        //If the letters aren't the same but you found at least the first letter, then reset
        if (g!=n && a!=b){
            g=n;
        }
        //If the letters are the same, and your at the end of the row and you found some of the letters
        //Then reset
        if (a==b && i==x && g!=0){
            g=n;
            j++;
            i=0;
            t=0;
        }

    }


    printf("I found the word %s %d times Left to Right\n",read,found);
    return found;

}
int RightoLeft(int x,int n,int t,char*read){
    //Starts at the end of the row, and works backwards
    int i=x-1;
    int j=0;
    int found =0;
    int f= 0;
    int q = t;
    int g = n;
    char a = ult[j][i];
    char b = read[t];



    while (j<=x){
        a=ult[j][i];
        b=read[t];
        //If you found a matching letter, subtract one from count and go to the next letter
        if (a==b){
            f=i;
            g--;
            t++;
        }
        //If you have found a word
        if (g==0 ){
            while (q>0){
                new[j][i] = ult[j][i];
                i++;
                q--;
            }
            q=n;
            i=f+1;
            found++;
            g=n;
            t=0;

        }
        //if you are at the end of the row
        if (i<0){
            i=x-1;
            j++;
            t=0;
            g=n;
        }
        //if none of these, put a '.' in the spot
        else {
            new[j][i] = '.';
            i--;


        }
        //if you think you have part of a word, but the letters are not the same
        if (g!=n && a!=b){
            //check if the next letter is the first letter, if so set it back to 1
            if(ult[j-1][i]==read[0]){
                g=n-1;
            }
            //Otherwise,reset
            else{
                g=n;
            }}
            //If the last letter in the row is a match but G is not 0, reset
        if (a==b && i<0 && g!=0){
            g=n;
            j++;
            i=x-1;
            t=0;
        }

    }
    printf("I found the word %s %d times Right to Left\n",read,found);
    return found;
}
 //This function simply traverse up and down rather than side to side
int UptoDown(int x,int n,int t,char*read){
    int i=0;
    int j=0;
    int found =0;
    int g = n;
    char a = ult[j][i];
    char b = read[t];
    int f =0;
    while (i<=x){
        a=ult[j][i];
        b=read[t];
        if (a==b){
            f=j;
            g--;
            t++;

        }

        if (g==0 ){
            j=f+1;
            found++;
            g=n;
            t=0;

        }
        if (j>=x-1){
            j=0;
            i++;
            t=0;
            g=n;
        }
        else {
            new[j][i] = '.';
            j++;


        }
        if (g!=n && a!=b){
            if(ult[j-1][i]==read[0]){
                g=n-1;
            }
            else{
                g=n;
            }}
        if (a==b && j==x-1 && g!=0){
            g=n;
            j=0;
            i++;
            t=0;
        }

    }
    printf("I found the word %s %d times Top to Bottom\n",read,found);
    return found;
}
int DowntoUp(int x,int n,int t,char*read){
    int i=0;
    int j=x;
    int found =0;
    int f= 0;
    int g = n;
    char a = ult[j][i];
    char b = read[t];
    int q=n;
    while (i<=x){
        a=ult[j][i];
        b=read[t];
        if (a==b){
            f=j;
            g--;
            t++;

        }

        if (g==0 ){
            while (q>0){
                new[j][i] = ult[j][i];
                j++;
                q--;
            }
            q=n;
            j=f-1;
            found++;
            g=n;
            t=0;

        }
        if (j<0){
            j=x+1;
            i++;
            t=0;
            g=n;
        }
        else {
            new[j][i] = '.';
            j--;


        }
        if (g!=n && a!=b){
            g=n;
        }
        if (a==b && j<0 && g!=0){
            g=n;
            j=x+1;
            i++;
            t=0;
        }

    }
    printf("I found the word %s %d times Bottom to Top\n",read,found);
    return found;

}
//This function prints the resultant matrix 
void Print(int x){
    int j=0;
    int    i=0;
    //While you still have more columns to print
    while (j<=x-2){
        printf("%c",new[j][i]);
        //When you are at the end of the row,reset
        if (i == x-2){
            printf("\n");
            i = 0;
            j++;
        }
        else{
            i++;
        }
    }
}
