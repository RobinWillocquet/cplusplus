#ifndef AUDIOLIB_H
#define AUDIOLIB_H

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "AudioFile.h"

// vr: référence
void ajouteBip(std::vector<float>* samples, int* top, float duree, float frequency); // Pour ajouter un bip dans un .wav
// vr: référence
void ajouteSilence(std::vector<float>* samples, int* top, float duree, float frequency); // Pour ajouter cette fois un silence
void writeAudioFile(std::vector<float>* samples, int* top,std::string filePath); // Ecrit le fichier .wav à partir des samples
void lineTextToAudio(std::string morseline,std::vector<float>* samples, int* top, float duree, float frequency); // Convertit une ligne de texte morse en samples;
std::string AudioToText(std::vector<float>* samples, float duree); // Convertit un fichier .wav en texte morse
int decodeBip(std::vector<float>* samples, float duree, unsigned int* top, std::string* morseline); // Detecte un silence dans l'audio et le convertit
int decodeSilence(std::vector<float>* samples, float duree, unsigned int* top, std::string* morseline); // Detecte un bip dans l'audio et le convertit

#endif
