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
            enum FileTypes {WAV,OGG};
            virtual ~Sound();
            virtual bool load(std::string, FileTypes);
            virtual void play();
            virtual void pause();
            virtual void stop();
            virtual void rewind();
            virtual States getState();

            virtual void setPitch(float);
            virtual void setGain(float);
            virtual void setLooping(bool);
            virtual void setPosition(float,float,float);
            virtual void setVelocity(float,float,float);



        protected:
//            ALsizei size, freq;
//            ALenum format;
//            void setState(ALenum);
            ALuint buffer, source;
//            ALint source_state;
    };

} /* namespace nk */
#endif /* SOUND_H_ */
