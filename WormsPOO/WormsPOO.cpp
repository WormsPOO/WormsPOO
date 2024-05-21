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

//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <string>
//#include <cmath>
//#include "Worms.h"
//
//// Configuration
//sf::Font font;
//bool isFullscreen = false, isOptions = false;
//const float VITESSE_ROQUETTE = 500.0f; // Vitesse de déplacement de la roquette
//const float RADIUS_IMPACT = 50.0f; // Rayon d'impact pour la roquette
//std::string windowname = "Nom du jeu"; // Nom de la fenêtre du jeu
//sf::Image plafondImage; // Image pour le plafond
//
//
//// Fonction de configuration pour charger la police
//void config() {
//    std::string fontPath = "C:/Windows/Fonts/arial.ttf"; // Chemin vers la police Arial
//
//    if (!font.loadFromFile(fontPath)) {
//        std::cerr << "Erreur lors du chargement de la police." << std::endl; // Message d'erreur si le chargement échoue
//    }
//}
//
//// Fonction pour détruire une zone circulaire dans une image
//void detruireZone(sf::Image& image, const sf::Vector2f& impactPosition, float radius) {
//    // Calcul des limites du rectangle entourant la zone à détruire
//    int left = static_cast<int>(std::max(0.f, impactPosition.x - radius));
//    int top = static_cast<int>(std::max(0.f, impactPosition.y - radius));
//    int right = static_cast<int>(std::min(static_cast<float>(image.getSize().x), impactPosition.x + radius));
//    int bottom = static_cast<int>(std::min(static_cast<float>(image.getSize().y), impactPosition.y + radius));
//
//    // Parcours des pixels dans la zone de destruction
//    for (int x = left; x < right; ++x) {
//        for (int y = top; y < bottom; ++y) {
//            // Calcul de la distance entre le pixel et le centre de l'impact
//            float distance = std::sqrt((x - impactPosition.x) * (x - impactPosition.x) + (y - impactPosition.y) * (y - impactPosition.y));
//            if (distance <= radius) {
//                image.setPixel(x, y, sf::Color::Transparent); // Rendre le pixel transparent si dans le rayon
//            }
//        }
//    }
//}
//
//int main() {
//    config(); // Charger la police
//    sf::Clock clock; // Horloge pour mesurer le temps écoulé
//    sf::Time dureeIteration = sf::Time::Zero;
//    // Création de la fenêtre principale
//    sf::RenderWindow window(sf::VideoMode(1800, 900), windowname);
//    sf::Vector2u windowSize = window.getSize();
//    window.setFramerateLimit(60); // Limite de fréquence d'images
//
//    Worms worms;
//    worms.setPosition(sf::Vector2f(100.f, windowSize.y - 100.f));
//
//    // Création de la roquette
//    sf::RectangleShape roquette(sf::Vector2f(50.f, 5.f));
//    sf::Texture t;
//    if (!t.loadFromFile("C:/Users/bryan/source/repos/Jeu/TestJeu/Image/Rocket.png")) {
//        std::cerr << "Erreur lors du chargement de la texture de la roquette." << std::endl;
//    }
//    roquette.setSize(sf::Vector2f(80.f, 80.f));
//    roquette.setTexture(&t);
//    bool tirerRoquette = false; // Indicateur de tir de la roquette
//    sf::Vector2f posRoquette;
//    sf::Vector2f directionRoquette; // Direction de la roquette
//
//    // Création du sol
//    sf::RectangleShape sol(sf::Vector2f(windowSize.x, 50.f));
//    sol.setPosition(0, windowSize.y - 50.f);
//    sol.setFillColor(sf::Color(100, 100, 100)); // Couleur grise
//    // Création de l'image du sol et chargement de la texture
//    sf::Image solImage;
//    solImage.create(windowSize.x, 50, sf::Color(100, 100, 100)); // Créez l'image du sol
//    sf::Texture solTexture;
//    if (!solTexture.loadFromImage(solImage)) {
//        std::cerr << "Erreur lors du chargement de la texture du sol à partir de l'image." << std::endl;
//        return -1;
//    }
//    sol.setTexture(&solTexture);
//
//    // Création du plafond
//    sf::RectangleShape plafond(sf::Vector2f(windowSize.x, 50.f));
//    plafond.setPosition(0, 0);
//
//    // Création de l'image du plafond et chargement de la texture
//    plafondImage.create(windowSize.x, 50, sf::Color(100, 100, 100)); // Créez l'image du plafond
//    sf::Texture plafondTexture;
//    if (!plafondTexture.loadFromImage(plafondImage)) {
//        std::cerr << "Erreur lors du chargement de la texture du plafond à partir de l'image." << std::endl;
//        return -1;
//    }
//    plafond.setTexture(&plafondTexture);
//
//    bool isMousePressed = false; // Indicateur de clic de souris
//
//    // Boucle principale du jeu
//    while (window.isOpen()) {
//        dureeIteration = clock.restart(); // Temps écoulé depuis la dernière frame
//
//        // Gestion des événements
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//            switch (event.type) {
//            case sf::Event::Closed:
//                window.close();
//                break;
//
//            case sf::Event::MouseButtonPressed:
//                if (event.mouseButton.button == sf::Mouse::Left && worms.IsRocketLaunched()) {
//                    isMousePressed = true;
//                }
//                break;
//
//            case sf::Event::MouseButtonReleased:
//                if (event.mouseButton.button == sf::Mouse::Left && isMousePressed) {
//                    // Position de départ de la roquette basée sur la position de la souris
//                    posRoquette = worms.GetPosition() + sf::Vector2f(worms.GetSize().x / 2.f, worms.GetSize().y / 2.f);
//                    roquette.setPosition(posRoquette);
//
//                    sf::Vector2f centerWorms = worms.GetPosition() + sf::Vector2f(worms.GetSize().x / 2.f, worms.GetSize().y / 2.f);
//                    directionRoquette = mousePos - centerWorms;
//                    float length = std::sqrt(directionRoquette.x * directionRoquette.x + directionRoquette.y * directionRoquette.y);
//                    directionRoquette /= length; // Normalisation de la direction
//
//                    worms.SetRocketLaunched(true);
//                    isMousePressed = false;
//                }
//                break;
//
//            default:
//                break;
//            }
//        }
//        // Gestion de la gravité
//        worms.applyGravity(dureeIteration.asSeconds(), sol, solImage);
//
//        // Gestion du saut
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
//            worms.jump();
//        }
//        float deltaTime = clock.restart().asSeconds();
//
//
//        // Déplacement de la roquette
//        if (tirerRoquette) {
//            if (directionRoquette != sf::Vector2f(0.f, 0.f)) {
//                roquette.move(directionRoquette * VITESSE_ROQUETTE * dureeIteration.asSeconds());
//
//                // Vérifiez si la roquette a touché le plafond
//                if (roquette.getGlobalBounds().intersects(plafond.getGlobalBounds())) {
//                    sf::Vector2f impactPosition = roquette.getPosition() - plafond.getPosition();
//                    detruireZone(plafondImage, impactPosition, RADIUS_IMPACT);
//
//                    if (!plafondTexture.loadFromImage(plafondImage)) {
//                        std::cerr << "Erreur lors de la mise à jour de la texture du plafond après destruction." << std::endl;
//                    }
//                    plafond.setTexture(&plafondTexture);
//
//                    tirerRoquette = false;
//                }
//                // Vérifiez si la roquette a touché le sol
//                else if (roquette.getGlobalBounds().intersects(sol.getGlobalBounds())) {
//                    sf::Vector2f impactPosition = roquette.getPosition() - sol.getPosition();
//                    detruireZone(solImage, impactPosition, RADIUS_IMPACT);
//
//                    if (!solTexture.loadFromImage(solImage)) {
//                        std::cerr << "Erreur lors de la mise à jour de la texture du sol après destruction." << std::endl;
//                    }
//                    sol.setTexture(&solTexture);
//
//                    tirerRoquette = false;
//                }
//                // Vérifiez si la roquette a quitté les limites de la fenêtre
//                else if (roquette.getPosition().x < 0 || roquette.getPosition().x > windowSize.x ||
//                    roquette.getPosition().y < 0 || roquette.getPosition().y > windowSize.y) {
//                    tirerRoquette = false;
//                }
//            }
//        }
//
//        // Déplacement du personnage avec les touches Q, D
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
//            worms.move(-dureeIteration.asSeconds(), 0);
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//            worms.move(dureeIteration.asSeconds(), 0);
//
//        // Mise à jour de la ligne de visée si le bouton de la souris est enfoncé
//        worms.AimLinePosition(window, isMousePressed);
//
//        // Effacer et dessiner la fenêtre
//        window.clear(sf::Color::White);
//        worms.draw(window, isMousePressed);
//        if (tirerRoquette) {
//            window.draw(roquette);
//        }
//        window.draw(sol);
//        window.draw(plafond);
//        window.display();
//    }
//
//    return 0;
//}
