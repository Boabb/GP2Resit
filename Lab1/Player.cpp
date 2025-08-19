#include "Player.h"
#include "Macros.h"

void Player::update()
{
    char input;

    input = std::cin.get();
    if (input == 'w')
    {
        if ((position.x - 1) > 0)
        {
            position.x--;
        }
    }
    else if (input == 'a')
    {
        if ((position.y - 1) > 0)
        {
            position.y--;
        }
    }
    else if (input == 's')
    {
        if ((position.x + 1) < WIDTH - 1)
        {
            position.x++;
        }
    }
    else if (input == 'd')
    {
        if ((position.y + 1) < HEIGHT - 1)
        {
            position.y++;
        }
    }
}

void Player::fireMissile(Missile& missile) const
{
    if (this->isActive && shootCooldown <= 0)
    {
        missile.position = { this->position.x, (short)(this->position.y - 1) };
        missile.setActive(true);
    }
};
