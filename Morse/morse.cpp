#include <iostream>
#include <string>
#include <map>

std::map<std::string,std::string> mapmorse = { // La map avec nos caracs en français et morse
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
    {"'", ".----."},
    {".", ".-.-.-"},
    {",", "--..--"},
    {"?", "..--.."},
    {"!", "-.-.--"},
    {"/", "-..-."},
    {"(", "-.--."},
    {")", "-.--.-"},
    {"&", ".-..."},
    {":", "---..."},
    {";", "-.-.-."},
    {"=", "-...-"},
    {"+", ".-.-."},
    {"-", "-....-"},
    {"_", "..--.-"},
    {"$", "...-..-"},
    {"@", ".--.-."},
    {"É", "..-.."}
};

std::string encode_lettre(std::string s){
    std::string S;
    S += toupper(s.at(0));
    // vr: un peu compliqué tu lances une exception que tu rattrapes tout de suite ! soit tu lances une exception à la fonction appelante qui t'a passé un string s malformée soit tu affiches un message d'erreur et tu retournes "" mais ne fais pas les deux
    /*
    try{
        if(mapmorse.find(S) == mapmorse.end()){
            throw "ERREUR : cette lettre n'est pas codée !"; // Il faut le notifier
        }
        return mapmorse[S]; // simple décodage par map ici
    }
    catch(const char* chaine){
        std::cerr << chaine;
    }
    return "";
    */
    
    if(mapmorse.find(S) == mapmorse.end()){
      throw "ERREUR : cette lettre n'est pas codée !"; // vr: j'arrête la traduction
    }
    return mapmorse[S]; // simple décodage par map ici
}



std::string encode_mot(std::string mot){
    std::string motcode;
    for(unsigned int i = 0;i<mot.size()-1;i++) {
        std::string letter;
        letter += mot.at(i);
        motcode += encode_lettre(letter); // On encode chaque lettre du mot
        motcode += " ";
    }
    std::string lastletter;
    lastletter += mot.at(mot.size()-1);
    motcode += encode_lettre(lastletter); // On encode la dernière lettre, sans espace ajouté
    return motcode;
}

std::string encode_msg(std::string msg){
    int deb = 0;
    std::string msgcode;
    if(msg.at(0) == ' '){
        msg.erase(msg.begin()); // Pour plus d'aisance
    }
    if(msg.at(msg.size()-1) != ' '){
        msg.push_back(' '); // Idem
    }
    for(unsigned int i = 0;i<msg.size();){
       if(msg.at(i) ==  ' '){
            std::string mot;
            for(unsigned int j = deb;j<i;j++){
                mot += msg.at(j); // On crée le mot avant l'espace
            }
            msgcode += encode_mot(mot); // On rajoute le mot encodé au message
            msgcode += " / "; // On sépare le mot des autres 
            i++;
            deb = i;
        }
        else{
            i++;
        }
    }
    msgcode.erase(msgcode.size()-3); // Pour ne pas avoir le retour à la ligne
    return msgcode;
}

std::string decode_lettre(std::string s){
    std::string letter = "";
    for(std::map<std::string,std::string>::iterator it = mapmorse.begin();it != mapmorse.end();it++){
        if(it->second == s){
            letter = it->first;
        }
    }

    // vr: pareil soit tu affiches un message soit tu lances une exception afficher un message en lancant une exception n'a pas de sens !
    /*
   try{
        if(letter == ""){
            throw "ERREUR : ce code ne correspond à aucune lettre !";
        }
        return letter; // On vérifie que ce code correspond bien à une lettre
    }
    catch(const char* chaine){
        std::cerr << chaine << ' ' << s;
    }
    return letter; // Décodage simple
    */
    if(letter == ""){
      throw "ERREUR : ce code ne correspond à aucune lettre !";
    }
    return letter; // On vérifie que ce code correspond bien à une lettre
}

std::string decode_mot(std::string motcode){
    int deb = 0;
    std::string mot;
    if(motcode.size() == 0){
        mot = "";
        return mot;
    }
    else {
        if(motcode.at(0) == ' '){
            motcode.erase(motcode.begin());
        }
        if(motcode.at(motcode.size()-1) != ' '){
            motcode.push_back(' '); // Ainsi l'entièreté du message est décodée
        }
        for(unsigned int i = 0;i<motcode.size();){
            if(motcode.at(i) ==  ' '){
                std::string letter;
                for(unsigned int j = deb;j<i;j++){
                    letter += motcode.at(j); 
                }
                mot += decode_lettre(letter); // On décode chaque lettre du mot
                i++;
                deb = i;
            }
            else{
                i++;
            }
        }
        return mot;
    }
    return mot;
}

// vr: à chaque fois que tu appelles cette fonction tu copies son argument, est-ce utile ?
std::string decode_msg(std::string msgcode){
    int deb = 0;
    std::string msg;
    if(msgcode.at(0) == '/'){
        msgcode.erase(msgcode.begin());
    }
    if(msgcode.at(msgcode.size()-1) != ' '){
        msgcode.push_back('/'); // Pour bien repérer le dernier mot
    }
    for(unsigned int i = 0;i<msgcode.size();){
        if(msgcode.at(i) ==  '/'){
            std::string motcode;
            for(unsigned int j = deb;j<i;j++){
                motcode += msgcode.at(j); // On écrit le mot morse...
            }
            msg += decode_mot(motcode); // Et on le décode !
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
    for(unsigned int i = 0;i<a.size();i++){
        if(a.at(i) != b.at(i)){
            same = false; // Si un seul caractère diffère...
        }
    }
    return same;
}
