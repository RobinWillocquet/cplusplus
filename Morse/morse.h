#ifndef MORSE_H
#define MORSE_H

#include <iostream>
#include <map>
#include <string>

std::map<std::string,std::string> mapmorse = {
    {"A", ".-"},
    {"B", "-..."},
    {"C", "-.-."},
    {"D", "-.."},
    {"E", "."},
    {"F", "..-."},
    {"G", "--."},
    {"H", "...."},
    {"I", ".."},
    {"J", ".---"},
    {"K", "-.-"},
    {"L", ".-.."},
    {"M", "--"},
    {"N", "-."},
    {"O", "---"},
    {"P", ".--."},
    {"Q", "--.-"},
    {"R", ".-."},
    {"S", "..."},
    {"T", "-"},
    {"U", "..-"},
    {"V", "...-"},
    {"W", ".--"},
    {"X", "-..-"},
    {"Y", "-.--"},
    {"Z", "--.."},
    {"0", "-----"},
    {"1", ".----"},
    {"2", "..---"},
    {"3", "...--"},
    {"4", "....-"},
    {"5", "....."},
    {"6", "-...."},
    {"7", "--..."},
    {"8", "---.."},
    {"9", "----."},
    {"'", ".----."}
};

std::string encode_lettre(std::string s);
std::string encode_mot(std::string s);
std::string encode_msg(std::string s);
std::string decode_lettre(std::string s);
std::string decode_mot(std::string s);
std::string decode_msg(std::string s);
bool pareil(std::string a, std::string b);

#endif