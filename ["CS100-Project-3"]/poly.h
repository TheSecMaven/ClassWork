//Project3 by Miclain Keffeler
//Poly.h function definition class
#ifndef POLY_H
#define POLY_H
//Poly type gets defined
typedef struct block {
    //didn't use but inserted prev function for access to prev nodes easily
    struct block *prev;
    double coeff;
    int exp;
    struct block *next;
} Poly;
//Function definitions 
extern double evaluate(double, Poly *p);
extern Poly *derivative(Poly *p);
extern Poly *addPoly(Poly *a, Poly *p);
extern Poly *subtractPoly(Poly *a, Poly *p);
extern Poly *addTerm(double c, int e, Poly *p);
extern void printPoly(Poly *p, FILE *fp);  
#endif
