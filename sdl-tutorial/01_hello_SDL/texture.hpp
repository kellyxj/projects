#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Texture{
public:
    Texture();
    ~Texture();

    bool loadFromFile(SDL_Renderer* Renderer, std::string path);
    void free();

    void render(SDL_Renderer* Renderer, int x, int y);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;

    int width;
    int height;
};