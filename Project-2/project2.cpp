//Project 2 by Miclain Keffeler
//Database Sorter/Reader for various information
#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<vector>

using namespace std;
//Function Declarations 
//Ascend and Descend float sort
void ascend_float(string **,int,int,int);
void descend_float(string **,int,int,int);

//Ascend and Descend String Sort
void ascend_string(string **, int,int,int);
void descend_string(string **,int,int,int);

//Swap function for ordering
void swap(string **, int,int,int);
//Descend and Ascend Int sort
void ascend_int(string **,int,int,int);
void descend_int(string **,int,int,int);
//Open stream for reading
ifstream infile;
//Contains Sort Criteria
string sorts[100][3];
void decider(string** data,int criteria_row,int columnchange,int rows, int columns);
string GetWord(ifstream &infile);
//Declared globally for easy access in functions
//Class Data, stores row and column information as well as the string that is ultimately used to hold data
class Data{
    public: 
        int rows=0;
        int columns=0;
        string **data;
//Declares an object of class Data as x        
}x;
int main(int argc, char **argv){
    ///////////////////////////////////////////////////////////////////
    //returns the number of rows and collums
    infile.open(argv[1]);
    string read;
    getline(infile,read);	
    int length = read.length();
    int counter = 0;
    //Column Counter
    for(counter = 0; counter <= length; counter++){
        if(read[counter] == ','){
            x.columns++;
        }
    }
    infile.close();
    //Close and reopen new file for reading through again
    infile.open(argv[1]);
    vector<string> titles;
    for(counter = 0; counter<x.columns+2; counter++){
        string temp;
        //Reads for titles of each column
        if(counter<x.columns){
            getline(infile,temp,',');
            titles.push_back(temp); 
        }
        else{
        //Otherwise, get new line and just add to title, end of columns
            getline(infile,temp);
            titles.push_back(temp); 
        }
    }
    //Row Counter
    //While there is more to read
    while(!infile.eof()){
        string checker;
        //Get line, and increment my rows
        getline(infile,checker);
        x.rows++;	
    }
    x.columns++;
    infile.close();
    //Will create a two d array to store the rest of the data
    //string data[rows][collums];
    x.data = new string*[50000];
    int i;
    //Initializes the 2d part of the string for each row
    for(i=0;i<50000;i++){
        x.data[i] = new string[100];
    }
    string dummy;
    infile.open(argv[1]);
    getline(infile,dummy);
    int r = 0;
    int c = 0;
    dummy.clear();
    //Reads until end of file
    while(!infile.eof()){
        while(c<x.columns){
        //Get a letter
            int letter = infile.get();
            //If youre at end of file, quit reading
            if( letter == EOF){
                break;
            }
            //If the letter is a comma or new line, add the word and move to next line and clear 
            if(letter == 44 || letter == 10 ){
                x.data[r][c] = dummy;
                dummy.clear();
                c++;
            }	
            else{
                dummy = dummy + (char)(letter);
            }
        }
        r++;
        c = 0;
    }
    infile.close();
    //goes through the second file and stores what we are searching  
    // for in a vector
    //Integers used to count various things
    int timesthrough = 0;
    int countlines = 0;
    infile.open(argv[2]);
    string temp2;
    //used to count total criteria to sort by
    while(getline(infile,temp2)){
        countlines++;
        temp2.clear();	
    }	
    infile.close();	
    ofstream outfile;
    outfile.open("output.csv");
    int h=0;
    infile.open(argv[2]);
    string file=argv[2];
    int criteria_count=0;
    //While there is more criteria to read in
    while(countlines>0){
        string linein;
        string temp1;
        counter=0;
        while(counter<=2){
        //Get a word, and put it in the specified spot in string sorts
            temp1=GetWord(infile);
            sorts[h][counter]=(temp1);
            temp1.clear();
            //Clear and increment for next word in criteria
            counter++;
        }
        h++;
        criteria_count++;
        //increment my counters used to sort
        --countlines;
    }
    infile.close();
    //While you haven't sorted by all criteria neccesary
    while(criteria_count>0){
        int columnchange = 0;
        //Start with last criteria, least important
        string col_search=sorts[h-1][0];
        //Finds column to sort by in titles
        while(col_search.compare(titles[columnchange]) != 0){
            columnchange++;

        }
        //Runs function that specifies which function to call and ascending or descending for that criteria
        decider(x.data,h-1,columnchange,x.rows,x.columns);
        criteria_count--;
        //Increment everything and sort for the next criteria
        h--;
    }
    //sorts the array 
    //prints the final string of data (2d) to output file
    int ro = 0;
    int col = 0;
    //Prints the titles to output
    while(col < x.columns){
    //if this is not the last column, print a comma after the title
        if(col < x.columns-1){
            outfile<<titles[col]<<',';
        }
        else{ 
        //Otherwise, just print the title to output
            outfile<<titles[col]<<"\n";
        }	
        //Increment
        col++;
    }	
    col=0;
    //Reset and continue again, prints the rest of the data entries after sorted
    while(ro<x.rows-1){
        while(col<x.columns){
            if(col<x.columns-1){
                outfile<<x.data[ro][col]<<',';
            }
            else{
                outfile<<x.data[ro][col]<<endl;
            }
            col++;
        }
        ro++;
        col = 0;
        timesthrough++;
    }
    outfile.close();
    return 0;
}
string GetWord(ifstream &infile){
    // Creates variables for the final word and each character read in
    string word;
    char c;

    // Reads in one character, or sets c to NULL if it is the end of the file
    if(!infile.eof()){
        c = infile.get();
        }
    else{
        c = '\0';
}
    // If c is not ',' or '\n', adds that letter to the word
    while(c != ',' && c != '\n' && !infile.eof()){
        word.push_back(c);
        //Increment and get next letter for the word
        c = infile.get();
    }

    //Return the word that was found
    //      string
    return word;
}
//Chooses which function I will be using for each criteria
void decider(string **data,int criteria_row, int columnchange, int rows, int columns){
    string data_1=sorts[criteria_row][2];
    //If we are sorting ascending for this specific criteria
    if(sorts[criteria_row][1]=="ascend"){
        //If we are sorting Strings
        if(data_1[0]=='s'){
            ascend_string(data,rows,columns,columnchange);
        }
        //If we are sorting ints
        if(data_1[0]=='i'){

            ascend_int(data,rows,columns,columnchange);
        }
        //If we are sorting floats
        if(data_1[0]=='f'){
            ascend_float(data,rows,columns,columnchange);
        }
    }
    //If we are sorting descending (only other option)
    else{//If we are sorting strings
        if(data_1[0]=='s'){
            descend_string(data,rows,columns,columnchange);
        }
        //If we are sorting Ints
        if(data_1[0]=='i'){
            descend_int(data,rows,columns,columnchange);
        }
        //If we are sorting floats
        if(data_1[0]=='f'){
            descend_float(data,rows,columns,columnchange);
        }
    }
}
void swap(string **array,int row1,int row2,int ccols){
    //Function swaps all columns for a specific two rows that need to be switched
    for(int i=0;i<ccols;i++){
    array[row1][i].swap(array[row2][i]);
    }
    }
/*The following six functions all implement Shell sort
*Shell sort is a far more efficient insertion sort
*Essentially, shell sort avoids large shifts in the case of a very large or small value being far to the right or left
* each respectively. By cutting this out, we can save a lot of time
*
*
*/

void ascend_int(string **array,int rows,int columns, int ccols){
    int j;
    for(int gap=rows/2;gap>0;gap/=2){
        for(int i=gap;i<rows-1;++i){
            int temp=stoi(x.data[i][ccols]);
            for(j=i;j>=gap && temp<stoi(x.data[j-gap][ccols]);j-=gap){
                swap(array,j,j-gap,columns);
            }}}}

void descend_int(string **array,int rows,int columns,int ccols){
    int j;
    for(int gap=rows/2;gap>0;gap/=2){
        for(int i=gap;i<rows-1;++i){
            int temp=stoi(x.data[i][ccols]);
            for(j=i;j>=gap && temp>stoi(x.data[j-gap][ccols]);j-=gap){
                swap(array,j,j-gap,columns);
            }}}}

void ascend_float(string **array, int rows,int columns,int ccols){
    int j;
    for(int gap=rows/2;gap>0;gap/=2){
        for(int i=gap;i<rows-1;++i){
            int temp=stod(x.data[i][ccols]);
            for(j=i;j>=gap && temp<stod(x.data[j-gap][ccols]);j-=gap){
                swap(array,j,j-gap,columns);
            }
            x.data[j][ccols]=temp;
            }}}

void descend_float(string **array,int rows,int columns, int ccols){
    int j;
    for(int gap=rows/2;gap>0;gap/=2){
        for(int i=gap;i<rows-2;++i){
            int temp=stof(x.data[i][ccols]);
            for(j=i;j>=gap && temp>stof(x.data[j-gap][ccols]);j-=gap){
                swap(array,j,j-gap,columns);
            }
            }
            }}

void ascend_string(string **array,int rows,int columns, int ccols){
    int j;
    for(int gap=rows/2;gap>0;gap/=2){
        for(int i=gap;i<rows-1;++i){
            for(j=i;j>=gap && array[j-gap][ccols].compare(array[j][ccols])>=0;j-=gap){
                swap(array,j,j-gap,columns);
            }}}}

void descend_string(string **array,int rows,int columns, int ccols){
    int j;
    for(int gap=rows/2;gap>0;gap/=2){
        for(int i=gap;i<rows-1;++i){
            for(j=i;j>=gap && array[j-gap][ccols].compare(array[j][ccols])<=0;j-=gap){
                swap(array,j,j-gap,columns);
            }}}}

