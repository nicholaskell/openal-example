/*
 * Sound.h
 *
 *  Created on: Jun 18, 2013
 *      Author: nicholas
 */

#ifndef SOUND_H_
#define SOUND_H_

#include <string>

namespace nk {

    class Sound {
        public:
            Sound();
            enum States {STATE_PLAYING, STATE_STOPPED, STATE_PAUSED};
            virtual ~Sound();
            virtual bool load(std::string);
            virtual void play();
            virtual void pause();
            virtual void stop();
            virtual void rewind();



        protected:
            ALsizei size, freq;
            ALenum format;
            ALuint buffer, source;
            ALint source_state;
    };

} /* namespace nk */
#endif /* SOUND_H_ */
