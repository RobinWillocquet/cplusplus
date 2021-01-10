#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "AudioFile.h"
#include "audiolib.h"

void SOS(std::vector<float>* samples,int* top){
    for(int i = 0; i < 3; i++){
        ajouteBip(samples,top,0.2);
        ajouteSilence(samples,top,0.2);
    }
    ajouteSilence(samples,top,0.4);
    for(int i = 0; i < 3; i++){
        ajouteBip(samples,top,0.6);
        ajouteSilence(samples,top,0.2);
    }
    ajouteSilence(samples,top,0.4);
    for(int i = 0; i < 2; i++){
        ajouteBip(samples,top,0.2);
        ajouteSilence(samples,top,0.2);
    }
    ajouteBip(samples,top,0.2);
    // ajouteSilence(samples,top,0.2);

}

int main() {
    //---------------------------------------------------------------
    /** Writes a sine wave to an audio file */
    std::vector<float>* samples = new std::vector<float>;
    int* top = new int;
    *top = 0;
    SOS(samples,top);
    writeAudioFile(samples,top,"SOS.wav");
    // std::cout << samples -> size() << std::endl;
    // std::cout << *top << std::endl;
    delete samples;
    delete top;
    //---------------------------------------------------------------
    std::cout << "**********************" << std::endl;
    std::cout << "Test audio : création d'un signal SOS" << std::endl;        
    std::cout << "**********************" << std::endl << std::endl;
    std::vector<float>* samplesi = new std::vector<float>;
    int* topi = new int;
    *topi = 0;
    lineTextToAudio("... --- ...",samplesi,topi);
    writeAudioFile(samplesi,topi,"SOSi.wav");
    std::cout << "**********************" << std::endl;
    std::cout << "Test audio : création d'un signal SOS 2 " << std::endl;        
    std::cout << "**********************" << std::endl << std::endl;
    delete samplesi;
    delete topi;
}