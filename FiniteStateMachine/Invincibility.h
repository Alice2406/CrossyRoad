#ifndef INVINCIBILITY_H
#define INVINCIBILITY_H
#include "PowerUp.h"

class Invincibility : public PowerUp {
public:
    void applyEffect(Player& player) override;
};

#endif