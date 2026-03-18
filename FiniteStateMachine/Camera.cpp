#include "Camera.h"

Camera::Camera(sf::Vector2f startLogicalPos, sf::Vector2f viewSize)
    : m_logicalPos(startLogicalPos)
{
    m_autoScroll = 0.f;
    m_view.setSize(viewSize);
}

void Camera::update(float dt, sf::Vector2f playerGridPos) {
    // 1. INITIALISATION DYNAMIQUE (Au premier appel)
    // On se cale sur le spawn du joueur, peu importe où il est sur la map
    if (!m_initialized) {
        m_startY = playerGridPos.y; // On mémorise la ligne de départ
        m_autoScroll = 0.f;         // On part de zéro scroll
        m_initialized = true;
    }

    // 2. SCROLLING AUTOMATIQUE RÉGULIER
    // La caméra avance toute seule à la vitesse m_speed
    if (m_speed < m_maxSpeed) {
        m_speed += m_acceleration * dt;
    }
    m_autoScroll += m_speed * dt;

    // 3. LOGIQUE DE RATTRAPAGE INSTANTANÉ
    // autoLimitY est la ligne où la caméra "devrait" être
    float autoLimitY = m_startY - m_autoScroll;

    // Si le joueur dépasse la caméra (Y plus petit), on tire le scroll avec lui
    if (playerGridPos.y < autoLimitY) {
        autoLimitY = playerGridPos.y;
        // On recalcule m_autoScroll pour supprimer la latence
        m_autoScroll = m_startY - playerGridPos.y;
    }

    // 4. AXE X FIXE (Très important pour la stabilité)
    // Mets ici la même valeur que ta colonne de spawn (ex: 20.f)
    float fixedGridX = 20.0f;

    // 5. CONVERSION ISOMÉTRIQUE
    // On utilise exactement les mêmes constantes que ta Map (32, 24, 900, 200)
    float targetIsoX = (fixedGridX - autoLimitY) * 32.f + 900.f;
    float targetIsoY = (fixedGridX + autoLimitY) * 24.f + 200.f;

    // 6. RÉGLAGE DE LA VUE (Zoom et Taille)
    m_view.setSize({ 1800.f * m_zoomFactor, 900.f * m_zoomFactor });

    // 7. POSITIONNEMENT FINAL (Offsets)
    // Ajuste offsetX et offsetY pour placer le perso en bas à droite
    // Valeurs négatives = décalage de la caméra vers le Haut/Gauche 
    // (ce qui fait descendre le décor vers le Bas/Droite)
    float offsetX = 500.f * m_zoomFactor;
    float offsetY = 100.f * m_zoomFactor;

    m_view.setCenter({ targetIsoX + offsetX, targetIsoY + offsetY });
}

void Camera::apply(sf::RenderWindow& window) {
    window.setView(m_view);
}

float Camera::getScreenBottom() const {
    return m_view.getCenter().y + (m_view.getSize().y / 2.0f);
}