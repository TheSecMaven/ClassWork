//Project 1 by Miclain Keffeler
//Takes in file, separates and reads ONLY words into a array of strings
//can actively search for any word and effectively use the '?' to 
//Represent any letter or be removed to represent nothing.
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
//Including all libraries neccesary
using namespace std;
//Declaring all functions
//This function is used to call the searching for a word
void WordSearch(string read[10000],int count, string words);
//Will count the number of unique words and return it
int uniqueCounter(string read[10000],int amount);
//Will convert all strings into lowercase for uniform reading/checking
string toLower(string word);
//This function will search for a '?' and then decide what the next step
//is to continue solving the problem at hand.
void SearchQMark(string read[10000],int count, string game);
//Checks for occurences of any word that is plugged into it
int occurences(string read[10000],int count, string words);

int main (int argc, char **argv) {
    //open the file from the command line
    ifstream file;
    file.open(argv[1]);
    //If the file fails to open/ does not exist
    if(file.fail()) {
        cout <<"I failed to open the file, please try again\n";
    }

    int i=0;
    //This string will hold the words from the file named 'file'
    string read[10000];
    string word;
    int count=0;
    int unique=0;
    char c;
    char last;
    int counted=0;
    //While you are still reading individual characters into the string
    while (file.get(c)){
        //If it is anything except for a letter, add the word and reset, adding one
        if ((c>=32 && c <=64) || (91<= c && c  <= 96) || c>=123){
            //Double check that we are correct it is NOT a letter
            if((last>=32 && last <=64) || (91<=last && last<= 96) || last>=123)
            {
                //spot I in read gets the lowercase word that came before this 
                read[i] = toLower(word);
                word = "";
                //Increments the spots
                i++;
                //Add one to count of total words
                counted++;
            }
            else{

                read[i] = toLower(word);
                word = "";
                i++;

                count++;
            }
        }
        //If it is a letter, add it to the string 'word', and continue
        if (('Z'>=c && c >='A') || ('z' >=c && c  >= 'a')){
            word +=c;

        }
        //If you just read the end of text character
        if (c==3){
            //Add the word and reset, increment
            read[i]=toLower(word);
            word= "";
            count++;
            i++;
        }
        //If you read a new line character, add the word and increment
        if (c==10){
            read[i] = toLower(word);
            word = "";
            i++;
            count++;
        }
        //Keeps the last character in mind in case of a non letter and space
        //That are next to each other, to separate words effectively
        last=c;
    }
    //Gets count of unique words now that we are done reading them in
    unique=uniqueCounter(read,(count+counted));
    cout << "The number of words found in the file was " << count-1;
    cout << "\nThe number of unique words found in the file was " << unique<< endl;
    //Prompts user to enter a word to search for, and reads in a string
    string search = "";
    cout << "\nPlease enter a word to search for or enter 0 to quit: ";
    cin >> search;
    int qmark=0;
    //Used to reference the question mark character
    char questionmark=63;
    //While the word is not our EOF character, '0'
    while (search.compare("0")!=0){
        //read the whole word and tell me if you find any question marks
        for(i=0;i<search.length();i++){
            if(search[i]==questionmark){
                qmark++;
            }
        }
        //If you found one or more in the search word, go to SearchQMark function
        if(qmark>0){
            SearchQMark(read,(count+counted),toLower(search));
        }
        //Otherwise, just do regular WordSearch
        else{
            WordSearch(read,(count+counted),toLower(search));
        }
        //Restart loop, ask again, and read it.
        cout << "\nPlease enter a word to search for or enter 0 to quit: ";
        cin >> search;
        //Question mark count reset
        qmark=0;
    }
    //Close the file now that we are done, for good measure
    file.close();
    return 0;


}
//This function will search for any words that can match any words read in
//According to the rules presented for question marks in Project 1
void SearchQMark(string read[10000],int count, string word){
    int length=word.length();
    string searching;
    int i=0;
    int found=0;
    int j=0;
    //Copy of word read in, to test.
    searching=word;
    //Tell me how many question marks there are present
    for(i=0;i<length;i++){
        if (searching[i]==63){
            found++;
        }
    }
    //Booleans used to test for letters and question marks, or just '?' 
    bool notqmarks=true;
    bool onlyqmarks=false;
    //Copy of word read in, for testing.
    string search=searching;

    for(i=0;i<length;i++){
        //If you found the question marks, set it true
        if(searching[i] == 63){
            onlyqmarks=true;
        }
        //If any letter is not a question mark, make this false
        else{
            notqmarks=false;
        }}
    //Erases all question marks from word, to test for matches without them
    for(i=0;i<length;i++){
        if(search[i] == 63){
            //Erases spot without assigning a null or space that would screw it up
            search.erase(i,1);
            //Must subtract to offset change in count from erasing one character
            i--;
        }

    }
    //if you found an occurence of the word searched for, run the WordSearch
    if(occurences(read,count,search)>=1){
        WordSearch(read,count,search);
    }
    //If it truly is just question marks and nothing else
    if (onlyqmarks==true && notqmarks==true){
        for(i=0;i<count;i++){
            //check if you're printing spaces
            if(read[i]==" "){
            }
            //Print every occurence of every word, because it could be anything
            else{
                WordSearch(read,count,read[i]);
            }}}
    //Replacement is equal to the ASCII table value for 'a'
    char replacement = 97;

    for(i=0;i<=length;i++){
        //If you have at least 1 question mark and its currently another '?'
        if(searching[i] == 63 && found ==1){
            while(j<27){
                //run through every letter and check for occurences of that word
                searching[i]=replacement;
                found=occurences(read,count,searching);
                //if you found an occurence of the word with the test letter
                if(found >0){                    
                    //Run it through WordSearch, and increment appropriately
                    WordSearch(read,count,searching);
                    j++;
                    replacement++;
                    found--;
                }
                else{
                    //Otherwise, increment to test for other words
                    j++;
                    replacement++;
                }
            }
        }
        //if you have potentially more than 2 question marks
        else if (searching[i] == 63 && found >1){
            //Check if their is only 1 letter in the search word
            if (length-found==1){
                //If the first character is a question mark
                if(searching[0] ==63){
                    //Run every possible letter it could be
                    searching[0]=replacement;
                    found=occurences(read,count,searching);
                    if (found >0){
                        //If you found an occurence of that word, run
                        //Increment properly to keep checking for more
                        WordSearch(read,count,searching);
                        replacement++;
                    }
                }
                for(i=0;i<count;i++){
                    //If you find the first letter of the search word in spot 0
                    char test=read[i].find(searching[0]);
                    if (test==0){
                        if(read[i].length()<= length){ 
                            //and the length is equal to or less than the search
                            //Run that word through the system
                            WordSearch(read,count,read[i]);
                        }

                    }
                }
            }
        }
    }
}


//This function runs through the string and checks if a word is in the file
int occurences(string read[10000],int count,string word){
    int count3 = count;
    int count2=0;
    int i=0;

    while(count3 > 0){
        //if you have a matching word, add it to the count and increment
        if (read[i] == word){
            count2++;
            i++;
            count3--;
        }
        else{
            //Otherwise, just increment
            i++;
            count3--;
        }
    }
    //Return total occurences of any word that is run through the function
    return count2;

}
//Searchs for any word that contains only letters, no Question marks 
//can be present in the search using this function
void WordSearch(string read[10000],int count, string find){
    int count2 = 0;
    int i=0;
    int count3 = count;
    while(count3 > 0){
        //if you find a match, show it in the count of total occurences
        if (read[i] == find){
            count2++;
            i++;
            count3--;
        }
        //Otherwise, increment forward in the list
        else{
            i++;
            count3--;
        }
    }
    //Print the final statement to show findings of occurences
    cout << "\nThe word " << find << " appears " << count2 << " times in the document";

}
//Returns integer giving total amount of unique words
int uniqueCounter(string read[10000],int max){
    string uniqueArray[10000];
    int counter=0;
    //Boolean used to verify no word occurs twice
    //I assigned the words to a new array to have it separated and to be used easily, but ended up not using this.
    bool unique = true;
    for(int i=0;i <max;i++){
        unique=true;
        //Set to true default everytime
        for (int j=0;j<max;j++){
            //If this spot in read is the same as the respective spot
            //In the unique array,set it to false
            if(read[i].compare(uniqueArray[j])==0){
                unique=false;
            }
        }
        //If we have true, add it to the list and add one to counter
        //then continue running, no one word will be put in this twice
        if(unique){
            uniqueArray[counter++]=read[i];
        }        
    }
    //Return total unique word count
    return counter;
}
//returns a string in all lowercase letters after converting
string toLower(string word){
    int i;
    //For you still have letters to read through
    for(i=0;i< word.length();i++){
        //used built in function to lower each character individually
        word[i] = tolower(word[i]);
    } 
    //return the lowercase string
    return word;
}

