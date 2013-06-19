/*
 * OpenAL example
 *
 * Copyright(C) Florian Fainelli <f.fainelli@gmail.com>
 */

/*
 * Modifications by Mark Hutcheson 2013
 *
 * Modifications public domain if above copyright notice doesn't apply (Shoot, I won't pretend to know how copyright works)
 *
 */
#include "openal-example.h"

int oldMain(int argc, char **argv)
{
	ALboolean enumeration;
	const ALCchar *devices;
	const ALCchar *defaultDeviceName = argv[1];
	int ret;
	char *bufferData;
	ALCdevice *device;
	ALuint *data;
	ALCcontext *context;
	ALsizei size, freq;
	ALenum format;
	ALuint buffer, source;
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	ALCenum error;
	ALint source_state;


	if (!defaultDeviceName)
		defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

	device = alcOpenDevice(defaultDeviceName);
	if (!device) {
		std::cerr << "unable to open default device" << std::endl;
		return -1;
	}

	std::cout <<  "Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;

	alGetError();

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		std::cerr << "failed to make default context" << std::endl;
		return -1;
	}

	/* set orientation */
	alListener3f(AL_POSITION, 0, 0, 1.0f);
    	alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);

	alGenSources((ALuint)1, &source);

	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);

	loadWavFile("media/test.wav", &buffer);	//Call our own function to load a WAV file, since alut is deprecated

	alSourcei(source, AL_BUFFER, buffer);

	alSourcePlay(source);

	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	while (source_state == AL_PLAYING) {
		alGetSourcei(source, AL_SOURCE_STATE, &source_state);
	}

	/* exit context */
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);

	return 0;
}
