#ifndef OPENAL_EXAMPLE_H
#define OPENAL_EXAMPLE_H

#include <string>
#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>

bool loadWavFile(const std::string filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format);

#endif
