#include "Worms.h"
#include <iostream>

Worms::Worms() : verticalSpeed(0.f), onGround(true) {
    Health.setSize(sf::Vector2f(20.f, 5.f));
    Health.setFillColor(sf::Color::Green);
    Health.setPosition(worm.getPosition().x, worm.getPosition().y - 20);

    aimLine.setSize(sf::Vector2f(5.f, 5.f));
    aimLine.setFillColor(sf::Color::Red);

    worm.setSize(sf::Vector2f(90.f, 50.f));
    worm.setFillColor(sf::Color::Black);
    sf::Texture t;
    if (!t.loadFromFile("C:/Users/bryan/source/repos/Jeu/TestJeu/Image/Worms.png")) {
        std::cerr << "Erreur lors du chargement de la texture de la roquette." << std::endl;
    }
    worm.setTexture(&t);
    isRocketLaunched = false;
}

Worms::~Worms() {
}

void Worms::setPosition(const sf::Vector2f& position) {
    worm.setPosition(position);
    Health.setPosition(position.x, position.y - 20);
}

sf::Vector2f Worms::GetSize() {
    return worm.getSize();
}

sf::Vector2f Worms::GetPosition() {
    return worm.getPosition();
}

void Worms::SetVerticalSpeed(float Di) {
    if (Di > 0) {
        verticalSpeed += Di;
    }
    else {
        verticalSpeed = JUMP_VELOCITY;
    }
}

void Worms::move(float offsetX, float offsetY) {
    Health.move(offsetX * Speed, offsetY);
    worm.move(offsetX * Speed, offsetY);
}

void Worms::draw(sf::RenderWindow& window, bool isMousePressed) const {
    window.draw(worm);
    window.draw(Health);
    if (isMousePressed) window.draw(aimLine);
}

sf::FloatRect Worms::getGlobalBounds() const
{
    return sf::FloatRect();
}

void Worms::jump() {
    if (onGround) {
        verticalSpeed = JUMP_VELOCITY;
        onGround = false;
    }
}

void Worms::applyGravity(float deltaTime, const sf::RectangleShape& ground, const sf::Image& groundImage) {
    if (!onGround) {
        verticalSpeed += GRAVITY * deltaTime;
        Health.move(0, verticalSpeed * deltaTime);
        worm.move(0, verticalSpeed * deltaTime);
    }
    checkCollisionWithGround(ground, groundImage);
}

void Worms::checkCollisionWithGround(const sf::RectangleShape& ground, const sf::Image& groundImage) {
    sf::FloatRect wormBounds = worm.getGlobalBounds();
    sf::FloatRect groundBounds = ground.getGlobalBounds();

    if (wormBounds.intersects(groundBounds)) {
        int left = static_cast<int>(wormBounds.left);
        int top = static_cast<int>(wormBounds.top);
        int right = static_cast<int>(wormBounds.left + wormBounds.width);
        int bottom = static_cast<int>(wormBounds.top + wormBounds.height);

        bool collision = false;

        for (int x = left; x < right; ++x) {
            for (int y = top; y < bottom; ++y) {
                if (x - groundBounds.left >= 0 && x - groundBounds.left < groundImage.getSize().x &&
                    y - groundBounds.top >= 0 && y - groundBounds.top < groundImage.getSize().y) {
                    if (groundImage.getPixel(x - groundBounds.left, y - groundBounds.top).a != 0) {
                        collision = true;
                        break;
                    }
                }
            }
            if (collision) {
                break;
            }
        }

        if (collision) {
            worm.setPosition(worm.getPosition().x, ground.getPosition().y - worm.getSize().y);
            verticalSpeed = 0.f;
            onGround = true;
        }
        else {
            onGround = false;
        }
    }
    else {
        onGround = false;
    }
}

bool Worms::isOnGround() const {
    return onGround;
}

void Worms::setOnGround(bool onGround) {
    this->onGround = onGround;
}

const sf::RectangleShape& Worms::getShape() const {
    return worm;
}

void Worms::shoot(sf::RectangleShape rocket, const sf::Vector2f& targetPosition) {
    sf::Vector2f position = worm.getPosition() + sf::Vector2f(worm.getSize().x / 2.f, worm.getSize().y / 2.f);
    sf::Vector2f direction = targetPosition - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length;
    //rocket.shoot();
    isRocketLaunched = true;
}

void Worms::AimLinePosition(sf::RenderWindow& window, bool isMousePressed) {
    if (isMousePressed) {
        sf::Vector2f centerWorms = worm.getPosition() + sf::Vector2f(worm.getSize().x / 2.f, worm.getSize().y / 2.f);
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f directionVec = mousePos - centerWorms;
        float length = std::sqrt(directionVec.x * directionVec.x + directionVec.y * directionVec.y);
        aimLine.setSize(sf::Vector2f(length, 5.0f)); // Longueur de la ligne, largeur de 5 pixels
        float angle = std::atan2(directionVec.y, directionVec.x) * 180.f / 3.14159f;
        aimLine.setRotation(angle);
        aimLine.setPosition(centerWorms);
    }
}

bool Worms::IsRocketLaunched()
{
    return isRocketLaunched;
}

void Worms::SetRocketLaunched(bool launched)
{
    isRocketLaunched = launched;
}
