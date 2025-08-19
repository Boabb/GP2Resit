#include "Alien.h"
#include "Menu.h"

void Alien::setPosition(short x, short y)
{
    this->position.x = x;
    this->position.y = y;
    position.x = x;
    position.y = y;
}

void Alien::update()
{
    RandomEngine randomEngine;
    shootCooldown -= randomEngine.getRandomShort(0, 5);
}

void Alien::shoot(Missile& missile)
{
    RandomEngine randomEngine;

    if (this->isActive && this->shootCooldown <= 0)
    {
        this->shootCooldown += MAXENEMYSHOOTCOOLDOWN * randomEngine.getRandomShort(1, 5);
        missile.position = { this->position.x, (short)(this->position.y + missile.acceleration) };
        missile.setActive(true);
    }
}


