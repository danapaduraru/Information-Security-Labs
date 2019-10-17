#include <iostream>
#include <vector>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "HexConverter.hpp"
#include "Utils.hpp"
#include "UtilsIO.hpp"
#include "EncryptionDecryptionFunctions.hpp"

using namespace std;


const string DICTIONARY_FILE = "dict.txt";
unsigned char INITIALIZATION_VECTOR[100];

// Functie care primeste ca parametru un cuvant si genereaza scrierea in hexa a acelui cuvant.
// Daca cuvantul este mai scurt de 16 caractere, caracterele ramase vor fi inlocuite cu caracterul spatiu scris in hexa "\x20"
void generateKey(string word, unsigned char key[130]) {
    // Generate the key starting from this word
    int len = word.length();
    while(len < 16) { 
        word.append(" ");
        len ++;
    }
    string key_string = string_to_hex(word);
    strcpy((char*)key, key_string.c_str());
}

// Functie care alege random un cuvant din dictionar, folosita pentru prima encriptare cand nu stim ce cheie este utilizata.
string getRandomWordFromDictionary() {
    // Get all possible words from the dictionary
    vector<string> words_from_file = getWordsFromFile(DICTIONARY_FILE);
    // Choose a random word
    int max_index = words_from_file.size();
    return words_from_file[random(0, max_index)];
}

// Function that receives a text file's name for encryption, encrypts the text that it contains and returns a cryptotext that will be written in another file.
void encryptText(string file_name, string encryption_mode) {
    strcpy((char*)INITIALIZATION_VECTOR, "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f");
    unsigned char cipher_text[100], plain_text[100], full_text[100], encryption_key[130];

    // get text to encrypt from text file
    getFullText(file_name, full_text);
    cout << "Original message: " << full_text << endl;

    // get encryption key
    generateKey(getRandomWordFromDictionary(), encryption_key);
    cout << "Encryption key: " << encryption_key << endl;

    cout << "Encryption mode: " << encryption_mode << endl;

    // encrypt text
    int ciphertext_len = encrypt(full_text, strlen((char *)full_text), encryption_key, INITIALIZATION_VECTOR, cipher_text, encryption_mode);
    cout << "Cipher Text: " << cipher_text << 'L' << endl;

    writeToFile(cipher_text, "encrypted_message.txt");
}   
