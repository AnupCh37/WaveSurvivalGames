#define _USE_MATH_DEFINES 
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
#include <array>
#include "Music.h"
#include "Sound.h" 

bool paused{};

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{
    float windowRatio = windowWidth / (float)windowHeight;
    float viewRatio = view.getSize().x / view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    if (horizontalSpacing)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }
    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    return view;
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG game", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    std::cout << "Hello I am making a game" << std::endl;

    FrameRate framRate;
    std::vector<Enemy> enemies;

  
    Enemy enemy1;
    enemy1.Load({ 100.0f, 100.0f });
    enemies.push_back(enemy1);

    Enemy enemy2;
    enemy2.Load({ 300.0f, 200.0f });
    enemies.push_back(enemy2);

    Player player;
    TileMap tmap;
    Pause pausegame;
    Music music;
    Sound soundEffects;

    player.soundSystem = &soundEffects;
    for (auto& enemy : enemies) {
        enemy.soundSystem = &soundEffects;
    }

 
    soundEffects.loadSound("arrowShoot", "Assets/Sounds/arrow_shoot.ogg");
    soundEffects.loadSound("playerWalk", "Assets/Sounds/footsteps.ogg");
    soundEffects.loadSound("playerHurt", "Assets/Sounds/player_hurt.ogg");
    soundEffects.loadSound("playerDeath", "Assets/Sounds/player_death.ogg");
    soundEffects.loadSound("axeHit", "Assets/Sounds/axe_hit.ogg");

  
    framRate.Load();
    player.Load();
    pausegame.Load();

    std::string filename = "levels/l1.csv";
    std::vector<int> level;

    const int tilew = 16;
    const int tileh = 16;
    const int mapw = 50;
    const int maph = 38;

    std::ifstream inputFile(filename);
    std::string line;
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open CSV file: " << filename << std::endl;
        return -1;
    }

    if (music.load("Assets/GameMusic/gameloop.ogg")) { 
        music.play(true);
    }
    else {
        std::cout << "Music file cannot be loaded." << std::endl;
    }

    // Parse CSV file
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            try {
                level.push_back(std::stoi(cell));
            }
            catch (const std::invalid_argument&) {
                std::cerr << "Warning: Invalid integer found in CSV: '" << cell << "'" << std::endl;
            }
            catch (const std::out_of_range&) {
                std::cerr << "Warning: Integer out of range in CSV: '" << cell << "'" << std::endl;
            }
        }
    }
    inputFile.close();

    if (!tmap.load("Assets/World/Prison/tilesheet.png", { tilew, tileh }, level.data(), mapw, maph))
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
            if (event.type == sf::Event::Resized)
            {
                view = getLetterboxView(sf::View(sf::FloatRect(0, 0, 800, 600)), event.size.width, event.size.height);
                window.setView(view);
            }
        }

        sf::Time deltaTimeTimer = clock.restart();
        float deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0f;

        if (!paused) {
            
            for (auto& enemy_obj : enemies) {
                enemy_obj.Update(deltaTime, player.psprite.getPosition(), player, level);
            }
            player.Update(deltaTime, enemies, window, level);
            framRate.Update(deltaTime);
        }

        pausegame.Update(deltaTime, window);
        window.setView(view);

        
        window.clear();
        window.draw(tmap);

        
        for (auto& enemy_obj : enemies) {
            enemy_obj.Draw(window);
        }

        player.Draw(deltaTime, window);
        framRate.Draw(window);

        if (paused) {
            pausegame.Draw(window);
        }

        window.display();
    }

    music.stop();
    return 0;
} 
