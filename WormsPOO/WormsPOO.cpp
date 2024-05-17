#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "menu.h"


sf::Font font;
bool isFullscreen = false, isOptions = false;
std::string windowname = "Star Worms";
void config() {
    // chemin police
    std::string fontPath = "C:/Windows/Fonts/arial.ttf";

    // police 
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
    }
}

void Fullscreen(sf::RenderWindow& window) {
    isFullscreen = !isFullscreen;
    window.close();
    if (isFullscreen)
        window.create(sf::VideoMode::getFullscreenModes()[0], windowname, sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(800, 600), windowname);
}

int main()
{
    config();

    // fenetre principale
    sf::RenderWindow window(sf::VideoMode(1800, 900), windowname);
    Menu menu(window);
    menu.showMenu(window);
    window.close();

    // boucle jeu
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

        }
        window.clear();
        // Dessiner les éléments du jeu
        window.display();
    }

    return 0;
}