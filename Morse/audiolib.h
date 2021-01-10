#ifndef AUDIOLIB_H
#define AUDIOLIB_H

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "AudioFile.h"

void ajouteBip(std::vector<float>* samples, int* top, float duree);
void ajouteSilence(std::vector<float>* samples, int* top, float duree);
void writeAudioFile(std::vector<float>* samples, int* top,std::string filePath);
void lineTextToAudio(std::string morseline,std::vector<float>* samples, int* top);

#endif