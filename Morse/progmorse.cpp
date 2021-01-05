#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "morse.h"

void execmorse() {
    std::cout << "Bienvenue dans le programme de conversion Morse-Français !" << std::endl << "Que souhaitez vous faire ?" << std::endl;
    std::cout << "  1) Traduire un message du français vers le morse" << std::endl;
    std::cout << "  2) Traduire un message du morse vers le français" << std::endl;
    std::cout << "  3) Traduire un fichier texte en français vers un fichier texte en morse" << std::endl;
    std::cout << "  4) Traduire un fichier texte en morse vers un fichier texte en français" << std::endl;
    int Choix;
    std::cin >> Choix;
    switch(Choix) {
        case 1 : {
            std::cout << "Entrez votre message en français : ";
            std::string msg1;
            std::cin.ignore();
            std::getline(std::cin,msg1);
            std::string msg2 = encode_msg(msg1);
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
            std::string msg2 = decode_msg(msg1);
            std::cout << "La traduction en français de '" << msg1 << "' est '" << msg2 << "' !" <<std::endl;
            break;
        }
        case 3 : {
            std::cout << "Spécifiez le chemin du fichier à traduire : ";
            std::string FichierFr;
            std::cin.ignore();
            std::getline(std::cin,FichierFr);
            std::ifstream FluxFr(FichierFr);
            std::cout << "Spécifiez le chemin du fichier traduit : ";
            std::string FichierMorse;
            std::getline(std::cin,FichierMorse);            
            std::string bruit;
            bruit += FichierMorse.at(0);
            std::cout << bruit << std::endl;
            std::ofstream FluxMorse(FichierMorse);
            std::string lignefr;
            while(getline(FluxFr,lignefr)){
                std::string S;
                S += toupper(lignefr.at(lignefr.size()-1));
                if(mapmorse.find(S) == mapmorse.end()){
                    lignefr.erase(lignefr.size()-1);                    
                }
                std::string lignemorse = encode_msg(lignefr);
                // std::cout << "'" << lignemorse << "' traduit '" << lignefr << "'" << std::endl;
                FluxMorse << lignemorse << std::endl;
            }
            std::cout << "Votre fichier '" << FichierFr <<"' est traduit en morse dans '" << FichierMorse << "'." << std::endl;
            break;
        }
        case 4 : {
            std::cout << "Spécifiez le chemin du fichier à traduire : ";
            std::string FichierMorse2;
            std::cin.ignore();
            std::getline(std::cin,FichierMorse2);
            std::ifstream FluxMorse2(FichierMorse2);
            std::cout << "Spécifiez le chemin du fichier traduit : ";
            std::string FichierFr2;
            std::getline(std::cin,FichierFr2);            
            std::string bruit2;
            bruit2 += FichierFr2.at(0);
            std::cout << bruit2 << std::endl;
            std::ofstream FluxFr2(FichierFr2);
            std::string lignemorse2;
            while(getline(FluxMorse2,lignemorse2)){
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
                std::string lignefr2 = decode_msg(lignemorse2);
                // std::cout << "'" << lignefr2 << "' traduit '" << lignemorse2 << "'" << std::endl;
                FluxFr2 << lignefr2 << std::endl;
            }
            std::cout << "Votre fichier '" << FichierMorse2 <<"' est traduit en français dans '" << FichierFr2 << "'." << std::endl;
            break;
        }
    }
} 

int main() {
    execmorse();
    return 0;
}