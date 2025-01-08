#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class Player; // Forward declaration
#include <SDL2/SDL.h>
#include <iostream>

class PlayerState {
public:
    virtual void handleEvents(Player& player, const SDL_Event& e) = 0;
    virtual void update(Player& player, float deltaTime) = 0;
    virtual void print() const = 0; // Pure virtual print method
    virtual ~PlayerState() = default;
};

class IdleState : public PlayerState {
public:
    void handleEvents(Player& player, const SDL_Event& e) override;
    void update(Player& player, float deltaTime) override;
    void print() const override {
        std::cout << "Player is in Idle state." << std::endl;
    }
};

class MovingState : public PlayerState {
public:
    void handleEvents(Player& player, const SDL_Event& e) override;
    void update(Player& player, float deltaTime) override;
    void print() const override {
        std::cout << "Player is in Moving state." << std::endl;
    }
};

class JumpingState : public PlayerState {
public:
    void handleEvents(Player& player, const SDL_Event& e) override;
    void update(Player& player, float deltaTime) override;
    void print() const override {
        std::cout << "Player is in Jumping state." << std::endl;
    }
};

#endif
