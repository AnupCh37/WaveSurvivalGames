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
#include "WaveManager.h"
#include "Menu.h"
#include <cmath>

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

std::vector<int> loadCSVFile(const std::string& filename)
{
    std::vector<int> tileData;
    std::ifstream inputFile(filename);
    std::string line;

    if (!inputFile.is_open()) return tileData;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            tileData.push_back(std::stoi(cell));
        }
    }
    inputFile.close();
    return tileData;
}

// Function to reset the game to initial state
void resetGame(Player& player, WaveManager& waveManager, std::vector<Enemy>& enemies,
    Sound* soundSystem, sf::Clock& gameTimer) {
    // Reset player
    player = Player();
    player.Load();
    player.soundSystem = soundSystem;

    // Reset wave manager
    waveManager = WaveManager(soundSystem);

    // Clear and reset enemies
    enemies.clear();
    waveManager.spawnWave(enemies, 1);
    for (auto& enemy : enemies) {
        enemy.soundSystem = soundSystem;
    }

    // Reset pause state and game timer
    paused = false;
    gameTimer.restart();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Wave Survival Game", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0, 0, 800, 600));
    window.setView(view);

    std::cout << "Wave Survival Game Starting..." << std::endl;

    // Game state management
    MenuState gameState = MenuState::INTRO_MENU;
    Menu gameMenu;

    // Game systems
    FrameRate framRate;
    Player player;
    TileMap backgroundLayer;
    TileMap foregroundLayer;
    Pause pausegame;
    Music music;
    Sound soundEffects;
    WaveManager waveManager(&soundEffects);
    std::vector<Enemy> enemies;

    // Game tracking
    sf::Clock gameTimer;
    int enemiesKilledCount = 0;

    // Initialize menu and load sounds
    gameMenu.Load();

    player.soundSystem = &soundEffects;
    soundEffects.loadSound("arrowShoot", "Assets/Sounds/arrow_shoot.ogg");
    soundEffects.loadSound("playerWalk", "Assets/Sounds/footsteps.ogg");
    soundEffects.loadSound("playerHurt", "Assets/Sounds/player_hurt.ogg");
    soundEffects.loadSound("playerDeath", "Assets/Sounds/player_death.ogg");
    soundEffects.loadSound("axeHit", "Assets/Sounds/axe_hit.ogg");

    // Load UI font
    sf::Font font;
    if (!font.loadFromFile("Assets/Fonts/OldLondon.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }

    sf::Text waveText;
    waveText.setFont(font);
    waveText.setCharacterSize(50);
    waveText.setFillColor(sf::Color::White);
    waveText.setStyle(sf::Text::Bold);
    sf::RectangleShape textBackground;
    textBackground.setFillColor(sf::Color(0, 0, 0, 150));

    // Initialize game objects (including initial player setup)
    framRate.Load();
    player.Load();
    pausegame.Load();

    // Initialize enemies for the first time (so player texture loads properly)
    waveManager.spawnWave(enemies, 1);
    for (auto& enemy : enemies) {
        enemy.soundSystem = &soundEffects;
    }

    // Load level data
    std::string backgroundFile = "levels/l1_background.csv";
    std::string foregroundFile = "levels/l1_foreground.csv";

    const int tilew = 16;
    const int tileh = 16;
    const int mapw = 50;
    const int maph = 38;

    std::vector<int> backgroundData = loadCSVFile(backgroundFile);
    std::vector<int> foregroundData = loadCSVFile(foregroundFile);

    if (backgroundData.empty())
        backgroundData = loadCSVFile("levels/l1.csv");

    // Load music
    if (music.load("Assets/GameMusic/gameloop.ogg"))
        music.play(true);
    else
        std::cout << "Music file cannot be loaded." << std::endl;

    // Load tile maps
    if (!backgroundLayer.load("Assets/World/Prison/tilesheet.png", { tilew, tileh }, backgroundData.data(), mapw, maph))
        return -1;

    if (!foregroundData.empty()) {
        if (!foregroundLayer.load("Assets/World/Prison/tilesheet.png", { tilew, tileh }, foregroundData.data(), mapw, maph))
            return -1;
    }

    sf::Clock clock;

    // Main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle escape key based on game state
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (gameState == MenuState::PLAYING) {
                    paused = !paused;
                    gameState = paused ? MenuState::PAUSED : MenuState::PLAYING;
                }
                else if (gameState == MenuState::PAUSED) {
                    paused = false;
                    gameState = MenuState::PLAYING;
                }
            }

            if (event.type == sf::Event::Resized) {
                view = getLetterboxView(sf::View(sf::FloatRect(0, 0, 800, 600)), event.size.width, event.size.height);
                window.setView(view);
            }
        }

        sf::Time deltaTimeTimer = clock.restart();
        float deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0f;

        // Update based on game state
        switch (gameState) {
        case MenuState::INTRO_MENU:
        case MenuState::GAME_OVER:
            gameMenu.Update(deltaTime, window, gameState);

            // Reset game when transitioning to PLAYING state
            if (gameState == MenuState::PLAYING) {
                resetGame(player, waveManager, enemies, &soundEffects, gameTimer);

                // Force reload player texture to fix white box issue
                player.Load(); // Call Load again to ensure texture is properly set

                enemiesKilledCount = 0;

                // Reset enemy tracking variables
                static int totalEnemiesSpawned = 0;
                static int currentWaveEnemies = 0;
                totalEnemiesSpawned = enemies.size(); // Initial enemies from wave 1
                currentWaveEnemies = 1;
            }
            break;

        case MenuState::PLAYING:
            if (!paused) {
                // Update wave manager
                waveManager.Update(enemies);

                // Count killed enemies (total killed, not just current dead ones)
                static int totalEnemiesSpawned = 0;
                static int currentWaveEnemies = 0;

                // Track when new wave spawns
                if (waveManager.getCurrentWave() > currentWaveEnemies) {
                    totalEnemiesSpawned += enemies.size();
                    currentWaveEnemies = waveManager.getCurrentWave();
                }

                // Count currently alive enemies
                int aliveEnemies = 0;
                for (const auto& enemy : enemies) {
                    if (enemy.getHealth() > 0) {
                        aliveEnemies++;
                    }
                }

                // Calculate total killed
                enemiesKilledCount = totalEnemiesSpawned - aliveEnemies;

                // Update game objects
                for (auto& enemy : enemies) {
                    enemy.Update(deltaTime, player.psprite.getPosition(), player, backgroundData);
                }

                player.Update(deltaTime, enemies, window, backgroundData, waveManager.getPlayerSpeed());
                framRate.Update(deltaTime);

                // Check for game over condition (player death)
                if (player.getHealth() <= 0) {
                    gameState = MenuState::GAME_OVER;
                    int survivalTime = static_cast<int>(gameTimer.getElapsedTime().asSeconds());
                    int wavesSurvived = waveManager.getCurrentWave() - 1;
                    gameMenu.setGameOverStats(survivalTime, wavesSurvived, enemiesKilledCount);
                }
            }
            break;

        case MenuState::PAUSED:
            pausegame.Update(deltaTime, window);
            break;
        }

        // Rendering
        window.setView(view);
        window.clear();

        // Always draw the game background when in game states
        if (gameState == MenuState::PLAYING || gameState == MenuState::PAUSED) {
            window.draw(backgroundLayer);

            // Draw game objects
            for (size_t i = 0; i < enemies.size(); i++) {
                enemies[i].Draw(window);
            }

            player.Draw(deltaTime, window);

            if (!foregroundData.empty())
                window.draw(foregroundLayer);

            // Draw wave transition text if wave is loading
            if (waveManager.isWaveLoading()) {
                float timeRemaining = waveManager.getTimeRemaining();
                int nextWave = waveManager.getCurrentWave();

                std::string waveMessage = "Wave " + std::to_string(nextWave + 1) + " starting in " +
                    std::to_string((int)std::ceil(timeRemaining)) + " seconds...";

                waveText.setString(waveMessage);

                // Center the text on screen
                sf::FloatRect textBounds = waveText.getLocalBounds();
                waveText.setPosition(
                    (800 - textBounds.width) / 2.0f,
                    (600 - textBounds.height) / 2.0f
                );

                textBackground.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20));
                textBackground.setPosition(
                    waveText.getPosition().x - 10,
                    waveText.getPosition().y - 10
                );

                // Draw background and text
                window.draw(textBackground);
                window.draw(waveText);
            }

            framRate.Draw(window);

            // Draw pause overlay if paused
            if (gameState == MenuState::PAUSED) {
                pausegame.Draw(window);
            }
        }

        // Draw menus
        if (gameState == MenuState::INTRO_MENU || gameState == MenuState::GAME_OVER) {
            // Draw game background dimmed for menu overlay
            if (gameState == MenuState::GAME_OVER) {
                window.draw(backgroundLayer);
                for (size_t i = 0; i < enemies.size(); i++) {
                    enemies[i].Draw(window);
                }
                player.Draw(deltaTime, window);
                if (!foregroundData.empty())
                    window.draw(foregroundLayer);
            }

            gameMenu.Draw(window, gameState);
        }

        window.display();
    }

    music.stop();
    return 0;
}