//
//  soundEffects.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-07-18.
//
//

#ifndef __opengl_series__soundEffects__
#define __opengl_series__soundEffects__

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <iostream>
#include <map>

#define MAX_SOUNDS (10)

class SoundEngine {
    
    ALuint soundArray[MAX_SOUNDS];

    std::map<const char*, ALuint> soundMap;
    
    ALuint soundIndex;
    
public:
    SoundEngine();
    
    std::map<const char*, ALuint> getSoundMap() { return soundMap; }
    ALuint* getSound() { return soundArray;}
    
    void playSound(ALuint sound);
    void sound(int xpos, int ypos, int zpos, const char* fileName, bool looping);

    bool isBigEndian();
    int convertToInt(char* buffer,int len);
    char* loadWAV(const char* fn,int& chan,int& samplerate,int& bps,int& size);

};

#endif /* defined(__opengl_series__soundEffects__) */
