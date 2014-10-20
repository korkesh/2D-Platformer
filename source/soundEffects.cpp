//
//  soundEffects.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-07-18.
//
//

#include "soundEffects.h"

#include <fstream>
#include <cstring>

SoundEngine::SoundEngine() {
    soundIndex = 1;
}

void SoundEngine::playSound(ALuint sound)
{
    alSourcePlay(sound);
    // *********This blocks main thread******
    //    ALint source_state;
    //    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    //    while (source_state == AL_PLAYING) {
    //        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    //    }
}

bool SoundEngine::isBigEndian()
{
    int a=1;
    return !((char*)&a)[0];
}

int SoundEngine::convertToInt(char* buffer,int len)
{
    int a=0;
    if(!isBigEndian())
        for(int i=0;i<len;i++)
            ((char*)&a)[i]=buffer[i];
    else
        for(int i=0;i<len;i++)
            ((char*)&a)[3-i]=buffer[i];
    return a;
}

char* SoundEngine::loadWAV(const char* fn,int& chan,int& samplerate,int& bps,int& size)
{
    char buffer[4];
    std::ifstream in(fn,std::ios::binary);
    in.read(buffer,4);
    if(strncmp(buffer,"RIFF",4)!=0)
    {
        std::cout << "this is not a valid WAVE file: " << fn << std::endl;
        return NULL;
    }
    in.read(buffer,4);
    in.read(buffer,4);      //WAVE
    in.read(buffer,4);      //fmt
    in.read(buffer,4);      //16
    in.read(buffer,2);      //1
    in.read(buffer,2);
    chan=convertToInt(buffer,2);
    in.read(buffer,4);
    samplerate=convertToInt(buffer,4);
    in.read(buffer,4);
    in.read(buffer,2);
    in.read(buffer,2);
    bps=convertToInt(buffer,2);
    in.read(buffer,4);      //data
    in.read(buffer,4);
    size=convertToInt(buffer,4);
    char* data=new char[size];
    in.read(data,size);
    return data;
}

void SoundEngine::sound(int xpos, int ypos, int zpos, const char* fileName, bool looping) {
    
    int channel, sampleRate, bps, size;
    char* data = loadWAV(fileName, channel, sampleRate, bps, size);
    ALCdevice* device=alcOpenDevice(NULL);
    if(device == NULL)
    {
        std::cout << "cannot open sound card" << std::endl;
        return 0;
    }
    ALCcontext* context=alcCreateContext(device,NULL);
    if(context==NULL)
    {
        std::cout << "cannot open context" << std::endl;
        return 0;
    }
    alcMakeContextCurrent(context);
    
    unsigned int bufferid,format;
    alGenBuffers(2, &bufferid);
    if(channel == 1)
    {
        if(bps == 8)
        {
            format = AL_FORMAT_MONO8;
        }else{
            format = AL_FORMAT_MONO16;
        }
    }else{
        if(bps == 8)
        {
            format = AL_FORMAT_STEREO8;
        }else{
            format = AL_FORMAT_STEREO16;
        }
    }
    
    ALuint soundMusic;
    alBufferData(bufferid, format, data, size, sampleRate);
    alGenSources(2, &soundMusic);
    alSourcei(soundMusic, AL_BUFFER, bufferid);
    
    alSource3f(soundMusic, AL_POSITION, 0, 0, 0);
    if (looping) {
        alSourcei(soundMusic, AL_LOOPING, AL_TRUE);
    } else {
        alSourcei(soundMusic, AL_LOOPING, AL_FALSE);
    }
    
    float f[]={1, 0, 0, 0, 1, 0};
    alListenerfv(AL_ORIENTATION, f);
    
    soundArray[soundIndex] = soundMusic;
    
    soundMap.insert(std::pair<const char*, ALuint>(fileName, soundIndex));
    soundIndex++;
    
}