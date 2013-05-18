#include <iostream>

#include "ogg.h"

using namespace std;

ALCcontext *context;

void setupOpenAL()
{
	//Open default device
	ALCdevice* device = alcOpenDevice(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	
	if (!device)
		cerr << "unable to open default device" << endl;
	
	//Set up error handling - calling alGetError() once starts waiting for errors
	alGetError();

	//Set up context
	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
		cerr << "failed to make default context" << endl;
	
	//Set up listener
	alListener3f(AL_POSITION, 0, 0, 1.0f);
  alListener3f(AL_VELOCITY, 0, 0, 0);
	alListenerfv(AL_ORIENTATION, listenerOri);
}

void cleanupOpenAL()
{
	ALCdevice* device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

int main(int argc, char* argv[])
{
    ogg_stream ogg;
    
    setupOpenAL();
    //alutInit(&argc, argv);

	try
	{
        if(argc < 2)
            throw string("oggplayer *.ogg");
	
		ogg.open(argv[1]);

        //ogg.display();

		if(!ogg.playback())
            throw string("Ogg refused to play.");
                    
        while(ogg.update())
        {
            if(!ogg.playing())
            {
                if(!ogg.playback())
                    throw string("Ogg abruptly stopped.");
                else
                    cout << "Ogg stream was interrupted.\n";
            }
        }
                    
        cout << "Program normal termination.";
        cin.get();
    }
    catch(string error)
	{
		cout << error;
        cin.get();
	}
	
	ogg.release();
	
	//alutExit();
	cleanupOpenAL();

	return 0;
}
