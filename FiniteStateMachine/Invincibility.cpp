#include "Invincibility.h"
#include "Player.h"
#include <iostream>

void Invincibility::applyEffect(Player& player) {
    std::cout << "Recolte : VIE SUPPLEMENTAIRE" << std::endl;
    // On ajoute une vie seulement si le joueur n'en a qu'une
    if (player.getLives() < 2) {
        player.addLife();
    }
}