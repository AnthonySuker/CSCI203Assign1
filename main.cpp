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

void binarySearch();

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

void binarySearch(){


}

//normal string and reverse string
string reverseWord(string nStr) {
    string rStr;
    rStr.assign(nStr.rbegin(), nStr.rend());
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

