// HelloMiyoo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Quick Formula for using SDL:
//      Create a window to render graphics. 
//      Create surface,
//      Transform surface to texture,
//      Render the texture.
// 
// Rendering:
//      Clear renderer
//      Copy texture to renderer
//      Display (present) renderer
// 
//      Profit

#include <iostream>
#include <SDL.h>                    // required for SDL operations
#include <SDL_ttf.h>                // required for SDL text rendering operations
#define WINDOW_HEIGHT 480           // window height in pixels
#define WINDOW_WIDTH 640            // window width in pixels
using namespace std;

int main(int argc, char* argv[])
{
    SDL_Surface* textSurface = NULL, * authorSurface = NULL;
    SDL_Texture* textTexture = NULL, * authorTexture = NULL;
    SDL_Renderer* renderer = NULL;

    // Use SDL_Init() to Initialize SDL components that we will need for our program. 
    // Use SDL_GetError() to get any errors
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "SDL coult not initialize! SDL Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    };

    // Initialize SDL_ttf library
    if (TTF_Init() == -1) {
        cout << "SDL coult not initialize TTF_Init: " << TTF_GetError() << endl;
        return EXIT_FAILURE;
    }

    // Create a window with the specified position, dimensions, and flags.
    // title 	the title of the window, in UTF-8 encoding
    // x 	    the x position of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
    // y 	    the y position of the window, SDL_WINDOWPOS_CENTERED, or SDL_WINDOWPOS_UNDEFINED
    // w 	    the width of the window, in screen coordinates
    // h 	    the height of the window, in screen coordinates
    // flags 	0, or one or more SDL_WindowFlags OR'd together
    SDL_Window* window = SDL_CreateWindow(
        "Hello Miyoo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_ALLOW_HIGHDPI
    );

    // Create a 2d Rendering context for the window
    // window 	the window where rendering is displayed
    // index 	the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
    // flags 	0, or one or more SDL_RendererFlags OR'd together
    renderer = SDL_CreateRenderer(window, -1, 0);
    //background color: (r, g, b, alpha)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Prepare Text Msg for displaying on screen
    // Load a font
    TTF_Font* font = TTF_OpenFont("Roboto-Black.ttf", 48);
    TTF_Font* authorfont = TTF_OpenFont("Roboto-Black.ttf", 18);
    if (font == NULL) {
        cout << "TTF_OpenFont: " << TTF_GetError() << endl;
        return EXIT_FAILURE;
    }
    // Set the color of the text
    SDL_Color color = { 255, 255, 255 };
    // Render the text into an SDL_Surface
    textSurface = TTF_RenderText_Blended(font, "Hello Miyoo", color);
    authorSurface = TTF_RenderText_Blended(authorfont, "by: Yorisoft", color);

    // Convert the surface to a texture
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    authorTexture = SDL_CreateTextureFromSurface(renderer, authorSurface);

    // Define a rect for the texture
    // A structure that contains the definition of a rectangle, with the origin at the upper left.
    // x    the x location of the rectangle's upper left corner
    // y    the y location of the rectangle's upper left corner
    // w    the width of the rectangle
    // h    the height of the rectangle
    SDL_Rect textRect;
    textRect.x = (WINDOW_WIDTH - textSurface->w) / 2;  // Center the text horizontally
    textRect.y = (WINDOW_HEIGHT - textSurface->h) / 2; // Center the text vertically
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    // Define another rect for the author's name
    SDL_Rect authorRect;
    authorRect.x = (WINDOW_WIDTH - authorSurface->w) / 2;  // Center the text horizontally
    authorRect.y = WINDOW_HEIGHT - authorSurface->h - 10; // Position the text at the bottom with a small margin
    authorRect.w = authorSurface->w;
    authorRect.h = authorSurface->h;

    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
            // Add this condition to quit when any key is pressed
            else if (windowEvent.type == SDL_KEYDOWN) {
                break;
            }
        }

        // Clear the window and make it all white
        SDL_RenderClear(renderer);

        // Copy the texture to the rendering context
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderCopy(renderer, authorTexture, NULL, &authorRect);

        // Flip the backbuffer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(authorSurface);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(authorTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    textSurface = NULL;
    textTexture = NULL;
    renderer = NULL;

    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

