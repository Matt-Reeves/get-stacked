#include "playerstate.hpp"
#include "player.hpp"
#include <iostream>
#include "globals.h"

// IdleState
void IdleState::handleEvents(Player& player, const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                player.changeState(new MovingState());
                break;
            case SDLK_LEFT:
                player.changeState(new MovingState());
                break;
            case SDLK_SPACE:
                player.changeState(new JumpingState());
                break;
            // Other cases...
        }
    }
}

void IdleState::update(Player& player, const float deltaTime){
    //Do nothing
}


// MovingState
void MovingState::handleEvents(Player& player, const SDL_Event& e) {
    if (e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT)) {
        player.changeState(new IdleState());
    
    } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
        player.changeState(new JumpingState());
    }
}

void MovingState::update(Player& player, float deltaTime) {
    //

}

// JumpingState
void JumpingState::handleEvents(Player& player, const SDL_Event& e) {
    if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE) {
        if (player.getVelocityY() < 0) {
            player.setVelocityY(player.getVelocityY()/2); // Halve upward velocity if  travelling upward. 
        }
    }
}


void JumpingState::update(Player& player, float deltaTime) {
    // Update logic for JumpingState
}
