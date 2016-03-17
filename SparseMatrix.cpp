/*Project 3 by Miclain Keffeler
this program will read in data points from a file (row col and val) and store it in a linked list. I then overloaded the + - * and << >> operators 
to work with matrices. Specifically, sparse matrices. The program should 
add, multiply, subtract, read in, and print out sparse matrices.
*/
//This program comes with a class definition of SparseMatrix and also should
//have a header file that comes with it FYI
#include<iostream>
#include<fstream>
#include<cctype>
#include"SparseMatrix.h"
using namespace std;
int check=0;
//Function to find the highest row number in a column of the sparsematrix.
int Max_Row(SparseMatrix list,int j){
    Node *ptr=list.p;
    int MAX=0;
    //Read through the whole list 
    while(ptr!=NULL){
        if(ptr->row>MAX){
        //If the current row is higher than the other, set it as the highest.
            MAX=ptr->row;
        }
        ptr=ptr->next;
    }
    //Returns Max
    return MAX;
}
//Function to find the highest column number in a row.
int Max_Columns(SparseMatrix list,int i){
    Node *ptr=list.p;
    int MAX=0;
    while(ptr!=NULL){

        if(ptr->col>MAX){
            MAX=ptr->col;
        }
        ptr=ptr->next;


    }
    return MAX;
}
//This function finds the lowest number of columns in a row.
int Min_Columns(SparseMatrix list,int i){
    Node *ptr=list.p;
    int Min=0;
    while(ptr!=NULL){

        if(ptr->col<Min){
            Min=ptr->col;
        }
        ptr=ptr->next;


    }
    return Min;
}
//This can be used to truncate the matrices for time efficiency but I 
//Did not implement this due to time constraints

//+ operator overload for SparseMatrix
//This function only works when the both matrices are sorted by row 
SparseMatrix operator+(SparseMatrix m1, SparseMatrix m2){
    SparseMatrix m=m1;
    Node *ptr=m.p;
    Node *ptr1=m2.p;
    //Traversing Nodes set
    //While their is more to read
    while(ptr!=NULL){
//If you found a match
        if(ptr->row==ptr1->row && ptr->col==ptr1->col){
            //add them and go to the next one
            ptr->val+=ptr1->val;
            ptr1=ptr1->next;
        }
        //Else go to the next 
        ptr=ptr->next;
    }
    //While the other list is not empty yet
    while(ptr1!=NULL){
    //Add the new node to the list
        SparseMatrix *q=new SparseMatrix(ptr1->row,ptr1->col,ptr1->val,m,0);
        ptr1=ptr1->next;
    }

    //Return the list
    return m;
}
//Overloaded - operator for sparsematrices, same as + operator
SparseMatrix operator-(SparseMatrix m1, SparseMatrix m2){
    SparseMatrix m=m1;
    Node *ptr=m.p;
    Node *ptr1=m2.p;
//Node variables
    while(ptr!=NULL){
    //If you found a match
        if(ptr->row==ptr1->row && ptr->col==ptr1->col){
        //Subtract the values and go to the next one
            ptr->val-=ptr1->val;
            ptr1=ptr1->next;
        }
        //Next node
        ptr=ptr->next;
    }
    //Add the resulting nodes to the list
    while(ptr1!=NULL){
        SparseMatrix *q=new SparseMatrix(ptr1->row,ptr1->col,-ptr1->val,m,0);
        ptr1=ptr1->next;
    }
    //Return the list
    return m;
}

//Constructor for each node
//This constructor sorts the list by row
//This is used for the multiplication operator
SparseMatrix::SparseMatrix(int row,int col, double val, SparseMatrix::SparseMatrix &m,int x){
//Get the nodes established
    Node *temp=new Node;
    temp->row=row;
    temp->col=col;
    temp->val=val;
    temp->next=NULL;
    Node *ptr1=m.p;
    //if the list is empty
    if (m.p==NULL){
        temp->next=m.p;
        m.p=temp;
    }

    else{
//If the rows are out of order, go to the next one
        if(row<ptr1->row){
            temp->next=ptr1;
            ptr1=temp;
            return;
        }
        Node *ptr=m.p;
        Node *back;
//While youre not at the end and the rows are still out of order
        while(ptr !=NULL && ptr->row <row){
            //add to the list
            back=ptr;
            ptr=ptr->next;
        //keep traversing
        }
        //While the rows are equal and the columns are out of order
        while(ptr!=NULL && ptr->row == row && ptr->col <col){
            //add to the list
            back=ptr;
            ptr=ptr->next;
            //keep traversing
        }
        while(ptr1!=NULL){
        //If they are the same, add them
            if(ptr1->col==temp->col && ptr1->row==temp->row){
                ptr1->val+=temp->val;
                return;
            }
            //next node
            ptr1=ptr1->next;

        }
        back->next=temp;
        temp->next=ptr;
    }}
//Second constructor, this sorts by column
SparseMatrix::SparseMatrix(int row,int col, double val, SparseMatrix::SparseMatrix &m){
    Node *temp=new Node;
    temp->row=row;
    temp->col=col;
    temp->val=val;
    temp->next=NULL;
    Node *ptr1=m.p;
    if (m.p==NULL){
        temp->next=m.p;
        m.p=temp;
    }

    else{

        if(col<ptr1->col){
            temp->next=ptr1;
            ptr1=temp;
            return;
        }
        Node *ptr=m.p;
        Node *back;

        while(ptr !=NULL && ptr->col <col){
            back=ptr;
            ptr=ptr->next;
        }
        while(ptr!=NULL && ptr->col == col && ptr->row <row){
            back=ptr;
            ptr=ptr->next;
        }
        while(ptr1!=NULL){
            if(ptr1->col==temp->col && ptr1->row==temp->row){
                ptr1->val+=temp->val;
                return;
            }
            ptr1=ptr1->next;

        }
        back->next=temp;
        temp->next=ptr;
    }
}
//* operator overloaded
SparseMatrix operator*(SparseMatrix m1, SparseMatrix m2){
    SparseMatrix m;
    Node *ptr = m1.p;
    Node *ptr1 = m2.p;
    int val;
    int j=0;
    //Node setting 
    /*
    *** Keep in Mind that one list has to be sorted by ROW and the other
    *** must be sorted by COLUMN
    */
    //sets boundaries for each loop to stay in the area of matrix
    for(int i=0; i<=Max_Row(m1,i); i++){
        for( j=0;j<=Max_Columns(m2,i); j++){
            val = 0;
            //While the row is less than what we are searching for,next node
            while(ptr != NULL && ptr->row < i){
                ptr = ptr->next;
            }
            //And the col of the other is less than search, go to next node
            while(ptr1 != NULL && ptr1->col <j){
                ptr1 = ptr1->next;
            }
            //While you have the same row and col
            while(ptr->row == i && ptr1->col == j){
                //If the row is a match but col isn't, next
                if(ptr->row == i && ptr->col < ptr1->row){
                    ptr = ptr->next;
                }
                //If we have null, break
                if(ptr == NULL){
                    break;
                }
                //If the col is a match but row isn't, next
                if(ptr1->col == j && ptr->col > ptr1->row){
                    ptr1 = ptr1->next;
                }
                //If we have null, break
                if(ptr1 == NULL){
                    break;
                }
                //If everything is a match for what we want to multiply
                if(ptr->col == ptr1->row && ptr1->col == j && ptr->row == i){
                    val += ptr->val * ptr1->val;
                    //multiply and add and move to the next values
                    ptr = ptr->next;
                    ptr1 = ptr1->next;
                }
                //If either is null, break
                if(ptr == NULL || ptr1 == NULL){
                    break;
                }
            }
            //Add the node the resulting matrix, and reset
            SparseMatrix *q = new SparseMatrix(i,j, val, m,0);
            ptr = m1.p;
            ptr1 = m2.p;
        }
    }
    return m;
}
//Print out operator overload
ostream& operator<<(ostream &outfile, SparseMatrix &m){
    Node *ptr=m.p;
    //Set to the beginning of the list
    while(ptr!=NULL){
    //While its not the end and you have a valid value
        if(ptr->val!=0){
        //Print in this format
            outfile<<ptr->row<<" " <<ptr->col<<" "<< ptr->val;
            outfile<<"\n";
        }
        //Next node in list
        ptr=ptr->next;
    }
    outfile<<"0 "<<"0 "<<"0 ";
}
//Read in operator, if you are confused see the * operator notes
istream& operator>>(istream &input, SparseMatrix &m){
    int row,col;
    double val;
    input>>row>>col>>val;
//While you are still reading in
    while(row!=0 || col!=0 ||val!=0){
        if(check==0){
        //Check is used to determine if we will be multiplying matrices together
            if(m.constructor==0){
            //The constructor value must also be zero to confirm its *
                SparseMatrix *g=new SparseMatrix(row,col,val,m,1);
                input>>row>>col>>val;
                //Then keep reading
            }
            else{
            //Add the node and next
                SparseMatrix *g=new SparseMatrix(row,col,val,m);
                input>>row>>col>>val;
            }
        }
        else{
        //Add the node and next
            SparseMatrix *g=new SparseMatrix(row,col,val,m);
            input>>row>>col>>val;
        }
    }
 //Check must be added to make sure we don't do the same thing unnecessarily
 check++;
    return input;

}


