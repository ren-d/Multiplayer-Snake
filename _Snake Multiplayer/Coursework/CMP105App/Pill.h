#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include <iostream>
#include <random>
class Pill :
    public GameObject
{
public:
    Pill();
    ~Pill();

    void render(sf::RenderWindow* wwindow);
    void update();
    sf::CircleShape _shape;
    float _growthValue;

};

