#pragma once
#include <SFML/Graphics.hpp>
class Platform
{

private:
    sf::RectangleShape platform;
    sf::Texture platformTexture;
    sf::Image platformImage;


public:
    Platform(float posX, float posY);
    ~Platform();
    void draw(sf::RenderWindow& window) const;
    const sf::RectangleShape& getShape() const;
    void destroyZone(const sf::Vector2f& impactPosition, float radius);
};

