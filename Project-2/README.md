Write a C++ program project2.cpp that operates as described below.
• Your program should accept three command line arguments. The first two arguments are
names of input files, and the third argument is the name of an output file.
• The data in all three files will be stored as comma-separated values (csv files format).
You must use C++ streams for all I/O. You cannot use Scanner from cs100.
• You can take a look at csv files with an ordinary text file editor or by using Microsoft Excel.
Both views will be illustrated in the examples below.
• The first input file contains a database arranged as a 2-dimensionsal table. The first line (row)
contains column headings. Each remaining line (row) contains a data record that consists of plain-text fields separated by commas. You may assume that each file contains at most 50000 rows, and that every row contains the same number of fields which is at most 100.
The second input file specifies how your program should sort the data from the first input file. Each row of the second file has three fields, as follows. The first field is a column name from the first input file, the second field specifies the direction (ascend or descend), and the
third field specifies the data type (string, int, or float). The first row denotes the primary key
for sorting, the second row (if it exists) denotes the secondary key, etc.
The output file should contain the same data as the first input file, with the rows rearranged as specified in the second input file. However, the first line of the output file should still contain the column headings.
Because the exact size of the database is not known in advance, your program should use an efficient sorting algorithm. Otherwise your program might be too slow for some larger data files, and if so then points will be deducted.
• Your program must define and use a class that stores the information found in a csv file. This class should contain at least the number of rows, the number of columns, and the data itself.
