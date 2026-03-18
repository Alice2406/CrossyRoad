#include "Invincibility.h"
#include "Player.h"
#include <iostream>

void Invincibility::applyEffect(Player& player) {
    std::cout << "Recolte : VIE SUPPLEMENTAIRE" << std::endl;
    
    if (player.getLives() < 2) {
        player.addLife();
    }
}