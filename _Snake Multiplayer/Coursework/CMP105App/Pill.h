#pragma once
#include "Framework/GameObject.h"
class Pill :
    public GameObject
{
public:
    Pill();
    ~Pill();

    void render();
    void update();
    sf::CircleShape _shape;
    float _growthValue;

};

