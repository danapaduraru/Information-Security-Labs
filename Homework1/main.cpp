#include <iostream>
#include <vector>

#include "FirstEncryption.hpp"

using namespace std;

int main() {
    // Create a first encryption with a random key from the dictionary
    cout << endl << "========== Encryption using a Random Key Algorithm ==========" << "\n\n";
    string to_encrypt_file = "to_encrypt.txt";
    string encryption_mode = "cfb";
    encryptText(to_encrypt_file, encryption_mode);

    // Get the original text
    unsigned char original_message[100];
    getFullText("to_encrypt.txt", original_message);
    deleteExtraSpaces(original_message);

    // Get the encrypted text
    unsigned char original_encrypted_message[100];
    getFullText("encrypted_message.txt", original_encrypted_message);
    deleteExtraSpaces(original_encrypted_message);
    //string original_encrypted_message(reinterpret_cast<char*>(original_encrypted_message_char));

    cout << endl << "========== Find Encryption Key Algorithm ==========" << "\n\n";
    cout << "Original Encrypted Message: " << original_encrypted_message << endl;

    // We will try encrypting the same file with all the keys
    // We will stop when we find an encryption that matches the original encrypted text.
    // Along with the key, we will print the original word that generated the key
    // and the number of encryptions until we found the key

    // Get all the words in the dictionary
    cout << "Looking for the key..." << endl;

    bool found_key = false;
    unsigned char encryption_key[130], possible_message[100];
    vector<string> dictionary = getWordsFromFile(DICTIONARY_FILE);
    int index = 0;

    while (!found_key && index < dictionary.size()) {
        // Generate a key for the word with the current index
        generateKey(dictionary[index], encryption_key);
        if(index % 10000 == 0) {
            cout << "Reached word #" << index << endl;
        }
        // Try decrypting the message         
        int possible_message_len = decrypt(original_encrypted_message, strlen((char *)original_encrypted_message), encryption_key, INITIALIZATION_VECTOR, possible_message, encryption_mode);
        if(possible_message_len != 0) {
            possible_message[possible_message_len] = '\0';
            deleteExtraSpaces(possible_message);
            // Check if decrypted message is equal to the original tmessageext
            if(strcmp((char*)possible_message, (char*)original_message) == 0) {
                found_key = true;
                cout << endl << "Found the key!" << endl;
                cout << "Decrypted message: " << possible_message << endl;
                cout << "The used key is: " << encryption_key << endl;
                cout << "The key was formed using the word: " << dictionary[index] << endl;
                cout << "Number of tries: " << index << endl;
            }
        }
        index ++;
    }
    return 0;
}
