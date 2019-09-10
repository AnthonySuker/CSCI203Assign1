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
void readDictionary();
void readSpellCheck();

struct wordComponents {
    char c;
    int x;
};
struct anagramData {
    string word;
    string anagrams[20];
    int ctr = 0;
    wordComponents components[15];
    int uniqueChars = 0;
};


//Searching algorithms
bool linearSearch(string *array, string word, int size);
void prepBinarySearch();
bool binarySearch(string *array, string word, int min, int max);
void swap(string *a, string *b);

//word processing
string reverseWord(string nStr);
string cleanseWord(string str);

//Boiler plate functions
void addEmord(string word);
void displayEmords();
void findDefinedUnique();
void printArray(string arr[], int size);

//part 4 functions
anagramData breakdownWord(string str);
bool componentExists(wordComponents *wc, int max, char c);
void printAnagramData(anagramData data);
int partition(string arr[], int low, int high);
void quickSort(string arr[], int low, int high);
void anagramSearch();
bool compareComponents(anagramData a, anagramData b);
void sortWordComponents(anagramData *d);
void printAnagramStats();

//global var's
string dictionary[400000];
string emord[200000];
string spellCheck[300];
string distinctDefined[300];
anagramData aData[300];

int ctr = 0;
int emordCtr = 0;
int spTotal = 0;    //number of total words from sample.txt
int spCtr = 0;      //number of distinct words from sample.txt
int distinctDefinedCtr = 0;   //Number of not defined unique words from sample.txt


int main(int argc, char *argv[]) {


//    auto startTime = std::chrono::system_clock::now();
//    auto endTime = std::chrono::system_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
//    cout << "Total run time (seconds): " << duration.count() << endl;



    time_t start,end;
    time(&start);

    //part 2
    try {
        readDictionary();
    } catch (string err) {
        cerr << err << endl;
    }
    cout << "Number of words in dictionary: " << ctr << endl;

    prepBinarySearch();
    displayEmords();

    //part 3
    cout << endl << "3. SPELL CHECK" << endl;
    try {
        readSpellCheck();
    } catch (string err) {
        cerr << err << endl;
    }

    findDefinedUnique();
    cout << "Total of words from sample.txt: " << spTotal << endl;
    cout << "Number of distinct words from sample.txt: " << spCtr << endl;
    cout << "Number of not defined unique words from sample.txt : " << distinctDefinedCtr << endl;


    quickSort(distinctDefined, 0, distinctDefinedCtr - 1);
//    printArray(distinctDefined,distinctDefinedCtr);


    anagramSearch();

    for (int i = 0; i < 10; i++) {
        printAnagramData(aData[i]);
    }

    printAnagramStats();

    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken;
    cout << " sec " << endl;

    return 0;
}

//region Read functions

void readDictionary() {
    string filename = "dictionary.txt";
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

void readSpellCheck() {
    string filename = "sample.txt";
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
        line = cleanseWord(line);
        if (line == "") {
            continue;
        }
        if (!linearSearch(spellCheck, line, spCtr)) {
            spellCheck[spCtr] = line;
            spCtr++;
        }

        in >> line;
    }
}




//endregion

//region Searches

bool linearSearch(string *array, string word, int size) {
    if (word.size() == 0) return true;
    //increases the total valid words found only if the string is > 0
    spTotal++;
    for (int x = 0; x < size; x++) {
        if (array[x] == word) return true;
    }
    return false;
}


/**Called as a recursive function to avoid loops
 * returns bool based on if an emord is found
 * terminating condition is when min and max are equal
 *      if its not that exact value an emord wont be found
 * @param word      parsed in reverse so reverse method isnt called repeatedly
 * @param min
 * @param max
 */

bool binarySearch(string *array, string word, int min, int max) {
    int mid = (min + max) / 2;

    if (word == array[mid]) {
        return true;
    } else if (min >= max) {
        return false;
    } else if (word < array[mid]) {
        return binarySearch(array, word, min, mid - 1);
    } else if (word > array[mid]) {
        return binarySearch(array, word, mid + 1, max);
    } else {
        cerr << ">No condition met in binary search" << endl;
    }
}


void prepBinarySearch() {
    for (int i = 0; i < ctr; i++) {
        if (binarySearch(emord, reverseWord(dictionary[i]), 0, emordCtr - 1)) {
            continue;
        }
        if (binarySearch(dictionary, reverseWord(dictionary[i]), 0, ctr - 1)) {
            addEmord(dictionary[i]);
        }
    }
}
//endregion

//region String manipulation

//normal string and reverse string
string reverseWord(string nStr) {
    string rStr = "";
    for (int i = nStr.length() - 1; i >= 0; i--) {
        rStr += nStr.at(i);
    }
    return rStr;
}

string cleanseWord(string str) {
    string returnStr = "";
    int length = str.length();

    for (int i = 0; i < length; i++) {
        if (((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))) {
            returnStr += str[i];
        }
    }

    for (int i = 0; i < returnStr.length(); i++) {
        if (returnStr[i] >= 'A' && returnStr[i] <= 'Z') {
            returnStr[i] += 32;
        }
    }
    return returnStr;
}
//endregion

//region Boiler plate

void addEmord(string word) {
    emord[emordCtr] = word;
    emordCtr++;
}

void displayEmords() {
    cout << "First 10 emordnilap words:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << emord[i] << " : " << reverseWord(emord[i]) << endl;
    }

    int max = 0;
    int loc;
    for (int i = 0; i < emordCtr; i++) {
        if (emord[i].length() > max) {
            max = emord[i].length();
            loc = i;
        }
    }
    cout << "largest emord: " << emord[loc] << endl;
}

void findDefinedUnique() {
    for (int i = 0; i < spCtr; i++) {
        if (binarySearch(dictionary, spellCheck[i], 0, ctr)) {
            distinctDefined[distinctDefinedCtr] = spellCheck[i];
            distinctDefinedCtr++;
        }
    }
}
//endregion


//part 4

//takes and stores all necessary data in a anagramData object and stores it
anagramData breakdownWord(string str) {
    anagramData data;
    data.word = str;
//    cout<<str<<endl;
    for (int i = 0; i < str.length(); i++) {

        if (componentExists(data.components, data.uniqueChars, str[i])) {
            continue;
        } else {
            data.uniqueChars++;
        }
    }
    sortWordComponents(&data);

    return data;
}

bool componentExists(wordComponents *wc, int max, char c) {
    for (int y = 0; y < max; y++) {
        if (wc[y].c == c) {
            wc[y].x++;
            return true;
        }
    }
    wc[max].c = c;
    wc[max].x = 1;
    return false;
}

void printAnagramData(anagramData data) {
    cout << "word: " << data.word << endl;
    cout << "unique chars: " << data.uniqueChars << endl;
    cout << "components: " << endl;
    for (int i = 0; i < data.uniqueChars; i++) {
        cout << data.components[i].c << ": ";
        cout << data.components[i].x << endl;
    }
    cout << "Anagrams:  ";
    for (int i = 0; i < data.ctr; i++) {
        cout << data.anagrams[i] << "  ";
    }
    cout << endl<<endl;
}

void anagramSearch() {
    for (int i = 0; i < distinctDefinedCtr; i++) {
        aData[i] = breakdownWord(distinctDefined[i]);
        for (int x = 0; x < ctr; x++) {
            if (dictionary[x].length() == aData[i].word.length()) {
                if (compareComponents(aData[i], breakdownWord(dictionary[x]))) {
                    aData[i].anagrams[aData[i].ctr] = dictionary[x];
                    aData[i].ctr++;
                }
            }
        }
//        cout<<"search complete"<<endl;
    }

}

void sortWordComponents(anagramData *d) {
    for (int x = 0; x < d->uniqueChars; x++) {
        for (int y = x + 1; y < d->uniqueChars; y++) {
            if (d->components[x].c > d->components[y].c) {
                wordComponents temp = d->components[x];
                d->components[x] = d->components[y];
                d->components[y] = temp;
            }
        }
    }
}


/**
 * since components are sorted we can just work down the array and compare to each other
 * if anything doesnt match we know its not a anagram
 */
bool compareComponents(anagramData a, anagramData b) {
    bool good = false;
    if (a.word == b.word) {
        return false;
    }


    if (a.uniqueChars == b.uniqueChars) {
        for (int x = 0; x < a.uniqueChars; x++) {
           if(a.components[x].c==b.components[x].c){
               if(a.components[x].x!=b.components[x].x){
                   return false;
               }
           }else{
               return false;
           }
        }
    }else{
        return false;
    }
    return true;

}

bool compareChar(char a, char b) {
    if (a == b) {
        return true;
    } else {
        return false;
    }
}


void swap(string *a, string *b) {
    string temp = *a;
    *a = *b;
    *b = temp;
}

int partition(string arr[], int low, int high) {
    string pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(string arr[], int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(string arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void printAnagramStats(){
    int loc=0;
    int val=0;
    int total=0;

    int largest=0;
    int largestLoc=0;

    int most=0;
    int mostLoc=0;

    for(int i=0;i<distinctDefinedCtr;i++){
        total+=aData[i].ctr;
        if(aData[i].ctr==0)continue;

        if(aData[i].word.size()>largest){
            largest = aData[i].word.size();
            largestLoc = i;
        }

        if(aData[i].ctr>val){
            val=aData[i].ctr;
            loc = i;
        }

    }

    cout<<aData[loc].word<<" has the most anagrams"<<endl;
    cout<<total<<" anagrams found"<<endl;
    cout<<aData[largestLoc].word<<" is the largest anagram"<<endl;
    cout<<aData[mostLoc].word<<" Has the most anagrams"<<endl;


}


/**
 * compile with CC -std=c++11 ass1.cpp -o ass1
 *
 * original run time was 8-11 seconds depeding on pc
 * run time with bst goes to 3 seconds
 *
 * with part 4 run time goes up to
 *
 * step 1&2 only use arrays and strings
 *
 * part 4 was optimised to break down a word into its char's and how often each char appears
 * i then used a quick sort to ordered this list to make checking a linear process of making sure
 * [i] from one data structure is equal to [i] in the other
 *
 * emord function works recursively
 * Called as a recursive function to avoid loops
 * returns bool based on if an emord is found
 * terminating condition is when min and max are equal
 * if its not that exact value an emord wont be found
 */
