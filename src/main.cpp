



#include "Audio.h"
#include "audio/Sound.h"

int main(int argc, char **argv){

    nk::Audio::initilize();

    nk::Sound testSound;
    testSound.load("media/test.wav");
    testSound.play();

}





