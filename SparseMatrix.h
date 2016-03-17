#ifndef SparseMatrix_H
#define SparseMatrix_H
//Struct node holds my data and link to next node
struct Node {
    int row;
    int col;
    double val;
    Node *next;
};
//SparseMatrix class, initializer to NULL and Initializer with values
class SparseMatrix {
    public:
        int constructor;
        SparseMatrix( ) { p=NULL;  }
        SparseMatrix(int row,int col, double val, SparseMatrix &m);
        Node *p;
        SparseMatrix(int row,int col, double val, SparseMatrix::SparseMatrix &m,int x);
    //Creates first value for list essentially
    private:
    //Functions and operators made/used with SparseMatrixes
        int Max_Row(SparseMatrix list,int i);
        int Max_Columns(SparseMatrix list,int i);
        int Min_Columns(SparseMatrix list, int i);
        friend std::ostream& operator<< (std::ostream&outfile, SparseMatrix&m);
        friend  std::istream& operator>> (std::istream&input, SparseMatrix&m);
        friend  SparseMatrix operator+(SparseMatrix m1, SparseMatrix m2);
        friend  SparseMatrix operator*(SparseMatrix m1, SparseMatrix m2);
        friend  SparseMatrix operator-(SparseMatrix m1, SparseMatrix m2);

};
//Declarations
int Max_Row(SparseMatrix list,int i);
int Max_Columns(SparseMatrix list,int i);
int Min_Columns(SparseMatrix list, int i);
std::ostream& operator<<(std::ostream&outfile, SparseMatrix&m);
std::istream& operator>>(std::istream&input, SparseMatrix&m);
SparseMatrix operator+(SparseMatrix m1, SparseMatrix m2);
SparseMatrix operator*(SparseMatrix m1, SparseMatrix m2);
SparseMatrix operator-(SparseMatrix m1, SparseMatrix m2);
#endif

