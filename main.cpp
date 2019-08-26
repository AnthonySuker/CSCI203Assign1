/* ------------------
Name: Anthony suker
Student Number: 6137210
Subject: CSCI203
Assignment: 1
 -------------------*/
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>

using namespace std;

//declarations
void read(string filename);

void linearSearch();

void prepBinarySearch();
bool binarySearch();

string reverseWord(string nStr);

void addEmord(string word);

void displayEmords();

//global var's
string dictionary[400000];
string emord[5];
int ctr = 0;
int emordCtr = 0;


int main(int argc, char *argv[]) {

    /**
     * TODO
     * get start time
     * read from file
     * add file contents into array
     * print size of array
     * get first 5 emordnilap's
     * get end time
     * display difference between start and end time
     */

    auto startTime = std::chrono::system_clock::now();

//read in dictionary.txt to dictionary[]
    try {
        read(argv[1]);
    } catch (string err) {
        cerr << err << endl;
    }

    cout<<"Number of words in dictionary: "<<ctr<<endl;

   // prepBinarySearch();

    linearSearch();
    displayEmords();

    auto endTime = std::chrono::system_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime-startTime);

    cout<<"Total run time (seconds): "<<duration.count()<<endl;


    return 0;


}

void read(string filename) {
    ifstream in;
    string line = "";
    in.open(filename);
    if (!in.good()) {
        string err = "> ERROR OPENING FILE\n> FILE NAME: " + filename;
        throw err;
    } else {
        cout << filename << "> READ GOOD!" << endl;
    }
    //prime data to avoid duplicate entries at the EOF
    in >> line;
    while (!in.eof()) {
        dictionary[ctr] = line;
        ctr++;
        in >> line;
    }

}

void linearSearch() {
    for (int x = 0; x < ctr; x++) {
        if (emordCtr == 5)return;
        for (int y = 0; y < ctr; y++) {
            if (dictionary[x] == reverseWord(dictionary[y])) {
                addEmord(dictionary[x]);
                break;
            }
        }
    }
}

/**Called as a recursive function to avoid loops
 * returns bool based on if an emord is found
 * terminating condition is when min and max are equal
 *      if its not that exact value an emord wont be found
 * @param word      parsed in reverse so reverse method isnt called repeatedly
 * @param min
 * @param max
 */
bool binarySearch(string word,int min, int max){
    int mid = (min + max)/2;

    if(word == dictionary[mid]) {
        return true;
    }else if(min == max){
        return false;
    }else if(word > dictionary[mid]){
        binarySearch(word,min,mid);
    }else if(word < dictionary[mid]){
        binarySearch(word,mid,max);
    }else{
        cerr<<">No condition met in binary search"<<endl;
    }

}



//normal string and reverse string
string reverseWord(string nStr) {
    string rStr="";
    for(int i = nStr.length()-1;i>=0;i--){
        rStr += nStr.at(i);
    }
    return rStr;
}

void addEmord(string word) {
    emord[emordCtr] = word;
    emordCtr++;
}

void displayEmords() {
    cout<<"First 5 emordnilap words:"<<endl;
    for(int i=0;i<5;i++){
        cout<<emord[i]<<" : "<<reverseWord(emord[i])<<endl;
    }
}

