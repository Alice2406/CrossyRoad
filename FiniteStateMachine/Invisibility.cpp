#include "Invisibility.h"
#include "Player.h"
#include <iostream>

void Invisibility::applyEffect(Player& player) {
    std::cout << "Recolte : INVISIBILITE (5.0s)" << std::endl;
    player.setGhostMode(5.0f); // On active le mode fantôme pour 5 secondes
}
