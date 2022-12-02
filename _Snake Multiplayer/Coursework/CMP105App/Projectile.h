#pragma once
#include "Framework/GameObject.h"
class Projectile :
    public GameObject
{
public:
    Projectile();
    ~Projectile();

    void update(float dt) override;
    void handleInput(float dt) override;
};

