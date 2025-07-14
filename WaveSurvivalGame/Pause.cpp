#include "Pause.h"
#include <iostream>

Pause::Pause() : isPaused(false)
{
    pauseText.setCharacterSize(30);
}

Pause::~Pause() {

}

void Pause::Draw(sf::RenderWindow& window) {
    window.draw(pauseButton);
    window.draw(pauseText);
}

void Pause::load()
{
    if (!font.loadFromFile("C://Users//anup3//OneDrive//Desktop//rpg game//assets//Fonts//arial.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }
    else {
        std::cout << "Pause text loaded successfully" << std::endl;
    }

    pauseButton.setSize(sf::Vector2f{ 100.f, 50.f });
    pauseButton.setPosition(sf::Vector2f{ 10.f, 10.f });
    pauseButton.setFillColor(sf::Color::Blue);

    pauseText.setFont(font);
    pauseText.setString("Pause");
    pauseText.setCharacterSize(20);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(sf::Vector2f{ 20.f, 15.f });
}

void Pause::Update(float deltaTime, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (pauseButton.getGlobalBounds().contains(worldPos)) {
            isPaused = !isPaused;
            sf::sleep(sf::milliseconds(200));
        }
    }
}
