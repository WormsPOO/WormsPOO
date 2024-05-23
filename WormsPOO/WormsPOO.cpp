#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <vector>
#include "menu.h"
#include "Worm.h"
#include "Rocket.h"
#include "Terrain.h"


sf::Font font;
bool isFullscreen = false, isOptions = false, isMousePressed = false, shootRocket = false;
std::string windowname = "Star Worms";
void config() {
    
    
    // chemin police
    std::string fontPath = "C:/Windows/Fonts/arial.ttf";

    // police 
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
    }
}

int main()
{
    config();

    sf::Clock clock; // Horloge pour mesurer le temps écoulé
    sf::Time deltaTime = sf::Time::Zero;
    sf::RenderWindow window(sf::VideoMode(1800, 900), windowname);
    sf::Sprite backgroundSprite;
    sf::Texture gameBackgroundTexture;

    if (!gameBackgroundTexture.loadFromFile("./assets/menu_background.png")) {
        std::cerr << "Erreur lors du chargement du background" << std::endl;
    }
    backgroundSprite.setTexture(gameBackgroundTexture);

    sf::Vector2u windowSize = window.getSize();
    window.setFramerateLimit(60);

    srand(time(NULL));

    std::vector<sf::Vector2f> positions = {
        sf::Vector2f(100.f, windowSize.y - 700.f),
        sf::Vector2f(900.f, windowSize.y - 750.f),
        sf::Vector2f(1400.f, windowSize.y - 850.f),
        sf::Vector2f(150.f, windowSize.y - 280.f),
        sf::Vector2f(1200.f, windowSize.y - 270.f)
    };

    int randomIndex = std::rand() % positions.size();
    sf::Vector2f randomPosition = positions[randomIndex];
    std::cout << "Position aléatoire sélectionnée: (" << randomPosition.x << ", " << randomPosition.y << ")\n";

    Terrain terrain(windowSize);

    Worm worm;
    worm.setPosition(randomPosition, terrain);

    std::vector<Rocket*> rockets;


    Menu menu(window);
    menu.showMenu(window);

    // boucle jeu
    while (window.isOpen())
    {
        deltaTime = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left && !shootRocket) {
                        isMousePressed = true;
                    }
                    break;

                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button == sf::Mouse::Left && isMousePressed) {
                        isMousePressed = false;
                        if (rockets.empty()) {
                            rockets.push_back(worm.shoot(mousePos));
                            shootRocket = true;
                        }
                    }
                    break;

                default:
                    break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            worm.jump();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            worm.move(-deltaTime.asSeconds(), 0, terrain, &window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            worm.move(deltaTime.asSeconds(), 0, terrain, &window);

        if (isMousePressed) {
            worm.aim(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        }

        worm.update(deltaTime.asSeconds(), terrain);

        for (auto rocket = rockets.begin(); rocket != rockets.end(); ) {
            (*rocket)->move(deltaTime.asSeconds());
            if ((*rocket)->isOffScreen(windowSize)) {
                delete* rocket;
                rocket = rockets.erase(rocket);
                shootRocket = false;
            }
            else {
                ++rocket;
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        terrain.draw(window);
        worm.draw(window, isMousePressed);
        for (const auto& rocket : rockets) {
            rocket->draw(window);
        }
        window.display();
    }

    for (auto rocket : rockets) {
        delete rocket;
    }

    return 0;
}

