#include <SDL.h>
#include <iostream>

extern "C"
{
	int main(int argc, char * argv[])
	{
		if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		{
			std::cerr << "Failed to init SDL: " << SDL_GetError() << std::endl;
			return 1;
		}

		SDL_Quit();
		return 0;
	}
}