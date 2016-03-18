In this project, you are asked to write a class named SparseMatrix that satisfies the following requirements. (The class will be defined and implemented in SparseMatrix.h and SparseMatrix.cpp respectively.)
 Define a data structure to efficiently represent a sparse matrix. You shall represent the sparse matrix internally using a linked structure. Do not use a 2D array representation, because some row and column numbers will be so large that a 2D array representation would be too inefficient in terms of both running time and memory usage. Matrix elements with value 0 are not permitted to appear within the sparse matrix representation.
 The default constructor will create a zero matrix (a matrix with all the elements being zero).
 Overload the + operator to get the sum of two sparse matrices.
 Overload the - operator to get the difference of two sparse matrices.
 Overload the * operator to get the product of two sparse matrices. Please see
https://en.wikipedia.org/wiki/Matrix_(mathematics) for the definition of matrix
multiplication.
 Overload the << operator to write a sparse matrix to an output stream. A file written by
the output stream via << must be in the correct format to be readable by a future >>
operation. The file format for a sparse matrix is to be described later.
 Overload the >> operator to read a sparse matrix from an input stream.
