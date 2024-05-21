#include "Rocket.h"
#include <iostream>

Rocket::Rocket() {
	roquette.setSize(sf::Vector2f(50.f, 5.f));
	sf::Texture t;
	if (!t.loadFromFile("C:/Users/bryan/source/repos/Jeu/TestJeu/Image/Rocket.png")) {
		std::cerr << "Erreur lors du chargement de la texture de la roquette." << std::endl;
	}
	roquette.setSize(sf::Vector2f(80.f, 80.f));
	roquette.setTexture(&t);
}

Rocket::~Rocket() {
}

void Rocket::Draw(sf::RenderWindow& w)
{
	w.draw(roquette);
}

void Rocket::setPosition(const sf::Vector2f& position)
{


}

void Rocket::move(const sf::Vector2f& offset)
{
}

//const sf::RectangleShape& Rocket::getShape() const
//{
//	// TODO: insérer une instruction return ici
//}

bool Rocket::checkCollision(const Platform& platform)
{
	return false;
}



