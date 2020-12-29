#ifndef MORSE_H
#define MORSE_H

#include <iostream>
#include <map>
#include <string>

extern std::map<std::string,std::string> mapmorse;

std::string encode_lettre(std::string s);
std::string encode_mot(std::string s);
std::string encode_msg(std::string s);
std::string decode_lettre(std::string s);
std::string decode_mot(std::string s);
std::string decode_msg(std::string s);
bool pareil(std::string a, std::string b);

#endif