#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "AudioFile.h"

 //=======================================================================

//=======================================================================

//=======================================================================    
// vr: exemple de passage par référence et pas de new
void ajouteBip(std::vector<float>* samples, int* top, float duree, float frequency){   
    //---------------------------------------------------------------
    // Create some variables to help us generate a sine wave   
    const float sampleRate = 44100.f;
    const float frequencyInHz = frequency;
    int dureesamples = floor(duree*sampleRate);
    int end = *top+dureesamples;
    for (int i = 0 ; i < dureesamples ; i++){
        samples -> push_back (0.1f*sin ((static_cast<float> (i) / sampleRate) * frequencyInHz * 2.f * M_PI)); // On crée un bip de la durée (dureesamples)
    }
    *top = end;
}

// vr: référence
void ajouteSilence(std::vector<float>* samples, int* top, float duree, float frequency){
    //---------------------------------------------------------------
    // Create some variables to help us generate a sine wave       
    const float sampleRate = 44100.f;
    const float frequencyInHz = frequency; // On peut choisir la fréquence du sinus pour une note choisie
    int dureesamples = floor(duree*sampleRate);
    int end = *top+dureesamples;
    for (int i = 0 ; i < dureesamples ; i++){
        samples -> push_back (0.0f*sin ((static_cast<float> (i) / sampleRate) * frequencyInHz * 2.f * M_PI)); // On crée un silence de la duree (dureesamples)
    }
    *top = end;
}


void writeAudioFile(std::vector<float>* samples, int* top,std::string filePath) { // Provient en partie de la fonction pour créer un .wav sinus de Adam Stark
    AudioFile<float> a;
    a.setNumChannels (2);
    a.setNumSamplesPerChannel (*top);
    for (int i = 0; i < a.getNumSamplesPerChannel(); i++)
    {
        for (int channel = 0; channel < a.getNumChannels(); channel++)
        {
            a.samples[channel][i] = samples -> at(i); // On ecrit le fichier avec le tableau des samples
        }
    }
    a.save (filePath, AudioFileFormat::Wave); // On sauvegarde le fichier
}

void lineTextToAudio(std::string morseline,std::vector<float>* samples, int* top, float duree, float frequency){
    for(unsigned int i = 0; i < morseline.size();i++){ // On est sûrs de ne pas avoir de warning de comparaison, puisque i est unsigned.
        char carac = morseline.at(i); // Selon le caractère, on met un bip ou un silence différent !
        switch(carac){
            case '.': { 
                ajouteBip(samples,top,duree,frequency);
                ajouteSilence(samples,top,duree,frequency);
                break;
            }
            case '-': {
                ajouteBip(samples,top,3*duree,frequency);
                ajouteSilence(samples,top,duree,frequency);
                break;
            }
            case ' ': {
                ajouteSilence(samples,top,2*duree,frequency); // Deja 0.2s après le dernier caractère, il suffit donc de rajouter 0.4s
                break;
            }
            case '/': {
                ajouteSilence(samples,top,2*duree,frequency); // Pour un total de 1.4s i.e. 7 temps.
                break;
            }
            default: {
                break;
            }
        } 
    }
}

int decodeSilence(std::vector<float>* samples,
		  float duree,
		  unsigned int* top,
		  std::string& morseline) { // vr: on passe par référence un objet de la pile
    int rate = 44100; // Le nombre de samples par seconde
    int unit = floor(rate*duree); // Le nombre de samples par unité
    unsigned int unit_bas = floor(unit*0.9f);        
    unsigned int unit_haut = floor(unit*1.1f); // Pour créer une marge d'acceptation
    // vr: tu n'as pas besoin de mettre end en mémoire dynamique, tu ne passes à des fonctions appelées par cette fonction donc un end dans la pile fera l'affaire et tu le passes par adresse (ça évite de manipuler le tas qui est plus cher que la pile)
    
    // vr:    unsigned int* end = new unsigned int;
    unsigned int value = 0;
    unsigned int* end = &value;
    float valsuite = samples -> at(*top+1); // On regarde si c'est aussi un non nul, pour déceler une portion de sinus
    if(valsuite != 0) {
        *top += 1;
        return *top; // On passe à la suite
    }
    if(valsuite == 0) {
        *end = *top+1;
        while(samples-> at(*end+1) == 0 && *end < samples -> size()-3) {
            *end = *end+1; // On regarde la taille de la portion nulle
        }
        unsigned int taille = *end-*top;
        // std::cout << "Le silence est de taille : " << taille << std::endl;
        if(unit_bas <= taille && taille <= unit_haut) {
            morseline += "";
            *top = *end;
	    // vr: delete end;
            return *top; // Un espace entre deux caractères morse
        }
        if(3*unit_bas <= taille && taille <= 3*unit_haut) {
            morseline += " ";
            *top = *end;
	    // vr: delete end;
            return *top; // Un espace entre deux lettres morse
        }
        if(7*unit_bas <= taille && taille <= 7*unit_haut) {
            morseline += " / ";
            *top = *end;
            return *top; // Un espace entre deux mots morse
        }
        if(taille > 7*unit_haut) {
             morseline += " / -..-. / ";
            *top = *end;
            // vr: delete end;
            return *top; // Un saut à la ligne (ici un /)
        }
        else {
            morseline += "";
            *top = *end;
            // vr: delete end;
            return *top; // Le cas où rien ne se passe
        }
    }
    return *top;
}

int decodeBip(std::vector<float>* samples, float duree, unsigned int* top, std::string& morseline) {
    int rate = 44100;
    int unit = floor(rate*duree);
    float unit_bas = floor(unit*0.9f);        
    float unit_haut = floor(unit*1.1f);

    // vr: idem ne mets rien en mémoire dynamique (tas)
    // vr:    unsigned int* end = new unsigned int;
    unsigned int value = 0;
    unsigned int* end = &value;
    float valsuite = samples -> at(*top+1);
    if(valsuite == 0) {
        *top += 1;
        return *top; // On passe à la suite
    }
    if(valsuite != 0) {
        *end = *top+1;
        while((samples-> at(*end+1) != 0 || (samples -> at(*end+1) == 0 && samples -> at(*end+2) != 0)) && *end < samples -> size() - 3) {
            *end = *end+1; // On regarde la taille de la portion non nulle
        }
        unsigned int taille = *end-*top;
        // std::cout << taille << std::endl;
        if(unit_bas <= taille && taille <= unit_haut) {
            morseline += ".";
            *top = *end; // Une unité simple morse
	    // vr: delete end;
            return *top;
        }
        if(3*unit_bas <= taille && taille <= 3*unit_haut) {
            morseline += "-";
            *top = *end; // Une unité longue morse
            // vr: delete end;
            return *top;
        }
        else {
            morseline += "";
            *top = *end;
            // vr: delete end;
            return *top; 
        }
    }
    return *top;
}

std::string AudioToText(std::vector<float>* samples, float duree) {
  // vr: idem ne mets pas morseline dans le tas laisse la dans la pile
  // vr:     std::string* morseline = new std::string;
  std::string morseline;
    if(samples -> size() == 0){
        morseline = ""; // Pas de samples, pas de string
    }
    else {
        unsigned int* top = new unsigned int;
        for(unsigned int i = 0;i < samples -> size() - 3;){ // On parcourt les samples
            *top = i;
            float val = samples -> at(i);
            if(val == 0) {
                i = decodeSilence(samples,duree,top,morseline); // On regarde si c'est bien un silence et on le décode
                // std::cout << morseline << ", " << i << std::endl;    
            }
            if(val != 0) {
                i = decodeBip(samples,duree,top,morseline); // Idem avec un bip
                // std::cout << morseline << ", " << i << std::endl;
            }
        }
        // vr: delete top;
    }
    return morseline; // La ligne décodée est renvoyée
    // vr: un delete après un return n'est jamais atteint
    // vr: delete morseline;
}
