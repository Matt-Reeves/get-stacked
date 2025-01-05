#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class Player; //forward declaration
#include <SDL2/SDL.h>

class PlayerState {
public:
    virtual void handleEvents(Player& player, const SDL_Event& e) = 0;
    virtual void update(Player& player, float deltaTime) = 0;
    virtual ~PlayerState() = default;
};

class IdleState : public PlayerState {
public:
    void handleEvents(Player& player, const SDL_Event& e) override;
    void update(Player& player, float deltaTime) override;
};

class MovingState : public PlayerState {
public:
    void handleEvents(Player& player, const SDL_Event& e) override;
    void update(Player& player, float deltaTime) override;
};

class JumpingState : public PlayerState {
public:
    void handleEvents(Player& player, const SDL_Event& e) override;
    void update(Player& player, float deltaTime) override;
};

#endif