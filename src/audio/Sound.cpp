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
//        source_state = NULL;
        buffer = NULL;
        source = NULL;
        std::cout << "Created a new sound." << std::endl;
        alGenSources((ALuint) 1, &source);

//        alSourcef(source, AL_PITCH, 1);
//        alSourcef(source, AL_GAIN, 2);
//        alSource3f(source, AL_POSITION, 0, 0, 0);
//        alSource3f(source, AL_VELOCITY, 0, 0, 0);
//        alSourcei(source, AL_LOOPING, AL_FALSE);

        this->setPitch(1.1);
        this->setGain(1.0);
        this->setPosition(0,0,0);
        this->setVelocity(0,0,0);
        this->setLooping(false);


    }

    Sound::~Sound() {
        if (source) {
            alDeleteSources(1, &source);
        }
        if (buffer) {
            alDeleteBuffers(1, &buffer);
        }

    }

    void Sound::setPitch(float pitch) {
        alSourcef(source, AL_PITCH, ALfloat(pitch));
    }

    void Sound::setGain(float gain) {
        alSourcef(source, AL_GAIN, ALfloat(gain));
    }

    void Sound::setPosition(float x, float y, float z) {
        alSource3f(source, AL_POSITION, ALfloat(z), ALfloat(y), ALfloat(z));
    }

    void Sound::setVelocity(float x, float y, float z) {
        alSource3f(source, AL_VELOCITY, ALfloat(z), ALfloat(y), ALfloat(z));
    }

    void Sound::setLooping(bool loop) {
        ALint toLoop = AL_FALSE;
        if (loop) {
            toLoop = AL_TRUE;
        }
        alSourcef(source, AL_LOOPING, toLoop);
    }

    bool Sound::load(std::string fileName, FileTypes type) {
        std::cout << "Attempting to load file:" << fileName << std::endl;
        bool isLoaded = false;
        switch (type) {
            default:
                break;
            case Sound::WAV:
                isLoaded = loadWavFile("media/test.wav", &buffer); //Call our own function to load a WAV file, since alut is deprecated
                break;
            case Sound::OGG:
                break;
        }

        if (isLoaded) {
            alSourcei(source, AL_BUFFER, buffer);
            //alDeleteBuffers(1, &buffer);
        } else {
            std::cerr << "Unable to load:" << fileName << std::endl;
        }
        return isLoaded;
    }


    Sound::States Sound::getState() {
        ALint source_state;
        States state;
        alGetSourcei(source, AL_SOURCE_STATE, &source_state);
        switch (source_state) {
            default:
                break;
            case AL_PLAYING:
                state = STATE_PLAYING;
                break;
            case AL_PAUSED:
                state = STATE_PAUSED;
                break;
            case AL_STOPPED:
                state = STATE_STOPPED;
                break;
        }
        return state;

    }

    void Sound::play() {
        alSourcePlay(source);
    }

    void Sound::pause() {
        alSourcePause(source);
    }

    void Sound::stop() {
        alSourceStop(source);
    }

    void Sound::rewind() {
        alSourceRewind(source);
    }

} /* namespace nk */
