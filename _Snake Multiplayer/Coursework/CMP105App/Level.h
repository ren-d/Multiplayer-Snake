#pragma once
#include "Framework/BaseLevel.h"
class Level :
    BaseLevel
{
public:
    Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
    ~Level();

    void handleInput(float dt) override;
    void update(float dt);
    void render();
};

