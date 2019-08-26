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
bool binarySearch(string word,int min, int max);

string reverseWord(string nStr);

void addEmord(string word);
bool checkEmord(string word);

void displayEmords();

//global var's
string dictionary[400000];
string emord[200000];
int ctr = 0;
int emordCtr = 0;


int main(int argc, char *argv[]) {

    auto startTime = std::chrono::system_clock::now();
    try {
        read(argv[1]);
    } catch (string err) {
        cerr << err << endl;
    }
    cout<<"Number of words in dictionary: "<<ctr<<endl;

    prepBinarySearch();

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



void prepBinarySearch(){
    for(int i=0;i<ctr;i++){
        if(checkEmord(dictionary[i])){
            continue;
        }

        if(binarySearch(reverseWord(dictionary[i]),0,ctr-1)){
            addEmord(dictionary[i]);
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
    }else if(min >= max){
        return false;
    }else if(word < dictionary[mid]){
        return binarySearch(word,min,mid-1);
    }else if(word > dictionary[mid]){
        return binarySearch(word,mid+1,max);
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

/**
 * the same word will never be tested twice to we check the
 * reversed version to see if its emord is contained in the array
 * @param word
 * @return
 */
bool checkEmord(string word) {
    word = reverseWord(word);
    for(int i=0;i<emordCtr;i++){
        if(word==emord[i]){
            return true;
        }
    }
    return false;
}

void displayEmords() {
    cout<<"First 10 emordnilap words:"<<endl;
    for(int i=0;i<10;i++){
        cout<<emord[i]<<" : "<<reverseWord(emord[i])<<endl;
    }

    int max=0;
    int loc;
    for(int i = 0;i<emordCtr;i++){
        if(emord[i].length() >max){
            max = emord[i].length();
            loc = i;
        }
    }
    cout<<"largest emord: "<<emord[loc]<<endl;
}

