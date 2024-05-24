#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <sstream>

class Overlay
{
public:
	Overlay(sf::Font* font) {
        turnTimerText.setFont(*font);
        turnTimerText.setCharacterSize(24);
        turnTimerText.setFillColor(sf::Color::Black);
        turnTimerText.setPosition(10.f, 10.f);
	}
    sf::Text getTimerText(float remainingTime) {
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(1) << remainingTime;
        turnTimerText.setString("Temps restant: " + ss.str() + "s");

        return turnTimerText;
    }
    void draw(float remaningTime, sf::RenderWindow* window) {
        window->draw(getTimerText(remaningTime));
    }
private:
    sf::Text turnTimerText;
};

