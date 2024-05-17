#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
sf::Font font;
bool isFullscreen = false, isOptions = false;
std::string windowname = "Nom du jeu";
void config() {
    // chemin polie
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

void WindowJeu() {
    // fenetre jeu
    sf::RenderWindow jeuWindow(sf::VideoMode(800, 600), "Jeu");

    // nouvelle fenetre + ancienne fermée
    while (jeuWindow.isOpen())
    {
        sf::Event jeuEvent;
        while (jeuWindow.pollEvent(jeuEvent))
        {
            if (jeuEvent.type == sf::Event::Closed)
                jeuWindow.close();
        }

        jeuWindow.clear(sf::Color::Blue);
        jeuWindow.display();
    }
}

void handleOptions(sf::RenderWindow& window) {
    // Boucle pour l'écran des options
    while (isOptions) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                isOptions = false;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isOptions = false; // Sortir du mode options
            }
        }

        window.clear(sf::Color::Black);

        // Vous pouvez dessiner les éléments de l'écran des options ici
        // Exemple :
        // window.draw(...);

        window.display();
    }
}

int main()
{
    config();

    // fenetre principale
    sf::RenderWindow window(sf::VideoMode(1800, 900), windowname);
    sf::Vector2u windowSize = window.getSize();

    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    sf::Text jouerText("Jouer", font, 40);
    jouerText.setFillColor(sf::Color::Black);
    jouerText.setPosition(330.f, 200.f);
    sf::Text optionsText("Options", font, 40);
    optionsText.setFillColor(sf::Color::Black);
    optionsText.setPosition(300.f, 300.f);
    sf::Text quitterText("Quitter", font, 40);
    quitterText.setFillColor(sf::Color::Black);

    // Rectangles boutons
    sf::RectangleShape jouerButton(sf::Vector2f(200.f, 50.f));
    jouerButton.setFillColor(sf::Color::White);
    sf::RectangleShape optionsButton(sf::Vector2f(250.f, 50.f));
    optionsButton.setFillColor(sf::Color::White);
    sf::RectangleShape quitterButton(sf::Vector2f(300.f, 50.f));
    quitterButton.setFillColor(sf::Color::White);

    // dimensions texte + rectangles
    sf::FloatRect jouerTextBounds = jouerText.getLocalBounds();
    sf::FloatRect optionsTextBounds = optionsText.getLocalBounds();
    sf::FloatRect quitterTextBounds = quitterText.getLocalBounds();
    sf::FloatRect jouerButtonBounds = jouerButton.getLocalBounds();
    sf::FloatRect optionsButtonBounds = optionsButton.getLocalBounds();
    sf::FloatRect quitterButtonBounds = quitterButton.getLocalBounds();

    // calcul position des elements
    float jouerTextPosX = (windowWidth - jouerTextBounds.width) / 2.f;
    float optionsTextPosX = (windowWidth - optionsTextBounds.width) / 2.f;
    float quitterTextPosX = (windowWidth - quitterTextBounds.width) / 2.f;
    float jouerButtonPosX = (windowWidth - jouerButtonBounds.width) / 2.f;
    float optionsButtonPosX = (windowWidth - optionsButtonBounds.width) / 2.f;
    float quitterButtonPosX = (windowWidth - quitterButtonBounds.width) / 2.f;

    // position texte
    jouerText.setPosition(jouerTextPosX, 200.f);
    optionsText.setPosition(optionsTextPosX, 300.f);
    quitterText.setPosition(quitterTextPosX, 400.f);

    // position rectangles
    jouerButton.setPosition(jouerButtonPosX, 200.f);
    optionsButton.setPosition(optionsButtonPosX, 300.f);
    quitterButton.setPosition(quitterButtonPosX, 400.f);

    // boucle jeu
    while (window.isOpen())
    {
        //events
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:

                // clic options
                if (event.mouseButton.button == sf::Mouse::Left &&
                    optionsButton.getGlobalBounds().contains(mousePos))
                {
                    isOptions = true;
                }

                if (event.mouseButton.button == sf::Mouse::Left && jouerButton.getGlobalBounds().contains(mousePos))
                {
                    window.clear();
                    //modifier avec ce que l'on doit utiliser dans le jeu 
                }

                if (event.mouseButton.button == sf::Mouse::Left && quitterButton.getGlobalBounds().contains(mousePos))
                {
                    window.close();
                }
                break;

            case sf::Event::EventType::KeyPressed:
                break;

            case sf::Event::MouseMoved:
                //survole les boutons

                if (jouerButton.getGlobalBounds().contains(mousePos))
                    jouerButton.setFillColor(sf::Color(128, 128, 128)); // Gris moyen
                else
                    jouerButton.setFillColor(sf::Color::White);

                if (optionsButton.getGlobalBounds().contains(mousePos))
                    optionsButton.setFillColor(sf::Color(128, 128, 128)); // Gris moyen
                else
                    optionsButton.setFillColor(sf::Color::White);

                if (quitterButton.getGlobalBounds().contains(mousePos))
                    quitterButton.setFillColor(sf::Color(128, 128, 128)); // Gris moyen
                else
                    quitterButton.setFillColor(sf::Color::White);
                break;
            default:
                break;
            }
        }

        // Efface et dessine la fenêtre
        window.clear(sf::Color::Black);
        if (isOptions) {
            handleOptions(window);
        }
        else {
            window.draw(jouerButton);
            window.draw(optionsButton);
            window.draw(quitterButton);
            window.draw(jouerText);
            window.draw(optionsText);
            window.draw(quitterText);
        }


        window.display();
    }

    return 0;
}