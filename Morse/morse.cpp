#include <iostream>
#include <string>
#include <map>
#include "morse.h"

std::string encode_lettre(std::string s){
    std::string S;
    S += toupper(s.at(0));
    try{
        if(mapmorse.find(S) == mapmorse.end()){
            throw "ERREUR : cette lettre n'est pas codée !";
        }
        return mapmorse[S];
    }
    catch(const char* chaine){
        std::cerr << chaine;
    }
    return "";
}

std::string encode_mot(std::string mot){
    std::string motcode;
    for(int i = 0;i<mot.size()-1;i++) {
        std::string letter;
        letter += mot.at(i);
        motcode += encode_lettre(letter);
        motcode += " ";
    }
    std::string lastletter;
    lastletter += mot.at(mot.size()-1);
    motcode += encode_lettre(lastletter);
    return motcode;
}

std::string encode_msg(std::string msg){
    int deb = 0;
    std::string msgcode;
    if(msg.at(0) == ' '){
        msg.erase(msg.begin());
    }
    if(msg.at(msg.size()-1) != ' '){
        msg.push_back(' ');
    }
    for(int i = 0;i<msg.size();){
       if(msg.at(i) ==  ' '){
            std::string mot;
            for(int j = deb;j<i;j++){
                mot += msg.at(j);
            }
            msgcode += encode_mot(mot);
            msgcode += " / ";
            i++;
            deb = i;
        }
        else{
            i++;
        }
    }
    msgcode.erase(msgcode.size()-3);
    return msgcode;
}

std::string decode_lettre(std::string s){
    std::string letter = "";
    for(std::map<std::string,std::string>::iterator it = mapmorse.begin();it != mapmorse.end();it++){
        if(it->second == s){
            letter = it->first;
        }
    }
    try{
        if(letter == ""){
            throw "ERREUR : ce code ne correspond à aucune lettre !";
        }
        return letter;
    }
    catch(const char* chaine){
        std::cerr << chaine << ' ' << s;
    }
    return letter;
}

std::string decode_mot(std::string motcode){
    int deb = 0;
    std::string mot;
    if(motcode.at(0) == ' '){
        motcode.erase(motcode.begin());
    }
    if(motcode.at(motcode.size()-1) != ' '){
        motcode.push_back(' ');
    }
    for(int i = 0;i<motcode.size();){
        if(motcode.at(i) ==  ' '){
            std::string letter;
            for(int j = deb;j<i;j++){
                letter += motcode.at(j);
            }
            mot += decode_lettre(letter);
            i++;
            deb = i;
        }
        else{
            i++;
        }
    }
    return mot;
}

std::string decode_msg(std::string msgcode){
    int deb = 0;
    std::string msg;
    if(msgcode.at(0) == '/'){
        msgcode.erase(msgcode.begin());
    }
    if(msgcode.at(msgcode.size()-1) != ' '){
        msgcode.push_back('/');
    }
    for(int i = 0;i<msgcode.size();){
        if(msgcode.at(i) ==  '/'){
            std::string motcode;
            for(int j = deb;j<i;j++){
                motcode += msgcode.at(j);
            }
            msg += decode_mot(motcode);
            msg += " ";
            i++;
            deb = i;
        }
        else{
            i++;
        }
    }
    msg.erase(msg.size()-1); // Pour enlever le ' ' à la fin !
    return msg;   
}

bool pareil(std::string a, std::string b){
    if(a.size()!=b.size()){
        return false;
    }
    bool same = true;
    for(int i = 0;i<a.size();i++){
        if(a.at(i) != b.at(i)){
            same = false;
        }
    }
    return same;
}
