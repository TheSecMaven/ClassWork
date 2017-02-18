#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"
#include "poly.h"

//Function Declarations
void Phase1(void);
void Phase2(void);
void Phase3(void);

int main(int argc, char *argv[]) {
    char *ans;
	printf("\nTesting your project 3 polynomial functions - addTerm, printPoly, evaluate, derivative\n\n");
	//Initiate testing of an empty polynomial, while adding terms, evaluating if they are correct, as well as taking the derivitave of the terms
    Phase1();

    printf("\nDo you want to check that your polynomials are always properly formatted (y/n) : "); 
    //Confirms with user if phase2 and phase3 need to be executed 

    ans = readToken(stdin);
    if ( strcmp(ans,"y") == 0 || strcmp(ans,"Y") == 0 || strcmp(ans, "yes") == 0 ) 
	    Phase2();

    printf("\nDo you want to check polynomial addition and subtraction (y/n) : ");
    ans = readToken(stdin);
    if ( strcmp(ans,"y") == 0 || strcmp(ans,"Y") == 0 || strcmp(ans, "yes") == 0 ) 
	    Phase3();

    return 0;
}
//Tests the addition of new terms into an empty polynomial list
void Phase1(void) {
	printf("Phase One Testing\n");
	printf("=================\n");

	Poly *p1 = NULL;
	printf("\nThe initial (empty) polynomial is ");
	printPoly(p1, stdout);
	printf("\n");

	printf("\nEnter the coefficient and exponent for a term in the polynomial : ");
	double c;
	int e;
	c = readReal(stdin);
	e = readInt(stdin);
	while ( c != -1 && e != -1 ) {
		p1 = addTerm(c, e, p1);
		printf("Enter the coefficient and exponent for the next term (or -1 -1 to exit) : ");
		c = readReal(stdin);
		e = readInt(stdin);
	}
	printf("\nThe polynomial is now : ");
	printPoly(p1, stdout);
	printf("\n");

	printf("\nEvaluation: Evaluating the polynomial for three values of x\n");
	double num1, num2, num3;
	printf("\nEnter the first value for x : ");
	num1 = readReal(stdin);
	printf("At x=%lf, the polynomial's value is %lf\n", num1, evaluate(num1, p1) );
	printf("\nEnter the second value for x : ");
	num2 = readReal(stdin);
	printf("At x=%lf, the polynomial's value is %lf\n", num2, evaluate(num2, p1) );
	printf("\nEnter the third value for x : ");
	num3 = readReal(stdin);
	printf("At x=%lf, the polynomial's value is %lf\n", num3, evaluate(num3, p1) );

	printf("\nDerivatives: Taking the derivative of the polynomial\n");
	p1 = derivative(p1);
	printf("\nThe derivative of the polynomial is ");
	printPoly(p1, stdout);
	printf("\n");
	return;
}
//Tests m derivative of polynomials as well as basic add-terms
void Phase2(void) {
	printf("\n\nPhase Two Testing\n");
	printf("=================\n");

    Poly *p1, *p2, *ans;
    p1 = p2 = NULL;

    printf("The polynomials are\n");
    p1=addTerm(3,3,p1); p1=addTerm(5,5,p1); p1=addTerm(1,1,p1); p1=addTerm(4,4,p1); p1=addTerm(2,2,p1);
    p2=addTerm(9,2,p2); p2=addTerm(1,9,p2); p2=addTerm(4,5,p2); p2=addTerm(5,4,p2);
    printf("\tp1: "); printPoly(p1, stdout); printf("\n");
    printf("\tp2: "); printPoly(p2, stdout); printf("\n");

    printf("\nEvaluting p1 at 5 gives a value of %.2lf\n", evaluate(5, p1));
    printf("\nEvaluting p2 at 4 gives a value of %.2lf\n", evaluate(4, p2));

    printf("\nThe derivative of p1 is\n\t");
    ans = derivative(p1);
    printPoly(ans, stdout); printf("\n");

    printf("\nThe derivative of p2 is\n\t");
    ans = derivative(p2);
    printPoly(ans, stdout); printf("\n");

    return;
}
//Test the addition and subtraction of different polynomials and evaluates their correctness.
void Phase3(void) {
	printf("\n\nPhase Three Testing\n");
	printf("===================\n");

    Poly *p1, *p2, *ans;
    p1 = p2 = NULL;

    printf("The polynomials are\n");
    p1=addTerm(5,1,p1); p1=addTerm(4,2,p1); p1=addTerm(3,3,p1); p1=addTerm(2,4,p1); p1=addTerm(1,5,p1);
    p2=addTerm(1,1,p2); p2=addTerm(2,2,p2); p2=addTerm(3,3,p2); p2=addTerm(4,4,p2); p2=addTerm(5,5,p2);
    printf("\tp1: "); printPoly(p1, stdout); printf("\n");
    printf("\tp2: "); printPoly(p2, stdout); printf("\n");

    ans = addPoly(p1,p2);
    printf("\nAdding p2 and p1 results in the new polynomial\n\t");
    printPoly(ans, stdout); printf("\n");
    ans = subtractPoly(p1,p2);
    printf("\nSubtracting p2 from p1 results in the new polynomial\n\t");
    printPoly(ans, stdout); printf("\n");

    p1 = p2 = NULL;

    printf("\nThe polynomials are\n");
    p1=addTerm(1,1,p1); p1=addTerm(5,5,p1);
    p2=addTerm(2,2,p2); p2=addTerm(3,3,p2); p2=addTerm(4,4,p2);
    printf("\tp1: "); printPoly(p1, stdout); printf("\n");
    printf("\tp2: "); printPoly(p2, stdout); printf("\n");

    ans = addPoly(p1,p2);
    printf("\nAdding p1 and p2 results in the new polynomial\n\t");
    printPoly(ans, stdout); printf("\n");
    ans = subtractPoly(p2,p1);
    printf("\nSubtracting p1 from p2 results in the new polynomial\n\t");
    printPoly(ans, stdout); printf("\n");

    return;
}
