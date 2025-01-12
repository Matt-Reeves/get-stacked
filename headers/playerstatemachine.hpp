#include "playerstate2.hpp"
class PlayerStateMachine {

    public:
        PlayerState currentState;
        
        void initialize(PlayerState startingState);
        void changeState(PlayerState newstate);
        PlayerState getCurrentState(){return currentState;}

    private:
        void setCurrentState(PlayerState currentState);
        
    protected:


};

void PlayerStateMachine::setCurrentState(PlayerState currentState){
    this->currentState = currentState;
}

void PlayerStateMachine::initialize(PlayerState startingState){
    currentState = startingState;

}