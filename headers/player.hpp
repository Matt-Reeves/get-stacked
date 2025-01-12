#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include "level.hpp"
#include "playerstate.hpp"
#include <memory>

enum State {
    IDLE         = 0,
    FACING_LEFT  = 1 << 0,
    FACING_RIGHT = 1 << 1,
    MOVING       = 1 << 2,
    DASHING      = 1 << 3,
    JUMPING      = 1 << 4,
    FALLING      = 1 << 5
};

class Player {
    private:
        
        PlayerState* currentState;

        int Vx, Vy;
        SDL_Rect rect;
        
        const int VEL = 800;
        const int RECT_WIDTH = 40;
        const int RECT_HEIGHT = 60;

    public:

        bool isJumping;
        bool isFalling;
        bool isGrounded;
        bool canMove;

        Player();
        ~Player();
        
        SDL_Rect* getRect(){return &rect;}
        void handleEvents(const SDL_Event &e);
        void logicUpdate(Level& level);
        void move(const float &deltaTime);
        void setVelocity(int Vx, int Vy){this-> Vx = Vx; this-> Vy = Vy;}
        int getVelocityY(){return Vy;}
        int getVelocityX(){return Vx;}
        void setVelocityY(int Vy){this->Vy = Vy;}
        void setVelocityX(int Vx){this->Vx = Vx;}
        
        void update(const float &deltaTime);
        bool detectCollisions(Level &level);
        void changeState(PlayerState* newState);
        void printState(){currentState->print();}
        
};

#endif



