#include <stdio.h>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>

bool loadWavFile(const std::string filename, ALuint* buffer,
                 ALsizei* size, ALsizei* frequency,
                 ALenum* format);
