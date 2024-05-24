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

		collisionLine.setSize(sf::Vector2f(1.f, sprite.getGlobalBounds().getSize().y / 2));
		collisionLine.setFillColor(sf::Color::Transparent); //DEBUG
		collisionLine.setPosition(sprite.getPosition().x + (sprite.getGlobalBounds().getSize().x / 2.f), sprite.getPosition().y + sprite.getGlobalBounds().getSize().y / 2);
	};
	void setPosition(sf::Vector2f position, const Terrain& terrain) {
		sprite.setPosition(position);
		healthBar.setPosition(position.x - 10.f, position.y - 15.f);
		collisionLine.setPosition(position.x + (sprite.getGlobalBounds().getSize().x / 2.f), position.y + sprite.getGlobalBounds().getSize().y / 2);
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
	void move(float offsetX, float offsetY, Terrain& terrain, sf::RenderWindow* window) {
		//BUG QUAND IL EST SUR LA RIGHTISLAND, WORM SURELEVE
		sf::Vector2u windowSize = window->getSize();

		if (sprite.getPosition().x < 0) {
			healthBar.move((- offsetX * speed) + 2, offsetY);
			healthBarBackground.move((- offsetX * speed) + 2, offsetY);
			sprite.move((- offsetX * speed) + 2, offsetY);
			collisionLine.move((- offsetX * speed) + 2, offsetY);
		}
		else if (sprite.getPosition().x + sprite.getGlobalBounds().width > windowSize.x) {
			healthBar.move((-offsetX * speed) - 2, offsetY);
			healthBarBackground.move((-offsetX * speed) - 2, offsetY);
			sprite.move((-offsetX * speed) - 2, offsetY);
			collisionLine.move((-offsetX * speed) - 2, offsetY);
		}

		healthBar.move(offsetX * speed, offsetY);
		healthBarBackground.move(offsetX * speed, offsetY);
		sprite.move(offsetX * speed, offsetY);
		collisionLine.move(offsetX * speed, offsetY);
		if (offsetX != 0) {
			if (!checkCollisionWithLine(terrain)) { //si le worm avance sur une pente descendante
				onGround = false;
			}
		}
		if (checkCollisionWithSprite(terrain)) { // si le worm essaie d'avancer dans un terrain
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

			if (checkCollisionWithLine(terrain)) { //atterit
				verticalSpeed = 0.f;
				onGround = true;
				sprite.move(0, -verticalSpeed * deltaTime);
				healthBar.move(0, -verticalSpeed * deltaTime);
				healthBarBackground.move(0, -verticalSpeed * deltaTime);
				collisionLine.move(0, -verticalSpeed * deltaTime);
			}
		}

		float angle = abs(getGroundAngle(terrain));
		if (angle > 135) { // PAS OPTI TROUVER MEILLEURE SOLUTION
			angle -= 90;
		}
		std::cout << "angle " << angle << std::endl;

		if (checkCollisionWithLine(terrain)) { //faire monter le worm s'il monte une pente, plus l'angle est élevé, plus il est ralenti
			sprite.move(0, -1 - (int)angle / 10);
			healthBar.move(0, -1 - (int)angle / 10);
			healthBarBackground.move(0, -1 - (int)angle / 10);
			collisionLine.move(0, -1 - (int)angle / 10);
		}
		if (checkCollisionWithSprite(terrain)) { // si le worm se cogne la tete
			verticalSpeed = 0.f;
			verticalSpeed += GRAVITY * deltaTime;
			healthBar.move(0, verticalSpeed * deltaTime);
			healthBarBackground.move(0, verticalSpeed * deltaTime);
			sprite.move(0, verticalSpeed * deltaTime);
			collisionLine.move(0, verticalSpeed * deltaTime);
		}
	}
	void update(float deltaTime, const Terrain& terrain) {
		applyGravity(deltaTime, terrain);
	}
	void aim(sf::Vector2f mousePos) {
		sf::Vector2f centerWorm = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f - 50.f);
		sf::Vector2f direction = mousePos - centerWorm;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		aimLine.setSize(sf::Vector2f(length, 3.f));
		float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f;
		aimLine.setRotation(angle);
		aimLine.setPosition(centerWorm);
	}
	Rocket* shoot(sf::Vector2f targetPosition) {
		Rocket* rocket = new Rocket();
		sf::Vector2f position = sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f , sprite.getGlobalBounds().height / 2.f - 50.f);
		sf::Vector2f direction = targetPosition - position;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= length;
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
	float getGroundAngle(const Terrain& terrain) const {
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sf::Vector2f bottomLeft(bounds.left, bounds.top + bounds.height);
		return terrain.getGroundAngleAtPoint(bottomLeft);
	}
	
private:
	float speed = 250.f;
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

