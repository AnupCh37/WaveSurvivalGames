#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
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

    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG game", sf::Style::Default, settings);
    window.setFramerateLimit(60);


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
    std::string filename = "levels/l1.csv";
    std::vector<int> level;
    std::ifstream inputFile(filename);
    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            try {

                level.push_back(std::stoi(cell));
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Warning: Invalid integer found in CSV: '" << cell << "'" << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Warning: Integer out of range in CSV: '" << cell << "'" << std::endl;
            }
        }
    }

    inputFile.close();
    if (!tmap.load("Assets/World/Prison/tilesheet.png", { 16, 16 }, level.data(), 50, 38))
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

        window.display();
    }

    return 0;
}