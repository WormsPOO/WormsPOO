#include "Platform.h"
#include <iostream>
#include <string>
#include <cmath>


Platform::Platform(float posX, float posY)
{
    platform.setSize(sf::Vector2f(800, 100));
    platform.setPosition(posX, posY);
    platform.setFillColor(sf::Color::Green);
    platformTexture.create(static_cast<unsigned int>(800), static_cast<unsigned int>(100));
    if (!platformTexture.loadFromFile("C:/Users/bryan/source/repos/Jeu/TestJeu/Image/Ground.png")) {
        std::cerr << "Erreur lors du chargement de la texture de la roquette." << std::endl;
    }
    platformImage = platformTexture.copyToImage();
    platform.setTexture(&platformTexture);
}

Platform::~Platform()
{
}

void Platform::draw(sf::RenderWindow& window) const
{
    window.draw(platform);
}

void Platform::destroyZone(const sf::Vector2f& impactPosition, float radius)
{
    // Calcul des limites du rectangle entourant la zone à détruire
    int left = static_cast<int>(std::max(0.f, impactPosition.x - radius));
    int top = static_cast<int>(std::max(0.f, impactPosition.y - radius));
    int right = static_cast<int>(std::min(static_cast<float>(platformImage.getSize().x), impactPosition.x + radius));
    int bottom = static_cast<int>(std::min(static_cast<float>(platformImage.getSize().y), impactPosition.y + radius));

    // Parcours des pixels dans la zone de destruction
    for (int x = left; x < right; ++x) {
        for (int y = top; y < bottom; ++y) {
            // Calcul de la distance entre le pixel et le centre de l'impact
            float distance = std::sqrt((x - impactPosition.x) * (x - impactPosition.x) + (y - impactPosition.y) * (y - impactPosition.y));
            if (distance <= radius) {
                platformImage.setPixel(x, y, sf::Color::Transparent); // Rendre le pixel transparent si dans le rayon
            }
        }
    }
}
