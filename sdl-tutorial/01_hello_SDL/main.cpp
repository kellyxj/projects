/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "texture.hpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool quit = false;
SDL_Event e;

SDL_Window* Window = NULL;

SDL_Renderer* Renderer = NULL;

//The image we will load and show on the screen
SDL_Texture* Texture = NULL;

bool init (){
	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Init failed. SDL_Error: " << SDL_GetError();
		success = false;
	}
	else {
		Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(Window == NULL) {
			std::cout << "Window creation failed. SDL_Error: " << SDL_GetError();
			success = false;
		}
		else {
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			if(Renderer == NULL) {
				std::cout << "Renderer could not be created. SDL Error: " << SDL_GetError();
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					std::cout << "Failed to initialize SDL_image. SDL_image error: " << IMG_GetError();
					success = false;
				}
			}
		}
	}
	return success;
}

SDL_Texture* loadTexture(std::string path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL) {
		std::cout << "Image load failed. SDL_Image error: " << path.c_str() << " " << IMG_GetError();
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
		if(newTexture == NULL) {
			std::cout << "Unable to create texture from " << path.c_str() << " " << SDL_GetError();
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

bool loadMedia()
{
    bool success = true;

    Texture = loadTexture( "texture.png" );
    if( Texture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

    return success;
}

void close() {
	SDL_DestroyTexture(Texture);
	Texture = NULL;

	SDL_DestroyRenderer(Renderer);
	Renderer = NULL;

	SDL_DestroyWindow(Window);
	Window = NULL;

	IMG_Quit();
	SDL_Quit();
}


int main( int argc, char* args[] )
{
	//Initialize SDL
	if( !init())
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		if(!loadMedia()) {
			printf("Failed to load media\n");
		}
		else {
			SDL_Rect topLeftViewport;
			topLeftViewport.x = 0;
			topLeftViewport.y = 0;
			topLeftViewport.w = SCREEN_WIDTH / 2;
			topLeftViewport.h = SCREEN_HEIGHT / 2;

			SDL_Rect topRightViewport;
            topRightViewport.x = SCREEN_WIDTH / 2;
            topRightViewport.y = 0;
            topRightViewport.w = SCREEN_WIDTH / 2;
            topRightViewport.h = SCREEN_HEIGHT / 2;
            
			SDL_Rect bottomViewport;
            bottomViewport.x = 0;
            bottomViewport.y = SCREEN_HEIGHT / 2;
            bottomViewport.w = SCREEN_WIDTH;
            bottomViewport.h = SCREEN_HEIGHT / 2;

			while(!quit) {
				while(SDL_PollEvent(&e) != 0) {
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					else if(e.type == SDL_KEYDOWN) {
						switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            std::cout << "up\n";
                            break;

                            case SDLK_DOWN:
                            std::cout << "down\n";
                            break;

                            case SDLK_LEFT:
                            std::cout << "left\n";
                            break;

                            case SDLK_RIGHT:
                            std::cout << "right\n";
                            break;

                            default:
                            std::cout << e.key.keysym.sym << "\n";
                            break;
                        }
					}
				}
				SDL_RenderClear(Renderer);

				SDL_RenderSetViewport( Renderer, &topLeftViewport );
				SDL_RenderCopy(Renderer, Texture, NULL, NULL);

				SDL_RenderSetViewport( Renderer, &topRightViewport );
				SDL_RenderCopy(Renderer, Texture, NULL, NULL);

				SDL_RenderSetViewport( Renderer, &bottomViewport );
				SDL_RenderCopy(Renderer, Texture, NULL, NULL);

				SDL_RenderPresent(Renderer);
			}
			
		}
	}

	//Destroy window
	SDL_DestroyWindow( Window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}