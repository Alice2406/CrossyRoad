#ifndef INVISIBILITY_H
#define INVISIBILITY_H
#include "PowerUp.h"

class Invisibility : public PowerUp {
public:
    void applyEffect(Player& player) override;
};

#endif