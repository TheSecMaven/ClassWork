//Project3 by Miclain Keffeler
//Poly.c contains program definitions for p3.c to call for testing
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "scanner.h"
#include "poly.h"

//This function sorts and adds terms to the list of polynomials 
//Sorts them from highest to lowest exponent
Poly *addTerm(double d, int a, Poly *p){
    //Made 3 pointers, back, dd, and temp
    Poly *back = NULL;
    Poly *dd = NULL;
    dd = malloc(sizeof(Poly));
    back = malloc(sizeof(Poly));
    Poly *temp = NULL;
    temp = malloc(sizeof(Poly));
    //Temp is assigned the new term that is to be added to the list
    temp->coeff = d;
    temp->exp = a;
    temp->next = NULL;
    dd = p;
    //If the list is empty, just add the new term
    if(p == NULL) {
        p = temp;
        return p;
    }
    //Compare which term has the highest exponent
    //If new one is higher, put it in the front of the list
    else if (temp->exp > dd->exp){
        temp->next = dd;
        return temp;
    }
    //Else, back of the list
    else{
        back = p;
        dd = back->next;
        //This loop allows the program to run through until end of list
        while(p != NULL && back != NULL && dd != NULL && temp->exp < dd->exp){
            back = dd;
            dd=dd->next;
        }
        //Next term for each pointer
        back->next = temp;
        temp->next = dd;


        return p;
    }

}



//This function prints the polynomial 

void printPoly(Poly *p, FILE *fp){
    while (p != NULL){
        //If its not the end of list and exp = 0, just print the coeff no exp
        if(p->next != NULL){
            if (p->exp == 0){
                printf("%lf",p->coeff);
                p=p->next;
            }
            //Else, print the exponent with a + sign
            else{
                printf("%lfx^%d +",p->coeff,p->exp);
                p = p->next;}
        }
        //These statements handle logic for if the p->next is NULL
        else {
            if(p->exp == 0){
                printf("%lf",p->coeff);
                p=p->next;
            }
            else{
                printf("%lfx^%d",p->coeff,p->exp);
                p=p->next;
            }
        }

    }
};
//Evaluates the list for a specific number. This function is not correct. 
//THIS FUNCTION EVALUATES INCORRECTLY AS IT SITS CURRENTLY.
double evaluate(double a, Poly *p){
    double answer = 0;
    //reads through the whole list and continues to multiply all of the 
    //Coeff and exp together until end of list, adding them all to answer
    
    double r = 0;
    double t = p->exp;
    while (t !=0){
    r += a*a;
    t--;
    }
    while (p != NULL){
        answer += p->coeff * r;
        p = p->next;
    }
    return answer;
};
//Performs derivitive on every term of a list and then uses addTerm to
//make a new list that is equal to the derivitive
Poly *derivative(Poly *list){
    Poly *new = NULL;
    double d = 0;
    int a = 0;
    while(list != NULL){
        d = (list->coeff * list->exp);
        a = list->exp -1;
        new = addTerm(d,a,new);
        //Addterm once again checks and makes sure that the list is in order
        list = list->next;
    }
    return new;
}
//This function determines if they are the same exp or different
//Then either adds them together in one Poly or adds it into the list separately
Poly *addPoly(Poly *a, Poly *p){
    Poly *final = NULL;
    final = malloc(sizeof(Poly));
    while (p != NULL ){
        if (p->exp == a->exp){
            //Uses add term to merge the two Poly's into one term
            final = addTerm((p->coeff+a->coeff),p->exp,final);
            a = a->next;
        }
        else{
            //Makes a new term in the new list
            final = addTerm(p->coeff,p->exp,final);
        }
        p = p->next;
    }
    while(a != NULL){
        //merges everything into the final list until NULL
        final = addTerm(a->coeff,a->exp,final);
        a = a->next;
    }

    return final;
}

//Performs exact same function as addPoly except with negatives
Poly *subtractPoly(Poly *p, Poly *a){
    Poly *final = NULL;
    final = malloc(sizeof(Poly));
    while (p != NULL ){
        if (p->exp == a->exp){
            //Uses add term to merge the two Poly's into one term
            final = addTerm((p->coeff+a->coeff),p->exp,final);
            a = a->next;
        }
        else{
            //Makes a new term in the new list
            final = addTerm(p->coeff,p->exp,final);
        }
        p = p->next;
    }
    double d = 0;
    int r = 0;
    while(a != NULL){
        //merges everything into the final list until NULL
        d =-1* (a->coeff);
        r = a->exp;
        final = addTerm(d,r,final);
        a = a->next;
    }

    return final;



}


