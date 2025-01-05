#include <SDL2/SDL.h>

#include "level.hpp"
#include "player.hpp"
#include "LTimer.hpp"

class Game {
    private:
        bool quit = false;
        int countedFrames = 0;
        
        Player player;
        Level level;
        
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event e;
        
        LTimer fpsTimer, capTimer;

    public:
        bool init();
        //bool loop();
        void update(float dt);
        void render();
        bool cleanup();
        void buildLevel();

    

};