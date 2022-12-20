#pragma once
#include "Player.h"

//class for all of the other players
class Ghost :
    public Player
{
public:
    Ghost(playerDATA data);
    Ghost();

    ~Ghost();

    void updatePlayerData(playerDATA data, float ping);
    
    void handleInput(float dt) override;

    float lerp(float a, float b, float f)
    {
        return a * (1.0 - f) + (b * f);
    }

    sf::Vector2f directionVectors[3];
};

