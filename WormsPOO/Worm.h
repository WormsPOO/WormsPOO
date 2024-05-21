#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rocket.h"

class Worm
{
public:
	Worm() : verticalSpeed(0.f), onGround(true) {
		if (!texture.loadFromFile("./assets/worm.png")) {
			std::cerr << "Erreur lors du chargement de la texture du ver" << std::endl;
		}
		sprite.setTexture(texture);
		sprite.setScale(0.7f, 0.7f);
		sprite.setTextureRect(sf::IntRect(0, 0, 283, 283));

		aimLine.setSize(sf::Vector2f(5.f, 5.f));
		aimLine.setFillColor(sf::Color::Red);

		healthBar.setSize(sf::Vector2f(200.f, 5.f));
		healthBar.setFillColor(sf::Color::Green);
		healthBar.setPosition(sprite.getPosition().x -1.f, sprite.getPosition().y - 10.f);
	};
	void setPosition(sf::Vector2f position) {
		sprite.setPosition(position);
		healthBar.setPosition(position.x + 10.f, position.y - 5.f);
	}
	sf::Vector2f getPosition() const {
		return sprite.getPosition();
	}
	void move(float offsetX, float offsetY) {
		healthBar.move(offsetX * speed, offsetY);
		sprite.move(offsetX * speed, offsetY);
	}
	void draw(sf::RenderWindow& window, bool isMousePressed) const {
		window.draw(sprite);
		window.draw(healthBar);
		if (isMousePressed) window.draw(aimLine);
	}
	void jump() {
		if (onGround) {
			verticalSpeed = JUMP_VELOCITY;
			onGround = false;
		}
	}
	void applyGravity(float deltaTime, sf::Vector2u windowSize) {
 		if (!onGround) {
			verticalSpeed += GRAVITY * deltaTime;
			healthBar.move(0, verticalSpeed * deltaTime);
			sprite.move(0, verticalSpeed * deltaTime);

			if (sprite.getPosition().y >= windowSize.y - 283.f) { // Position du sol arbitraire
				sprite.setPosition(sprite.getPosition().x, windowSize.y - 283.f);
				healthBar.setPosition(sprite.getPosition().x + 10.f, sprite.getPosition().y - 5.f);
				verticalSpeed = 0.f;
				onGround = true;
			}
		}
	}
	void update(float deltaTime, sf::Vector2u windowSize) {
		applyGravity(deltaTime, windowSize);
	}
	void aim(sf::Vector2f mousePos) {
		sf::Vector2f centerWorm = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
		sf::Vector2f direction = mousePos - centerWorm;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		aimLine.setSize(sf::Vector2f(length, 5.f)); // Longueur de la ligne, largeur de 5 pixels
		float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
		aimLine.setRotation(angle);
		aimLine.setPosition(centerWorm);
	}
	Rocket* shoot(sf::Vector2f targetPosition) {
		Rocket* rocket = new Rocket();
		sf::Vector2f position = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
		sf::Vector2f direction = targetPosition - position;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= length; // Normalisation
		rocket->setPosition(position);
		rocket->setDirection(direction);
		return rocket;
	}
	
private:
	const float speed = 400.f;
	const float GRAVITY = 981.0f;
	const float JUMP_VELOCITY = -400.0f;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape healthBar;
	sf::RectangleShape aimLine;
	float verticalSpeed;
	bool onGround;
};

