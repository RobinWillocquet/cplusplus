#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "morse.h"
#include "audiolib.h"
#include "AudioFile.h"

void execmorse() {
    std::cout << "Bienvenue dans le programme de conversion Morse-Français !" << std::endl << "Que souhaitez vous faire ?" << std::endl;
    std::cout << "  1) Traduire un message du français vers le morse" << std::endl;
    std::cout << "  2) Traduire un message du morse vers le français" << std::endl;
    std::cout << "  3) Traduire un fichier texte en français vers un fichier texte en morse" << std::endl;
    std::cout << "  4) Traduire un fichier texte en morse vers un fichier texte en français" << std::endl;
    std::cout << "  5) Traduire un fichier texte en français vers un fichier audio en morse" << std::endl;
    std::cout << "  6) Traduire un fichier audio en morse vers un fichier texte en français" << std::endl;
    int Choix;
    std::cin >> Choix; // On demande son choix à l'utilisateur : 6 pas encore fini
    switch(Choix) {
        case 1 : {
            std::cout << "Entrez votre message en français : ";
            std::string msg1;
            std::cin.ignore();
            std::getline(std::cin,msg1); // On récupère le message
            std::string msg2 = encode_msg(msg1); // On l'encode
            std::cout << "La traduction en morse de '" << msg1 << "' est '" << msg2 << "' !" <<std::endl;
            break;
        }
        default :
            std::cout << "Entrez un nombre valide !" << std::endl;
            break;
        case 2 : {
            std::cout << "Entrez votre message en morse : ";
            std::string msg1;
            std::cin.ignore();
            std::getline(std::cin,msg1);
            std::string msg2 = decode_msg(msg1); // Ou on le décode...
            std::cout << "La traduction en français de '" << msg1 << "' est '" << msg2 << "' !" <<std::endl;
            break;
        }
        case 3 : {
            std::cout << "Spécifiez le chemin du fichier à traduire : ";
            std::string FichierFr;
            std::cin.ignore();
            std::getline(std::cin,FichierFr); // Un fichier que l'on va traduire
            std::ifstream FluxFr(FichierFr);
            std::cout << "Spécifiez le chemin du fichier traduit : ";
            std::string FichierMorse;
            std::getline(std::cin,FichierMorse); // Et là où on le traduit
            std::ofstream FluxMorse(FichierMorse);
            std::string lignefr;
            while(getline(FluxFr,lignefr)){
                if(lignefr.size() == 0){
                    std::string lignemorse;
                    FluxMorse << lignemorse << std::endl; // S'il n'y a rien à mettre...
                }
                else {
                    std::string S;
                    S += toupper(lignefr.at(lignefr.size()-1));
                    if(mapmorse.find(S) == mapmorse.end()){
                        lignefr.erase(lignefr.size()-1);                    
                    }
                    std::string lignemorse;
                    if(lignefr != ""){
                        lignemorse = encode_msg(lignefr); // On encode la ligne
                    }   
                    // std::cout << "'" << lignemorse << "' traduit '" << lignefr << "'" << std::endl;
                    FluxMorse << lignemorse << std::endl; // On l'ajoute au fichier
                }
            }
            std::cout << "Votre fichier '" << FichierFr <<"' est traduit en morse dans '" << FichierMorse << "'." << std::endl;
            break;
        }
        case 4 : { // Structure quasi identique au précédent
            std::cout << "Spécifiez le chemin du fichier à traduire : ";
            std::string FichierMorse2;
            std::cin.ignore();
            std::getline(std::cin,FichierMorse2);
            std::ifstream FluxMorse2(FichierMorse2);
            std::cout << "Spécifiez le chemin du fichier traduit : ";
            std::string FichierFr2;
            std::getline(std::cin,FichierFr2);
            std::ofstream FluxFr2(FichierFr2);
            std::string lignemorse2;
            while(getline(FluxMorse2,lignemorse2)){
                if(lignemorse2.size() == 0){
                    std::string lignefr2;
                    FluxFr2 << lignefr2 << std::endl;
                }
                else {
                    std::string s;
                    s += toupper(lignemorse2.at(lignemorse2.size()-1));
                    std::string letter = "";
                    for(std::map<std::string,std::string>::iterator it = mapmorse.begin();it != mapmorse.end();it++){
                        if(it->second == s){
                            letter = it->first;
                        }   
                    }
                    if(letter == ""){
                        lignemorse2.erase(lignemorse2.size()-1);                     
                    }
                    std::string lignefr2;
                    if(lignemorse2 != ""){
                        lignefr2 = decode_msg(lignemorse2);
                    }
                    // std::cout << "'" << lignefr2 << "' traduit '" << lignemorse2 << "'" << std::endl;
                    FluxFr2 << lignefr2 << std::endl;
                }
            }
            std::cout << "Votre fichier '" << FichierMorse2 <<"' est traduit en français dans '" << FichierFr2 << "'." << std::endl;
            break;
        }
        case 5 : {
            std::cout << "Spécifiez le chemin du fichier à traduire : ";
            std::string FichierFr;
            std::cin.ignore();
            std::getline(std::cin,FichierFr);
            std::ifstream FluxFr(FichierFr);
            std::cout << "Spécifiez le chemin du fichier texte temporaire : ";
            std::string FichierMorse;
            std::getline(std::cin,FichierMorse);
            std::ofstream FluxMorse(FichierMorse);
            std::cout << "Spécifiez le chemin du fichier audio traduit : ";
            std::string AudioMorse;
            std::getline(std::cin,AudioMorse);
            std::cout << "Donnez une durée caractéristique (par défaut : 0.2s) : "; // Durée d'un bip réglementaire
            float duree;
            std::cin >> duree;
            std::vector<float>* samples = new std::vector<float>;
            int* top = new int;
            *top = 0;
            std::string lignefr;
            while(getline(FluxFr,lignefr)){
                if(lignefr.size() == 0){
                    std::string lignemorse;
                    FluxMorse << lignemorse << std::endl;
                    lineTextToAudio(" / -..-. / ",samples,top,duree); // On ajoute une séparation de ligne (/)
                }
                else {
                    std::string S;
                    S += toupper(lignefr.at(lignefr.size()-1));
                    if(mapmorse.find(S) == mapmorse.end()){
                        lignefr.erase(lignefr.size()-1);                    
                    }
                    std::string lignemorse;
                    if(lignefr != ""){
                        lignemorse = encode_msg(lignefr);
                        
                    }   
                    // std::cout << "'" << lignemorse << "' traduit '" << lignefr << "'" << std::endl;
                    FluxMorse << lignemorse << std::endl;
                    lineTextToAudio(lignemorse,samples,top,duree);
                    lineTextToAudio(" / ",samples,top,duree); // On ajoute la ligne aux samples audios, et on sépare la ligne des autres
                }
            }
            writeAudioFile(samples,top,AudioMorse); // On écrit le fichier demandé
            delete samples;
            delete top;
            // int a;
            // a = remove(FichierMorse);
            std::cout << "Votre fichier '" << FichierFr <<"' est traduit en audio morse dans '" << AudioMorse << "'." << std::endl;
            break;
        }
    }
} 

int main() {
    execmorse();
    return 0;
}