#pragma once
class Rocket
{
public:
	Rocket() {
		if (!texture.loadFromFile("./assets/rocket.png")) {
			std::cerr << "Erreur lors du chargement de la texture de la roquette" << std::endl;
		}
		sprite.setTexture(texture);
		sprite.setScale(0.5f, 0.5f);
		sprite.setTextureRect(sf::IntRect(0, 0, 500, 500));
	}
	void setPosition(const sf::Vector2f& pos) {
		sprite.setPosition(pos);
	}

	void setDirection(const sf::Vector2f& dir) {
		direction = dir;
	}

	void move(float deltaTime) {
		sprite.move(direction * speed * deltaTime);
	}

	void draw(sf::RenderWindow& window) const {
		window.draw(sprite);
	}
private:
	const float RADIUS_IMPACT = 30.0f;
	const float speed = 700.0f;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	sf::Vector2f direction;
};

