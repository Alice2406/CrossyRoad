#ifndef POWERUP_H
#define POWERUP_H

class Player; 
class PowerUp {

public:
    virtual ~PowerUp() = default;
    virtual void applyEffect(Player& player) = 0;
};

#endif