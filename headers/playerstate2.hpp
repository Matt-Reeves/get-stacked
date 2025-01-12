#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "player.hpp"
#include "playerstatemachine.hpp"
#include "playerdata.hpp"


class PlayerState {
protected: 
    Player* player;
    PlayerStateMachine* stateMachine;
    PlayerData* playerData;
    float startTime;

private:
    std::string animBoolName;

public:
    virtual void enter();
    virtual void exit();
    virtual void logicUpdate();
    virtual void physicsUpdate();
    virtual void doChecks();

    PlayerState(Player *player, PlayerStateMachine *stateMachine, PlayerData *playerData, std::string animBoolName);
    virtual ~PlayerState() = default;
    
};

// Constructor definition
PlayerState::PlayerState(Player *player, PlayerStateMachine *stateMachine, PlayerData *playerData, std::string animBoolName): 
    player(player), 
    stateMachine(stateMachine), 
    playerData(playerData),
    animBoolName(animBoolName) {}

void PlayerState::enter()
{
    doChecks();
    //startTime = Time.time;

};

#endif
