//
//  soundEffects.cpp
//  opengl-series
//
//  Created by Matthew Correia on 2014-07-18.
//
//

#include "soundEffects.h"
#include "sound.h"

#include <fstream>
#include <cstring>

ALCdevice *device;
ALCcontext *context;
ALuint soundCollision, soundExplosion, soundCow, soundPig;
ALuint bufferCollision, bufferExplosion, bufferCow, bufferPig;
ALsizei size, freq;
ALenum format;
ALvoid *data;

void playSound(ALuint sound)
{
    alSourcePlay(sound);
    // *********This blocks main thread******
    //    ALint source_state;
    //    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    //    while (source_state == AL_PLAYING) {
    //        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    //    }
}

bool isBigEndian()
{
    int a=1;
    return !((char*)&a)[0];
}

int convertToInt(char* buffer,int len)
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

char* loadWAV(const char* fn,int& chan,int& samplerate,int& bps,int& size)
{
    char buffer[4];
    std::ifstream in(fn,std::ios::binary);
    in.read(buffer,4);
    if(strncmp(buffer,"RIFF",4)!=0)
    {
        std::cout << "this is not a valid WAVE file"  << std::endl;
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

void sound(int xpos, int zpos)
{
    int channel,sampleRate,bps,size;
    char* data=loadWAV("/Users/Korkesh/2D-Platformer/resources/SuperMarioBros.wav",channel,sampleRate,bps,size);
    ALCdevice* device=alcOpenDevice(NULL);
    if(device==NULL)
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
    alGenBuffers(1,&bufferid);
    if(channel==1)
    {
        if(bps==8)
        {
            format=AL_FORMAT_MONO8;
        }else{
            format=AL_FORMAT_MONO16;
        }
    }else{
        if(bps==8)
        {
            format=AL_FORMAT_STEREO8;
        }else{
            format=AL_FORMAT_STEREO16;
        }
    }
    alBufferData(bufferid,format,data,size,sampleRate);
//    unsigned int sourceid;
    alGenSources(1,&soundCollision);
    alSourcei(soundCollision,AL_BUFFER,bufferid);
    
    alSource3f(soundCollision,AL_POSITION,0,0,0);
    alSourcei(soundCollision,AL_LOOPING,AL_TRUE);

    float f[]={1,0,0,0,1,0};
    alListenerfv(AL_ORIENTATION,f);

    
}