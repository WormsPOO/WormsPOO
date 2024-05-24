#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int MAP_WIDTH = 1800;
const int MAP_HEIGHT = 900;

class Terrain
{
public:
    Terrain(sf::Vector2u windowSize) {
        if (!texture.loadFromFile("./assets/terrain.png")) {
            std::cerr << "Erreur lors du chargement de la texture du ver" << std::endl;
        }

        leftIsland.setPointCount(7);

        leftIsland.setPoint(0, sf::Vector2f(0, 200));
        leftIsland.setPoint(1, sf::Vector2f(windowSize.x - 1600.f, 230));
        leftIsland.setPoint(2, sf::Vector2f(windowSize.x - 1400.f , 205));
        leftIsland.setPoint(3, sf::Vector2f(windowSize.x - 1200.f, 340));
        leftIsland.setPoint(4, sf::Vector2f(windowSize.x - 1300.f, 450));
        leftIsland.setPoint(5, sf::Vector2f(windowSize.x - 1450.f, 400));
        leftIsland.setPoint(6, sf::Vector2f(0, 450));

        leftIsland.setTexture(&texture);
        //leftIsland.setFillColor(sf::Color::Green);

        centerIsland.setPointCount(7);

        centerIsland.setPoint(0, sf::Vector2f(windowSize.x - 1100.f, 205));
        centerIsland.setPoint(1, sf::Vector2f(windowSize.x - 1000.f, 150));
        centerIsland.setPoint(2, sf::Vector2f(windowSize.x - 900.f, 175));
        centerIsland.setPoint(3, sf::Vector2f(windowSize.x - 800.f, 220));
        centerIsland.setPoint(4, sf::Vector2f(windowSize.x - 780.f, 380));
        centerIsland.setPoint(5, sf::Vector2f(windowSize.x - 950.f, 430));
        centerIsland.setPoint(6, sf::Vector2f(windowSize.x - 1050.f, 320));
        
        centerIsland.setTexture(&texture);
        //centerIsland.setFillColor(sf::Color::Green);

        rightIsland.setPointCount(10);

        rightIsland.setPoint(0, sf::Vector2f(windowSize.x - 200.f, 0));
        rightIsland.setPoint(1, sf::Vector2f(windowSize.x - 210.f, 50));
        rightIsland.setPoint(2, sf::Vector2f(windowSize.x - 450.f, 125));
        rightIsland.setPoint(3, sf::Vector2f(windowSize.x - 500.f, 300));
        rightIsland.setPoint(4, sf::Vector2f(windowSize.x - 620.f, 380));
        rightIsland.setPoint(5, sf::Vector2f(windowSize.x - 700.f, 450));
        rightIsland.setPoint(6, sf::Vector2f(windowSize.x - 650.f, 550));
        rightIsland.setPoint(7, sf::Vector2f(windowSize.x - 325.f, 600));
        rightIsland.setPoint(8, sf::Vector2f(windowSize.x, 550));
        rightIsland.setPoint(9, sf::Vector2f(windowSize.x, 0));

        rightIsland.setTexture(&texture);
        //rightIsland.setFillColor(sf::Color::Green);

        ground.setPointCount(8);

        ground.setPoint(0, sf::Vector2f(0, windowSize.y - 300.f));
        ground.setPoint(1, sf::Vector2f(windowSize.x - 1650.f, windowSize.y - 150.f));
        ground.setPoint(2, sf::Vector2f(windowSize.x - 1250.f, windowSize.y - 225.f));
        ground.setPoint(3, sf::Vector2f(windowSize.x - 950.f, windowSize.y - 200.f));
        ground.setPoint(4, sf::Vector2f(windowSize.x - 850.f, windowSize.y - 275.f));
        ground.setPoint(5, sf::Vector2f(windowSize.x, windowSize.y - 100));
        ground.setPoint(6, sf::Vector2f(windowSize.x, windowSize.y));
        ground.setPoint(7, sf::Vector2f(0, windowSize.y));

        ground.setTexture(&texture);
        //ground.setFillColor(sf::Color::Green);
        if (!renderTexture.create(windowSize.x, windowSize.y)) {
            std::cerr << "Erreur lors de la création du RenderTexture" << std::endl;
        }
        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(leftIsland);
        renderTexture.draw(centerIsland);
        renderTexture.draw(rightIsland);
        renderTexture.draw(ground);
        renderTexture.display();
        collisionImage = renderTexture.getTexture().copyToImage();
    }
    void draw(sf::RenderWindow& window) {
        window.draw(leftIsland);
        window.draw(centerIsland);
        window.draw(rightIsland);
        window.draw(ground);
    }
    bool isCollidingRect(const sf::RectangleShape& collisionLine) const {
        sf::FloatRect rectBounds = collisionLine.getGlobalBounds();
        for (int x = static_cast<int>(rectBounds.left); x < static_cast<int>(rectBounds.left + rectBounds.width); ++x) {
            for (int y = static_cast<int>(rectBounds.top); y < static_cast<int>(rectBounds.top + rectBounds.height); ++y) {
                if (x >= 0 && x < static_cast<int>(collisionImage.getSize().x) && y >= 0 && y < static_cast<int>(collisionImage.getSize().y)) {
                    if (collisionImage.getPixel(x, y).a != 0) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    bool isCollidingSprite(const sf::Sprite& sprite) const {
        sf::FloatRect spriteBounds = sprite.getGlobalBounds();
        sf::Image image = renderTexture.getTexture().copyToImage();

        sf::Vector2f topLeft(spriteBounds.left, spriteBounds.top);
        sf::Vector2f topRight(spriteBounds.left + spriteBounds.width, spriteBounds.top);

        if (isPixelOpaque(image, topLeft) || isPixelOpaque(image, topRight)) {
            return true;
        }
        return false;
    }
    bool containsPoint(const sf::ConvexShape& shape, const sf::Vector2f& point) const {
        sf::FloatRect bounds = shape.getGlobalBounds();
        return bounds.contains(point.x, point.y);
    }
    bool isPixelOpaque(const sf::Image& image, sf::Vector2f point) const {
        if (point.x < 0 || point.y < 0 || point.x >= image.getSize().x || point.y >= image.getSize().y) {
            return false;
        }
        sf::Color pixelColor = image.getPixel(point.x, point.y);
        return pixelColor.a != 0; // Vérifie si le pixel est opaque
    }
    float getGroundAngleAtPoint(const sf::Vector2f& point) const {
        for (const auto& shape : { &leftIsland, &centerIsland, &rightIsland, &ground }) {
            if (shape->getGlobalBounds().contains(point)) {
                //std::cout << shape->getPointCount() << std::endl;
                for (size_t i = 0; i < shape->getPointCount(); ++i) {
                    //std::cout << shape->getPoint(i).x << "  " << shape->getPoint(i).y << std::endl;
                    sf::Vector2f p1 = shape->getTransform().transformPoint(shape->getPoint(i));
                    sf::Vector2f p2 = shape->getTransform().transformPoint(shape->getPoint((i + 1) % shape->getPointCount()));
                    if ((point.x >= std::min(p1.x, p2.x) && point.x <= std::max(p1.x, p2.x)) &&
                        (point.y >= std::min(p1.y, p2.y) && point.y <= std::max(p1.y, p2.y))) {
                        float angle = std::atan2(p2.y - p1.y, p2.x - p1.x) * 180 / 3.14159265f;
                        return angle;
                    }
                }
            }
        }
        return 0.f; 
    }
    bool isNearGround(const sf::Vector2f& point, float distance) const {
        for (int x = static_cast<int>(point.x) - distance; x <= static_cast<int>(point.x) + distance; ++x) {
            for (int y = static_cast<int>(point.y) - distance; y <= static_cast<int>(point.y) + distance; ++y) {
                if (x >= 0 && x < static_cast<int>(collisionImage.getSize().x) && y >= 0 && y < static_cast<int>(collisionImage.getSize().y)) {
                    if (collisionImage.getPixel(x, y).a != 0) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
private:
    sf::ConvexShape leftIsland;
    sf::ConvexShape rightIsland;
    sf::ConvexShape ground;
    sf::ConvexShape centerIsland;
    sf::Texture texture;
    sf::RenderTexture renderTexture;
    sf::Image collisionImage;
};

