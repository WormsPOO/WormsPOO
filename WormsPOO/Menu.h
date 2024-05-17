#pragma once
class Menu
{
public:
    Menu(sf::RenderWindow& window) {
        isMenuActive = true;

		//creations des textures
		sf::Vector2u windowSize = window.getSize();

        if (!playButtonTexture.loadFromFile("./assets/playbutton.png") || !optionsButtonTexture.loadFromFile("./assets/optionsbutton.png") || !quitButtonTexture.loadFromFile("./assets/quitbutton.png")) {
			std::cerr << "Erreur lors du chargement de la feuille des boutons" << std::endl;
		}
        if (!backgroundTexture.loadFromFile("./assets/menu_background.png")) {
			std::cerr << "Erreur lors du chargement du background" << std::endl;
		}
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "Erreur lors du chargement de la police" << std::endl;
        }
        if (!onbuttonTexture.loadFromFile("./assets/onbutton.png") || !offbuttonTexture.loadFromFile("./assets/offbutton.png")) {
            std::cerr << "Erreur lors des boutons ON/OFF" << std::endl;
        }

        float windowWidth = static_cast<float>(windowSize.x);
        float windowHeight = static_cast<float>(windowSize.y);

        backgroundSprite.setTexture(backgroundTexture);

        playButton.setTexture(playButtonTexture);
        playButton.setTextureRect(sf::IntRect(0, 0, 300, 125));
        float playButtonPosX = (windowWidth - playButton.getGlobalBounds().width) / 2.f;
        playButton.setPosition(playButtonPosX, 200.f);

        optionsButton.setTexture(optionsButtonTexture);
        optionsButton.setTextureRect(sf::IntRect(0, 0, 300, 125));
        float optionsButtonPosX = (windowWidth - optionsButton.getGlobalBounds().width) / 2.f;
        optionsButton.setPosition(optionsButtonPosX, 400.f);

        quitButton.setTexture(quitButtonTexture);
        quitButton.setTextureRect(sf::IntRect(0, 0, 300, 125)); 
        float quitButtonPosX = (windowWidth - quitButton.getGlobalBounds().width) / 2.f;
        quitButton.setPosition(quitButtonPosX, 600.f);

        fullscreenButton.setTexture(offbuttonTexture);
        fullscreenButton.setTextureRect(sf::IntRect(0, 0, 300, 125)); 
        float fullscreenButtonPosX = (windowWidth - playButton.getGlobalBounds().width) / 2.f;
        fullscreenButton.setPosition(fullscreenButtonPosX, 200.f);
	}
    void showMenu(sf::RenderWindow& window) {
		// Boucle jeu
        while (window.isOpen() && isMenuActive)
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
                        if (event.mouseButton.button == sf::Mouse::Left && optionsButton.getGlobalBounds().contains(mousePos))
                        {
                            isOptions = true;
                        }

                        if (event.mouseButton.button == sf::Mouse::Left && playButton.getGlobalBounds().contains(mousePos))
                        {
                            std::cout << "Fin du menu" << std::endl;
                            isMenuActive = false;
                        }

                        if (event.mouseButton.button == sf::Mouse::Left && quitButton.getGlobalBounds().contains(mousePos))
                        {
                            window.close();
                        }
                        break;

                    case sf::Event::EventType::KeyPressed:
                        break;


                    default:
                        break;
                }
            }

            // Efface et dessine la fenêtre
            window.clear(sf::Color::Black);
            if (isOptions) {
                showOptions(window);
            }
            else {
                window.draw(backgroundSprite);
                window.draw(playButton);
                window.draw(optionsButton);
                window.draw(quitButton);
            }

            window.display();
        }
        std::cout << "Fin du menu" << std::endl;
	}   
    void showOptions(sf::RenderWindow& window) {
        text.setFont(font); // Définir la police
        text.setString("MENU OPTIONS"); // Définir le texte
        text.setCharacterSize(50); // Définir la taille des caractères
        text.setFillColor(sf::Color::Black);
        text.setPosition((window.getSize().x - text.getLocalBounds().width) / 2, 50.f);

        // Boucle pour l'écran des options
        while (isOptions) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    isOptions = false;
                }
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                switch (event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::MouseButtonPressed:

                        // clic options
                        if (event.mouseButton.button == sf::Mouse::Left && fullscreenButton.getGlobalBounds().contains(mousePos))
                        {
                            isOptions = true;
                        }
                        break;

                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape) {
                            isOptions = false; // Sortir du mode options
                        }
                        break;


                    default:
                        break;
                }
            }

            window.clear(sf::Color::Black);

            // Vous pouvez dessiner les éléments de l'écran des options ici
            // Exemple :
            // window.draw(...);
            window.draw(backgroundSprite);
            window.draw(text);
            window.draw(fullscreenButton);

            window.display();
        }
    }
    private:
        bool isOptions = false;
        sf::Texture playButtonTexture;
        sf::Texture optionsButtonTexture;
        sf::Texture quitButtonTexture;
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        sf::Sprite playButton;
        sf::Sprite optionsButton;
        sf::Sprite quitButton;
        sf::Sprite fullscreenButton;
        bool isMenuActive;
        sf::Font font;
        sf::Text text;
        sf::Texture onbuttonTexture;
        sf::Texture offbuttonTexture;
};

