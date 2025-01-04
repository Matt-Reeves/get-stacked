#include <SDL2/SDL.h>
#include <iostream>

#include "player.hpp"
#include "LTimer.hpp"
#include "globals.h"
#include "level.hpp"


//Declare global variables
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

Player player;
Level level;

int main() {    

    bool quit = false;         // Main loop flag
    SDL_Event e;               // Event handler

    LTimer fpsTimer;           // The frames per second timer
    LTimer capTimer;           // The frames per second cap timer

    level.setName("Level 1");
    
    GameObject ground;
    GameObject platform1, platform2, platform3; 
    ground.setRect({0,SCREEN_HEIGHT-10,SCREEN_WIDTH,50});
    platform1.setRect({100,SCREEN_HEIGHT-100,100,20});
    platform2.setRect({200,SCREEN_HEIGHT-200,100,20});
    platform3.setRect({600,SCREEN_HEIGHT-200,100,20});
    
    level.addPlatform(ground);
    level.addPlatform(platform1);
    level.addPlatform(platform2);
    level.addPlatform(platform3);
    level.print();


    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Get Stacked", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Start counting frames per second
    int countedFrames = 0;
    fpsTimer.start();

    // Time since last frame
    float deltaTime = 0.0f;
	Uint32 lastTime = SDL_GetTicks();
    // While application is running
    while (!quit) {
        
        capTimer.start(); // Start cap timer
        Uint32 startTime = SDL_GetTicks();
        
        // Render
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
        SDL_RenderClear(gRenderer);
        SDL_SetRenderDrawColor(gRenderer, 255, 0, 255, 0);
        SDL_RenderFillRect(gRenderer, player.getRect());
        SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);
        SDL_RenderFillRect(gRenderer, ground.getRect());
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderFillRect(gRenderer, platform1.getRect());
        SDL_RenderFillRect(gRenderer, platform2.getRect());
        SDL_RenderFillRect(gRenderer, platform3.getRect());
        SDL_RenderPresent(gRenderer);

        // Update the surface
        SDL_UpdateWindowSurface(gWindow);
        ++countedFrames;
        
        // Calculate and correct fps
        float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
        if (avgFPS > 2000000) {
            avgFPS = 0;
        }
        // If frame finished early
        int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICK_PER_FRAME) {
            SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
        }
        Uint32 endTime = SDL_GetTicks();
        float deltaTime = (endTime-startTime)/ 1000.0f;
        
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true; // User requests quit
            player.handleEvents(e);
        }
        
        player.move(deltaTime);
        player.detectCollisions(level);
        
        
    }

    return 0;
}
