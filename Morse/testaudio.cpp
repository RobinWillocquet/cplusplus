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
    writeAudioFile(samples,top,"SOS.wav"); // On crée un signal SOS en rajoutant des bips et des silences
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
    lineTextToAudio("... --- ...",samplesi,topi,0.2);
    writeAudioFile(samplesi,topi,"SOSi.wav"); // On convertit "... --- ..." en .wav
    std::cout << "**********************" << std::endl;
    std::cout << "Test audio : création d'un signal SOS 2 " << std::endl;        
    std::cout << "**********************" << std::endl << std::endl;
    delete samplesi;
    delete topi;
    std::string inputwav = "SOSi.wav";
    AudioFile<float> soswav;
    bool loadedok = soswav.load(inputwav); // On charge le .wav qu'on vient de créer dans soswav
    assert(loadedok);
    std::vector<float>* samplesj = new std::vector<float>;
    int numSamples = soswav.getNumSamplesPerChannel();
    int numChannels = soswav.getNumChannels();
    std::cout << numSamples << std::endl;
    std::cout << numChannels << std::endl;
    for(int i = 0; i < 430;i++) {
        samplesj -> push_back(soswav.samples[0][i]); // samplesj sera la liste des samples de SOSi.wav
        std::cout << samplesj -> at(i) << ", "; // ... Il arrete d'en afficher apres environ 430 samples ! Pourquoi ? Même sans les afficher, le programme freeze au bout d'un certain temps... While infini ? Je ne sais pas...
    }
    std::string sosmorse;
    sosmorse = AudioToText(samplesj,0.2); // Ne fonctionne pas... Enfin je n'ai pas d'erreur de compil mais le programme freeze !
    std::cout << "'" << sosmorse << "'" << std::endl;
    delete samplesj;
}