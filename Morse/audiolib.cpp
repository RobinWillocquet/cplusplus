#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "AudioFile.h"

 //=======================================================================

//=======================================================================

//=======================================================================    
void ajouteBip(std::vector<float>* samples, int* top, float duree){   
    //---------------------------------------------------------------
    // Create some variables to help us generate a sine wave   
    const float sampleRate = 44100.f;
    const float frequencyInHz = 800.f;
    int dureesamples = floor(duree*sampleRate);
    int end = *top+dureesamples;
    for (int i = 0 ; i < dureesamples ; i++){
        samples -> push_back (0.1f*sin ((static_cast<float> (i) / sampleRate) * frequencyInHz * 2.f * M_PI));
    }
    *top = end;
}

void ajouteSilence(std::vector<float>* samples, int* top, float duree){
    //---------------------------------------------------------------
    // Create some variables to help us generate a sine wave       
    const float sampleRate = 44100.f;
    const float frequencyInHz = 800.f;
    int dureesamples = floor(duree*sampleRate);
    int end = *top+dureesamples;
    for (int i = 0 ; i < dureesamples ; i++){
        samples -> push_back (0.0f*sin ((static_cast<float> (i) / sampleRate) * frequencyInHz * 2.f * M_PI));
    }
    *top = end;
}


void writeAudioFile(std::vector<float>* samples, int* top,std::string filePath) {
    //---------------------------------------------------------------
    // 1. Let's setup our AudioFile instance
        
    AudioFile<float> a;
    a.setNumChannels (2);
    a.setNumSamplesPerChannel (0);

        
    //---------------------------------------------------------------
    // 3. Write the samples to the AudioFile sample buffer
        
    a.setNumSamplesPerChannel (*top);
    for (int i = 0; i < a.getNumSamplesPerChannel(); i++)
    {
        for (int channel = 0; channel < a.getNumChannels(); channel++)
        {
            a.samples[channel][i] = samples -> at(i);
        }
    }
    
    //---------------------------------------------------------------
    // 4. Save the AudioFile
        
    // change this to somewhere useful for you
    a.save (filePath, AudioFileFormat::Wave);
}

void lineTextToAudio(std::string morseline,std::vector<float>* samples, int* top){
    for(int i = 0; i < morseline.size();i++){
        char carac = morseline.at(i);
        switch(carac){
            case '.': {
                ajouteBip(samples,top,0.2);
                ajouteSilence(samples,top,0.2);
                break;
            }
            case '-': {
                ajouteBip(samples,top,0.6);
                ajouteSilence(samples,top,0.2);
                break;
            }
            case ' ': {
                ajouteSilence(samples,top,0.4); // Deja 0.2s après le dernier caractère, il suffit donc de rajouter 0.4s
                break;
            }
            case '/': {
                ajouteSilence(samples,top,0.6); // Pour un total de 1.4s i.e. 7 temps.
                break;
            }
            default: {
                break;
            }
        } 
    }
}
