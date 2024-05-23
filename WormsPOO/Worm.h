#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rocket.h"
#include "Terrain.h"

class Worm
{
public:
	Worm() : verticalSpeed(0.f), onGround(true) {
		if (!texture.loadFromFile("./assets/worm.png")) {
			std::cerr << "Erreur lors du chargement de la texture du ver" << std::endl;
		}
		sprite.setTexture(texture);
		sprite.setScale(0.3f, 0.3f);
		sprite.setTextureRect(sf::IntRect(0, 0, 109, 169));

		aimLine.setSize(sf::Vector2f(5.f, 5.f));
		aimLine.setFillColor(sf::Color::Red);

		healthBar.setSize(sf::Vector2f(169.f * 0.3, 5.f));
		healthBar.setFillColor(sf::Color::Green);
		healthBar.setPosition(sprite.getPosition().x - 10.f, sprite.getPosition().y - 15.f);

		healthBarBackground.setSize(sf::Vector2f(182.f * 0.3, 9.f));
		healthBarBackground.setFillColor(sf::Color::Black);
		healthBarBackground.setPosition(sprite.getPosition().x - 12.f, sprite.getPosition().y - 17.f);

		collisionLine.setSize(sf::Vector2f(1.f, sprite.getGlobalBounds().getSize().y));
		collisionLine.setFillColor(sf::Color::Red); //DEBUG
		collisionLine.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().getSize().x / 2.f), sprite.getPosition().y);
	};
	void setPosition(sf::Vector2f position, const Terrain& terrain) {
		sprite.setPosition(position);
		healthBar.setPosition(position.x - 10.f, position.y - 15.f);
		collisionLine.setPosition(position.x + (sprite.getGlobalBounds().getSize().x / 2.f), position.y);
		healthBarBackground.setPosition(position.x - 12.f, position.y - 17.f);
		while (checkCollisionWithLine(terrain)) {
			sprite.move(0, -1.f);
			healthBar.move(0, -1.f);
			collisionLine.move(0, -1.f);
			healthBarBackground.move(0, -1.f);
		}
	}
	sf::Vector2f getPosition() const {
		return sprite.getPosition();
	}
	void move(float offsetX, float offsetY, Terrain& terrain) {
		healthBar.move(offsetX * speed, offsetY);
		healthBarBackground.move(offsetX * speed, offsetY);
		sprite.move(offsetX * speed, offsetY);
		collisionLine.move(offsetX * speed, offsetY);
		if (offsetX != 0) {
			if (!checkCollisionWithLine(terrain)) {
				onGround = false;
			}
		}
		if (checkCollisionWithSprite(terrain)) {
			std::cout << "Collision" << std::endl;
			healthBar.move(- offsetX * speed, offsetY);
			healthBarBackground.move(- offsetX * speed, offsetY);
			sprite.move(- offsetX * speed, offsetY);
			collisionLine.move(- offsetX * speed, offsetY);
		}
	}
	void draw(sf::RenderWindow& window, bool isMousePressed) const {
		window.draw(sprite);
		window.draw(healthBarBackground);
		window.draw(healthBar);
		window.draw(collisionLine);
		if (isMousePressed) window.draw(aimLine);
	}
	void jump() {
		if (onGround) {
			verticalSpeed = JUMP_VELOCITY;
			onGround = false;
		}
	}
	void applyGravity(float deltaTime, const Terrain& terrain) {
 		if (!onGround) {
			verticalSpeed += GRAVITY * deltaTime;
			healthBar.move(0, verticalSpeed * deltaTime);
			healthBarBackground.move(0, verticalSpeed * deltaTime);
			sprite.move(0, verticalSpeed * deltaTime);
			collisionLine.move(0, verticalSpeed * deltaTime);

			if (checkCollisionWithLine(terrain)) {
				verticalSpeed = 0.f;
				onGround = true;
				sprite.move(0, -verticalSpeed * deltaTime);
				healthBar.move(0, -verticalSpeed * deltaTime);
				healthBarBackground.move(0, -verticalSpeed * deltaTime);
				collisionLine.move(0, -verticalSpeed * deltaTime);
			}
		}
	}
	void update(float deltaTime, const Terrain& terrain) {
		applyGravity(deltaTime, terrain);
	}
	void aim(sf::Vector2f mousePos) {
		sf::Vector2f centerWorm = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f - 50.f);
		sf::Vector2f direction = mousePos - centerWorm;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		aimLine.setSize(sf::Vector2f(length, 3.f)); // Longueur de la ligne, largeur de 5 pixels
		float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
		aimLine.setRotation(angle);
		aimLine.setPosition(centerWorm);
	}
	Rocket* shoot(sf::Vector2f targetPosition) {
		Rocket* rocket = new Rocket();
		sf::Vector2f position = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f , sprite.getGlobalBounds().height / 2.f - 50.f);
		sf::Vector2f direction = targetPosition - position;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= length; // Normalisation
		rocket->setPosition(position);
		rocket->setDirection(direction);
		return rocket;
	}
	bool checkCollisionWithLine(const Terrain& terrain) {
		return terrain.isCollidingRect(collisionLine);
	}
	bool checkCollisionWithSprite(const Terrain& terrain) {
		return terrain.isCollidingSprite(sprite);
	}
	
private:
	const float speed = 400.f;
	const float GRAVITY = 981.0f;
	const float JUMP_VELOCITY = -400.0f;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarBackground;
	sf::RectangleShape aimLine;
	sf::RectangleShape collisionLine;
	float verticalSpeed;
	bool onGround;
};

