project3:	project3.o 
			g++ -std=c++11 -Wall -o project3 project3.cpp SparseMatrix.cpp


clean:		
			rm -f *.o project3
