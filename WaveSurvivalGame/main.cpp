#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "FrameRate.h"
#include <windows.h>
#include "TileMap.h"
#include "Pause.h"
#include "Weapon.h"
#include<array>
bool paused{};

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1216, 800), "RPG game", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    // Load a font (make sure you have a font file in your Assets folder)
    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf")) {
        std::cout << "Failed to load font for pause button\n";
    }

    // Create the pause button rectangle
    sf::Vector2f buttonSize(100, 40);
    sf::RectangleShape pauseButton(buttonSize);
    pauseButton.setFillColor(sf::Color(80, 80, 80));
    pauseButton.setOutlineColor(sf::Color::White);
    pauseButton.setOutlineThickness(2);
    pauseButton.setPosition(window.getSize().x - buttonSize.x - 10, 10);

    // Create the pause button text
    sf::Text pauseText("Pause", font, 22);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(
        pauseButton.getPosition().x + 20,
        pauseButton.getPosition().y + 5
    );

    constexpr std::array level = {
         0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,2,0,0,0,0,0,0,
    0,0,0,2,0,0,0,1,1,1,1,1,0,0,0,0,0,2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,2,0,0,0,
    0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,3,3,
    0,2,0,0,0,0,3,0,0,0,0,2,0,0,0,0,3,0,0,0,0,0,0,0,0,3,0,0,0,0,0,2,0,0,0,3,0,0,
    0,0,0,0,3,3,3,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,3,3,3,0,0,0,
    0,1,0,0,0,0,3,0,0,0,0,1,0,0,0,0,3,0,0,0,0,0,2,0,0,3,0,0,0,1,0,0,0,0,3,0,0,2,
    0,1,1,1,1,0,3,0,0,0,0,1,1,1,1,0,3,0,0,0,0,1,1,1,1,3,0,0,0,1,1,1,1,0,3,0,0,0,
    0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,3,2,0,0,
    0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,3,0,0,0,
    2,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,
    0,0,0,2,0,0,3,0,0,3,0,0,0,2,0,0,3,0,0,3,0,0,0,0,2,3,0,0,3,0,0,0,2,0,3,0,0,3,
    0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,3,0,0,3,0,0,0,0,0,3,0,0,3,
    0,0,0,0,1,1,3,0,0,3,1,1,0,0,0,0,3,0,0,3,1,1,0,0,0,3,0,0,3,1,1,0,0,0,3,0,0,3,
    0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,0,3,0,0,3,0,0,0,0,0,3,0,0,3,0,0,0,0,0,3,0,0,3,
    0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,
    0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    3,3,3,3,0,0,0,0,3,3,3,3,0,0,0,0,3,3,3,3,0,0,0,0,3,3,3,3,0,0,0,0,3,3,3,3,0,0,
    0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,3,0,
    0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,
    1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,
    0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,3,3,3,3,0,0,0,0,3,3,3,3,0,0,0,0,3,3,3,3,0,
    0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };

    std::cout << "Hello I am making a game" << std::endl;

    std::vector<sf::RectangleShape> bullets;
    Weapon weapon;
    FrameRate framRate;
    Enemy enemy;
    Player player;
    TileMap tmap;
    Pause pausegame;


    player.Initialize();
    weapon.Initialize();
    enemy.Initialize();


    weapon.Initialize();
    player.load();
    enemy.Load();
    weapon.load();



    if (!tmap.load("Assets/World/Prison/tilesetmap.png", { 32, 32 }, level.data(), 38, 25))
        return -1;


    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                paused = !paused;
                sf::sleep(sf::milliseconds(200));
            }
        }

        // Pause button click handling
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (pauseButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                paused = !paused;
                sf::sleep(sf::milliseconds(200)); // debounce
            }
        }

        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0;

        if (!paused) {
            enemy.Update(deltaTime, player.psprite.getPosition());
            player.Update(deltaTime, enemy, window);
            weapon.Update(deltaTime);
        }

        pausegame.Update(deltaTime, window);

        window.clear(sf::Color::Black);
        window.draw(tmap);
        player.Draw(deltaTime, window);
        enemy.Draw(window);

        weapon.drawBullets(window);

        window.draw(pauseButton);
        window.draw(pauseText);

        window.display();
    }

    return 0;
}
