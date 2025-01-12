#include "playerstate.hpp"
#include "player.hpp"
#include <iostream>
#include "globals.h"

// IdleState
void IdleState::handleEvents(Player& player, const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT:
                player.setVelocityX(+VEL);
                player.changeState(new MovingState());
                break;
            case SDLK_LEFT:
                player.setVelocityX(-VEL);
                player.changeState(new MovingState());
                break;
            case SDLK_SPACE:
                player.setVelocityY(-VEL);
                player.isGrounded = false;
                player.changeState(new JumpingState());
                break;
        }
    }
}

void IdleState::update(Player& player, const float deltaTime){
    player.move(deltaTime);
}

void IdleState::logicUpdate(Player &player, Level& level){
     player.detectCollisions(level);
}


// MovingState
void MovingState::handleEvents(Player& player, const SDL_Event& e) {
    if (e.type == SDL_KEYUP && (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_LEFT)) {
        player.setVelocityX(0);
        player.changeState(new IdleState());
    
    }  
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
        player.setVelocityY(-VEL);
        player.isGrounded = false;
        player.changeState(new JumpingState());
    }
}

void MovingState::update(Player& player, float deltaTime) { 
    player.move(deltaTime);
}

void MovingState::logicUpdate(Player &player, Level& level){
     player.detectCollisions(level);
}

// JumpingState
void JumpingState::handleEvents(Player& player, const SDL_Event& e ) {
    if (e.type == SDL_KEYUP){ 
        if (e.key.keysym.sym == SDLK_SPACE) {
            if (player.getVelocityY() < 0) {
                player.setVelocityY(player.getVelocityY()/2); // Halve upward velocity if  travelling upward. 
            }
        }            
        if (e.key.keysym.sym == SDLK_LEFT ) {
            player.setVelocityX(0);
        }
        else if (e.key.keysym.sym == SDLK_RIGHT){
            player.setVelocityX(0);
        }
    }
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_LEFT){
            if (player.getVelocityX() >= 0)
                player.setVelocityX(-VEL);
        }
        if (e.key.keysym.sym == SDLK_RIGHT)
        {
            if (player.getVelocityX() <= 0 )
            player.setVelocityX(VEL);
        }
    }
}

void JumpingState::logicUpdate(Player &player, Level& level){
     if (player.detectCollisions(level)){
        if (player.getVelocityX() != 0){  
            player.changeState(new MovingState());
        }
        else { 
            player.changeState(new IdleState());
        }
     }
}


void JumpingState::update(Player& player, float deltaTime) {
    player.move(deltaTime);
}
