// Quick Formula for using SDL:
//		Initialize SDL
//      Create and define a window to render graphics. 
//      Create and define primary surface,
//      Create and define other surfaces ( for hello miyoo text ),
//		Define a position for those surfaces ( SDL_Rect )
//      Create and define a render context
// 		Create a texture for copying to the renderer 
// 		Copy other surfaces onto the main surface
//		Copy main surface to the texture
// 		Copy ( Or render ) the texture to the rendering context
// 
// Rendering:
//      Clear renderer
//      Copy texture to renderer
//      Display (present) renderer
// 
//      Profit

#include <iostream>
#include <SDL2/SDL.h>                    // required for SDL operations
#include <SDL2/SDL_ttf.h>                // required for SDL text rendering operations
#define WINDOW_HEIGHT 480           	// window height in pixels
#define WINDOW_WIDTH 640            	// window width in pixels
#define DEPTH 16            			// window depth in pixels
using namespace std;

int main(int argc, char* argv[])
{
    SDL_Surface* textSurface = NULL, * authorSurface = NULL, *screen = NULL;
    SDL_Texture* textTexture = NULL, * authorTexture = NULL;
    SDL_Renderer* renderer = NULL;

    // Use SDL_Init() to Initialize SDL components that we will need for our program. 
    // Use SDL_GetError() to get any errors
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "SDL coult not initialize! SDL Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    };

    // Create a window with the specified position, dimensions, and flags.
    SDL_Window* window = SDL_CreateWindow(
        "Hello Miyoo",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
	
	// Create a surface with the specified position, dimensions, and flags.
	screen = SDL_CreateRGBSurface(
		0, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT, 
		DEPTH, 
		0, 0, 0, 0
	);
	// Perform a fast fill of a rectangle ( our surface ) with a specific color.
	SDL_FillRect(
		screen, 
		&screen->clip_rect, 
		SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)
	);
	
	// Initialize SDL_ttf library
    if (TTF_Init() == -1) {
        cout << "SDL coult not initialize TTF_Init: " << TTF_GetError() << endl;
        return EXIT_FAILURE;
    }
    // Prepare Text Msg surface for displaying on screen
    // Load a font
    TTF_Font* font = TTF_OpenFont("Roboto-Black.ttf", 58);
    TTF_Font* authorfont = TTF_OpenFont("Roboto-Black.ttf", 28);
    if (font == NULL) {
        cout << "TTF_OpenFont: " << TTF_GetError() << endl;
        return EXIT_FAILURE;
    }
    // Set the color of the text
    SDL_Color color = { 255, 255, 255 };
    // Render the text into an SDL_Surface
    textSurface = TTF_RenderText_Blended(font, "Hello Miyoo", color);	
    authorSurface = TTF_RenderText_Blended(authorfont, "by: Yorisoft", color);
	
	// Define a rect for the surface
    // A structure that contains the definition of a rectangle, with the origin at the upper left.
    SDL_Rect textRect;
    textRect.x = (WINDOW_WIDTH - textSurface->w) / 2;  		// Center the text horizontally
    textRect.y = (WINDOW_HEIGHT - textSurface->h) / 2; 		// Center the text a vertically-top
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;	
    // Define another rect for the author's name
    SDL_Rect authorRect;
    authorRect.x = (WINDOW_WIDTH - authorSurface->w) / 2;  	// Center the text horizontally
    authorRect.y = WINDOW_HEIGHT - authorSurface->h - 10; 				// Position the text a bit lower
    authorRect.w = authorSurface->w;
    authorRect.h = authorSurface->h;

	// Create a 2d Rendering context for the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Create a texture for copying to the renderer 
	textTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// Copy our temp surfaces ( what ever graphics they have up to this point ) onto the main surface
	SDL_BlitSurface(textSurface, NULL, screen, &textRect);
	SDL_BlitSurface(authorSurface, NULL, screen, &authorRect);
    SDL_FreeSurface(textSurface);
	SDL_FreeSurface(authorSurface);
	// Copy our main surface to the texture
	SDL_UpdateTexture(textTexture, NULL, screen->pixels, screen->pitch);
	
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
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);\

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