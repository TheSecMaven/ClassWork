//Project 1 by Miclain Keffeler
//This program determines what gift to get for specific kinds of people
//Based off of a logic tree we were presented with
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

//Define questions globally for easy access
char *family1 = "Which family member is it?\t";
char *mom = "Is it your mom?\t";
char *beating = "Did they ever beat you up?\t";
char *last = "When did you last see them?\t";
char *type = "What type of friend is this person?\t";
char *roommate = "Is he or she your roommate?\t";
char *date = "Are you dating them?\t";
char *everdate = "Did you ever date them?\t";
char *friends = "Are you still friends?\t";
char *goodfriend = "Are you good friends?\t";
char *will = "Are you in their will?\t";
char *deserve = "Did you deserve to get beaten up?\t";
char *wash = "Does she still do your wash?\t";
//GetYesNo function returns a 1 for yes and 0 for no. 
//This function is used for all questions that require a yes or no answer
char *a;
int getYesNo(char *x){
    printf("%s\n",x);
    a = readToken(stdin);
    if (strcmp(a,"yes")==0)
        return 1;
    else
        return 0;
}
//This function asks the question at hand and then assigns the answer to a 
// numerical value that is referenced in friend and family function logic
int getAnswer(char *a){
    char *b;
    int result = 0;
    printf("%s\n",a);
    b = readToken(stdin);
    if (strcmp(b,"family")==0)
        result =0;
    else if(strcmp(b,"friend")==0)
        result =1;
    else if(strcmp(b,"parent")==0)
        result =2;
    else if(strcmp(b,"sibling")==0)
        result =3;
    else if (strcmp(b,"other")==0)
        result =4;
    else if (strcmp(b,"childhood")==0)
        result =5;
    else if(strcmp(b,"college")==0)
        result =6;
    else if (strcmp(b,"recently")==0)
        result =7;
    else if (strcmp(b,"long-time")==0)
        result =8;
    else if (strcmp(b,"never")==0)
        result =9;

    return result;
}
//This function contains logic for all friend possibilities
char *friend(int fd){
    int rgd,rpl,wer,ght,jjj,ttt;
    int rew =0;
    char *rt = NULL;
    int rty = getAnswer(type);
    if (rty == 5){
        rgd = getAnswer(last);
        if (rgd == 7){
            rpl = getYesNo(everdate);   
            if (rpl ==1){
                rew = getYesNo(friends);
                if (rew ==1){
                    rt = "\nRecommendation:Something small but nice\n";
                }
                else if (rew == 0){
                    rt = "\nRecommendation- Just a card\n";
                }
                else if (rpl == 0){
                    rt ="\nRecommendation- nothing\n";
                }}}
        else if (rgd == 8){
            wer = getYesNo(goodfriend);
            if (wer ==1){
                rt = "\nRecommendation- Just a card\n";
            }
            else if (wer == 0){
                rt = "Recommendation- nothing\n";
            }}}
    else if (rty == 6){
        ght = getYesNo(roommate);
        if (ght == 1){
            rt = "Recommendation- Just a card\n";
        }
        else if (ght == 0){
            jjj =getYesNo(date);
            if (jjj == 1){
                rt = "Recommendation- A really special gift\n";
            }
            else if (jjj == 0){
                ttt = getYesNo(goodfriend);
                if (ttt == 1){
                    rt = "Recommendation- Just a card\n";
                }
                else if (ttt == 0){
                    rt = "Recommendation- Nothing\n";
                }}}}
                return rt;
}

//This function contains the logic for all family possibilities                 
char *family(int l){
    int rx,rt,fg,rs,tr,ty,ut;
    char *az=NULL;
    rx = getAnswer(family1);
    if (rx==2){
        fg = getYesNo(mom);
        if (fg ==1){
            rt = getYesNo(wash);
            if (rt == 1){
                az ="Recommendation- A really special gift\n";
            }
            else if (rt ==0){
                az = "Recommendation- Something small but nice\n";
            }}
        else if (fg ==0) {
            az = "Recommendation- Just a card\n";}}
    else if (rx == 3){
        rs = getYesNo(beating);
        if (rs == 1){
            tr = getYesNo(deserve);
            if (tr == 1){
                az = "Recommendation- Just a card\n";
            }
            else if (tr == 0){
                az = "Recommendation- Nothing\n";
            }}      
        else if (rs ==0){
            az = "Recommendation- Just a card\n";
        }}
    else if (rx == 4){
        ty = getAnswer(last);

        if (ty == 7){
            az = "Recommendation- Just a card\n";
        }
        else if  (ty == 9){
            ut = getYesNo(will);

            if (ut == 1){
                az = "Recommendation- Just a card\n";
            }
            else if  (ut ==0){
                az = "Recommendation- Nothing\n";
            }}
    }
    return az;
}

int main(int argc, char *argv[]){
    char *ds,*rd;
    char *who = "Who is receiving the gift?";
    printf("Welcome to the Gift Decider.\n");
    int z = getAnswer(who);
    //This conditional determines whether to run family or friend logic
    //based on answer to who is receiving gift question.
    if (z ==0){
        ds = family(z);
        printf("%s",ds);
    }
    else if (z ==1){
        rd = friend(z);
        printf("%s",rd);
    }
    else {
        printf("Invalid Entry");
    }    
}
