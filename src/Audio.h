/*
 * Audio.h
 *
 *  Created on: Jun 18, 2013
 *      Author: nicholas
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <AL/al.h>
#include <AL/alc.h>

namespace nk {

    class Audio {
        public:
            Audio();
            virtual ~Audio();
            static void initilize();


        protected:
            static ALCdevice *device;
            static ALCcontext *context;


    };

} /* namespace nk */
#endif /* AUDIO_H_ */
