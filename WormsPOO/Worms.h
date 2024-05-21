#pragma once
#include "Rocket.h"
class Worms
{

public:
	Worms();
	~Worms();

	void setPosition(const sf::Vector2f& position);
	void move(float offsetX, float offsetY);
	void draw(sf::RenderWindow& window, bool isMousePressed) const;
	sf::FloatRect getGlobalBounds() const;
	void applyGravity(float deltaTime, const sf::RectangleShape& ground, const sf::Image& groundImage);
	void jump();
	bool isOnGround() const;
	void setOnGround(bool onGround);
	const sf::RectangleShape& getShape() const;
	void shoot(sf::RectangleShape rocket, const sf::Vector2f& targetPosition);
	sf::Vector2f GetSize();
	sf::Vector2f GetPosition();
	void SetVerticalSpeed(float di);
	void AimLinePosition(sf::RenderWindow& window, bool isMousePressed);
	bool IsRocketLaunched();
	void SetRocketLaunched(bool launched);

private:
	//surement probleme vitesse de chute pour traverser les pixels transparents
	//patch possible : rectangle entre le climax du saut et le point de reception
	//verifier s'il y a un element qui bloquerait la chute si oui le pdr est au blocage
	const int Speed = 400;
	const float GRAVITY = 981.0f;
	const float JUMP_VELOCITY = -400.0f;
	bool isRocketLaunched;
	sf::RectangleShape worm;
	sf::RectangleShape Health;
	sf::RectangleShape aimLine;
	float verticalSpeed;
	bool onGround;
	Rocket rock;
	void checkCollisionWithGround(const sf::RectangleShape& ground, const sf::Image& groundImage);

};

