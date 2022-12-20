#pragma once
#include "Player.h"
class Ghost :
    public Player
{
public:
    Ghost(playerDATA data);
    Ghost();

    ~Ghost();

    void updatePlayerData(playerDATA data);
    
    void handleInput(float dt) override;

};

