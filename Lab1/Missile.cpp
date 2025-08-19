#include "Missile.h"
#include "Macros.h"

void Missile::update() 
{
    if (this->isActive)
    {
        if (this->isEnemy == false)
        {
            if (this->position.y <= 0)
            {
                this->isActive = false;
            }
            else
            {
                this->travelTime++;
                if (this->travelTime >= 2)
                {
                    this->travelTime = 0;
                    this->position.y += acceleration;
                }
            }
        }
        else
        {
            if (this->position.y >= HEIGHT - 1)
            {
                this->isActive = false;
            }
            else
            {
                this->travelTime++;
                if (this->travelTime >= 2)
                {
                    this->travelTime = 0;
                    this->position.y += acceleration;
                }
            }
        }
    }
}

