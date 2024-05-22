#include <stdio.h>

extern "C" {
	#include "SDL.h"
	#include "SDL_thread.h"
	#include "SDL_main.h"
}

extern int PlayPcmByPush();
extern int PlayPcmByPull();

int main(int argc, char *argv[])
{
	SDL_version ver;
	SDL_VERSION(&ver);

	printf("hello sdl: %d %d\n", ver.major, ver.minor);

	PlayPcmByPull();

	return 0;
}