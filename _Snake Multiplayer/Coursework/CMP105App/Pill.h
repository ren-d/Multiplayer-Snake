#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include <iostream>
#include <random>
struct pillDATA
{
    sf::Int16 id,
        x, y,
        growthValue;
};

class Pill :
    public GameObject
{
public:
    Pill();
    Pill(pillDATA data);
    ~Pill();

    void init();
    void render(sf::RenderWindow* wwindow);
    void update();
    sf::CircleShape _shape;
    float _growthValue;

    pillDATA _data;

};

