#pragma once
class Rocket
{
public:
	Rocket() {
		if (!texture.loadFromFile("./assets/rocket.png")) {
			std::cerr << "Erreur lors du chargement de la texture de la roquette" << std::endl;
		}
		sprite.setTexture(texture);
		sprite.setScale(0.1f, 0.1f);
		sprite.setTextureRect(sf::IntRect(0, 0, 500, 500));

		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
	}
	void setPosition(const sf::Vector2f& pos) {
		sprite.setPosition(pos);
	}
	void setDirection(const sf::Vector2f& dir) {
		direction = dir;
		float angle = std::atan2(dir.y, dir.x) * 180.f / 3.14159f + 45.f;
		sprite.setRotation(angle);
	}
	void move(float deltaTime) {
		sprite.move(direction * speed * deltaTime);
	}
	void draw(sf::RenderWindow& window) const {
		window.draw(sprite);
	}
	bool isOffScreen(sf::Vector2u windowSize) const {
		sf::Vector2f position = sprite.getPosition();
		return (position.x < 0 || position.x > windowSize.x || position.y < 0 || position.y > windowSize.y);
	}
private:
	const float RADIUS_IMPACT = 30.0f;
	const float speed = 700.0f;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	sf::Vector2f direction;
};

