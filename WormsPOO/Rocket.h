#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
class Rocket
{
public:
    Rocket();
    ~Rocket();
    void Draw(sf::RenderWindow& w);
    void setPosition(const sf::Vector2f& position);
    void move(const sf::Vector2f& offset);
    const sf::RectangleShape& getShape() const;
    bool checkCollision(const Platform& platform);

private:
    // Création de la roquette
    sf::RectangleShape roquette;
    sf::Texture t;
    const float RADIUS_IMPACT = 30.0f;
    const float Speed = 700.0f;
    sf::Vector2f posRocket;
    sf::Vector2f Direction;
};

