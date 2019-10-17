#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

static const char* const HEX_VALUES = "0123456789ABCDEF";

string string_to_hex(const string& word)
{
    size_t len = word.length();

    string hex_word;
    hex_word.reserve(4 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = word[i];
        hex_word.push_back('\\');
        hex_word.push_back('x');
        hex_word.push_back(HEX_VALUES[c >> 4]);
        hex_word.push_back(HEX_VALUES[c & 15]);
    }
    return hex_word;
}

string hex_to_string(const string& full_hex_word)
{
    // First, remove the "\x" added for each character in the string_to_hex method
    size_t len = full_hex_word.length();
    string hex_word = "";
    for(size_t i = 0; i < len - 1; ++i) {
        if(full_hex_word[i] != '\\' && full_hex_word[i] != 'x') {
            hex_word += full_hex_word[i];
        }
    }

    cout << "New string: " << hex_word << endl;

    if (len & 1) throw invalid_argument("odd length");

    string word;
    word.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = hex_word[i];
        const char* p = lower_bound(HEX_VALUES, HEX_VALUES + 16, a);
        if (*p != a) throw invalid_argument("not a hex digit");

        char b = hex_word[i + 1];
        const char* q = lower_bound(HEX_VALUES, HEX_VALUES + 16, b);
        if (*q != b) throw invalid_argument("not a hex digit");

        word.push_back(((p - HEX_VALUES) << 4) | (q - HEX_VALUES));
    }
    return word;
}