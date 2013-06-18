/*
 * Sound.cpp
 *
 *  Created on: Jun 18, 2013
 *      Author: nicholas
 */

#include <AL/al.h>
#include <string>
#include <iostream>
#include "Sound.h"
#include "loaders/Wav.h"

namespace nk {

    Sound::Sound() {

        std::cout << "Created a new sound." << std::endl;
        alGenSources((ALuint) 1, &source);

        alSourcef(source, AL_PITCH, 1.5);
        alSourcef(source, AL_GAIN, 1);
        alSource3f(source, AL_POSITION, 0, 0, 0);
        alSource3f(source, AL_VELOCITY, 0, 0, 0);
        alSourcei(source, AL_LOOPING, AL_FALSE);

    }

    Sound::~Sound() {
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);

    }

    bool Sound::load(std::string fileName) {
        std::cout << "Attempting to load file:"<<fileName << std::endl;
        bool isLoaded = loadWavFile("media/test.wav", &buffer, &size, &freq,
                &format); //Call our own function to load a WAV file, since alut is deprecated

        if (isLoaded) {
            alSourcei(source, AL_BUFFER, buffer);
        } else {
            std::cerr << "Unable to load:" << fileName << std::endl;
        }
        return isLoaded;
    }

    void Sound::play() {
        alSourcePlay(source);

        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        while (source_state == AL_PLAYING) {
            alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        }
    }

    void Sound::pause(){
        alSourcePause(source);
    }

    void Sound::stop(){
        alSourceStop(source);
    }

    void Sound::rewind(){
        alSourceRewind(source);
    }

} /* namespace nk */
