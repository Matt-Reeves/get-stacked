#include "player.hpp"
#include "globals.h"
#include "level.hpp"
#include "playerstate.hpp"
#include <iostream>

//Constuctor
Player::Player(){
    Vx = 0;
    Vy = 0;
    rect.x = 0;
    rect.y = 0;
    rect.h = RECT_HEIGHT;
    rect.w = RECT_WIDTH;
    currentState = new JumpingState();
    //currentState = new IdleState();

}

// Destructor
Player::~Player() {
    delete currentState; // Clean up the current state
}

// void Player::handleEvents(const SDL_Event& e){

// if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
// {
//     //Adjust the velocity
//     switch( e.key.keysym.sym )
//     {
//         case SDLK_LEFT: Vx -= VEL; break;
//         case SDLK_RIGHT: Vx += VEL; break;
//         case SDLK_SPACE: 
//             if (isGrounded){
//                 Vy -= VEL; 
//                 isGrounded = false;
//             }
//                 break;
            
//     }
// }
// //If a key was released
// else if ( e.type == SDL_KEYUP && e.key.repeat == 0 )
// {
//     //Adjust the velocity
//     switch( e.key.keysym.sym )
//     {
//             case SDLK_LEFT: Vx += VEL; break;
//             case SDLK_RIGHT: Vx -= VEL; break;
//             case SDLK_SPACE: 
//                 if (Vy < 0){ 
//                     Vy /= 2; 
//                     break;
//                 }
            
//     }
//     }
// }

void Player::move(const float &deltaTime ){

rect.x += Vx*deltaTime;
rect.y += Vy*deltaTime;

//Update position (forward Euler)
 if (!isGrounded)
    Vy += GRAVITY*deltaTime;
// if (*currentState == MovingState)


//Undo movement if collision with wall occurs
if (rect.x + rect.w > SCREEN_WIDTH || rect.x < 0 ){ 
    rect.x -= Vx*deltaTime;
}

}


bool Player::detectCollisions(Level &level){

    //Lambda for bounds checks
    auto isWithinBounds = [](SDL_Rect* platform, SDL_Rect &rect) {
            bool yOverlap = rect.y + rect.h >= platform->y && rect.y + rect.h <= platform->y + platform->h;
            bool xOverlap = rect.x + rect.w >= platform->x && rect.x  <= platform->x + platform->w;
        return xOverlap && yOverlap;
    };

        //Check for platform collisions
        std::size_t numPlatforms = level.platforms.size();
        for (std::size_t i=0; i<numPlatforms; i++){
            SDL_Rect *currentPlatform = level.platforms[i].getRect();
            if (Vy >= 0){
                if (isWithinBounds(currentPlatform,rect))
                {   
                    std::cout << "Collision detected: Platform " << i <<  std::endl;
                    Vy = 0;
                    rect.y = currentPlatform->y - rect.h;
                    isGrounded = true;
                    return true;
                }
                else
                { 
                    isGrounded = false;
                }
                
            }
                //if (isGrounded) break;
        }
            return false;
    }
    

void Player::handleEvents(const SDL_Event& e) {
    currentState->handleEvents(*this, e);
}

void Player::logicUpdate(Level& level){
    currentState->logicUpdate(*this, level);
}

void Player::update(const float &deltaTime) {
    currentState->update(*this, deltaTime);
}

void Player::changeState(PlayerState* newState) {
    delete currentState;
    currentState = newState;
}

