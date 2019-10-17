#include <fstream>
#include <iostream>
#include <vector>
#include "string.h"

// Functie care citeste toate randurile dintr-un fisier text (pentru a citi posibilele chei din fisierul dictionar.txt) si returneaza un vector cu toate cuvintele
// Function that reads all lines from a text file (in order to get all possible words for keys in the file dictionary.txt) and returns an array of strings
vector<string> getWordsFromFile(string text_file_name) {
    vector<string> words;
    string word = "";
    ifstream f;
    f.open(text_file_name);
    while (getline(f, word)) {
        words.push_back(word);
    }
    f.close();
    return words;
}

char* getFullText(string text_file_name, unsigned char full_text[100]) {
    vector<string> words = getWordsFromFile(text_file_name);
    for(string word : words) {
        const unsigned char* unsigned_word = reinterpret_cast<const unsigned char *>(word.c_str());
        strcat((char*)full_text, (char*)unsigned_word);
        strcat((char*)full_text, " ");
    }
}

void writeToFile(unsigned char text[100], string file_name) {
    ofstream o (file_name);
    o << text;
    o.close();
}