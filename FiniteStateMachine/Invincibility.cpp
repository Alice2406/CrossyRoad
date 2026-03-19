#include "Invincibility.h"
#include "Player.h"
#include <iostream>

void Invincibility::applyEffect(Player& player) {
    std::cout << "Recolte : VIE SUPPLEMENTAIRE" << std::endl;

    if (player.getLives() < 2) {
        player.addLife();
        std::cout << "Une vie a ete ajoutee (Total: " << player.getLives() << ")" << std::endl;
    }
    else {
        std::cout << "Vie deja au maximum !" << std::endl;
    }

}