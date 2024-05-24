#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <sstream>
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
    sf::Clock turnClock;
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

    int randomIndex1 = std::rand() % positions.size();
    sf::Vector2f randomPosition1 = positions[randomIndex1];

    positions.erase(positions.begin() + randomIndex1); 

    int randomIndex2 = std::rand() % positions.size();
    sf::Vector2f randomPosition2 = positions[randomIndex2];

    Terrain terrain(windowSize);

    Worm worm1;
    worm1.setPosition(randomPosition1, terrain);

    Worm worm2;
    worm2.setPosition(randomPosition2, terrain);

    std::vector<Rocket*> rockets;


    Menu menu(window);
    menu.showMenu(window);

    bool turnWorm1 = true;
    const float turnDuration = 10.0f;

    sf::Text turnTimerText; //A METTRE DANS LA CLASSE OVERLAY
    turnTimerText.setFont(font);
    turnTimerText.setCharacterSize(24);
    turnTimerText.setFillColor(sf::Color::Black);
    turnTimerText.setPosition(10.f, 10.f);


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
                            if (turnWorm1) {
                                rockets.push_back(worm1.shoot(mousePos));
                            }
                            else {
                                rockets.push_back(worm2.shoot(mousePos));
                            }
                            shootRocket = true;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        float elapsedTurnTime = turnClock.getElapsedTime().asSeconds();
        float remainingTime = turnDuration - elapsedTurnTime;
        if (remainingTime <= 0) {
            turnWorm1 = !turnWorm1;
            turnClock.restart();
            remainingTime = turnDuration;
        }

        std::ostringstream ss; //CA AUSSI DANS OVERLAY
        ss << std::fixed << std::setprecision(1) << remainingTime;
        turnTimerText.setString("Temps restant: " + ss.str() + "s");

        if (turnWorm1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                worm1.jump();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                worm1.move(-deltaTime.asSeconds(), 0, terrain, &window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                worm1.move(deltaTime.asSeconds(), 0, terrain, &window);

            if (isMousePressed) {
                worm1.aim(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            }

            worm1.update(deltaTime.asSeconds(), terrain);
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                worm2.jump();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                worm2.move(-deltaTime.asSeconds(), 0, terrain, &window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                worm2.move(deltaTime.asSeconds(), 0, terrain, &window);

            if (isMousePressed) {
                worm2.aim(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            }

            worm2.update(deltaTime.asSeconds(), terrain);
        }

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
        worm1.draw(window, turnWorm1 && isMousePressed);
        worm2.draw(window, !turnWorm1 && isMousePressed);
        for (const auto& rocket : rockets) {
            rocket->draw(window);
        }
        window.draw(turnTimerText);
        window.display();
    }

    for (auto rocket : rockets) {
        delete rocket;
    }

    return 0;
}

