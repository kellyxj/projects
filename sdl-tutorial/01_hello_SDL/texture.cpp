#include "texture.hpp"

Texture::Texture() {
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(SDL_Renderer* Renderer, std::string path) {
    free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        std::cout << "Failed to load image " << path.c_str() << " " << "SDL_Image error: " << IMG_GetError();
    }
    else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface);
        if(newTexture == NULL) {
            std::cout << "Unable to create texture from " << path.c_str() << ". SDL_Error: " << SDL_GetError();
        }
        else {
            width = loadedSurface->w;
            height = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    texture = newTexture;
    return newTexture != NULL;
}

void Texture::free() {
    if(texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::render(SDL_Renderer* Renderer) {
    
}