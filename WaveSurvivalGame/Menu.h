#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class MenuState {
    INTRO_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Menu {
public:
    Menu();
    ~Menu();

    void Load();
    void Update(float deltaTime, sf::RenderWindow& window, MenuState& gameState);
    void Draw(sf::RenderWindow& window, MenuState gameState);

    void setGameOverStats(int survivedTime, int wavesSurvived, int enemiesKilled);

private:
    // Fonts and textures
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Intro Menu
    sf::Text titleText;
    sf::Text playButtonText;
    sf::Text exitButtonText;
    sf::RectangleShape playButton;
    sf::RectangleShape exitButton;

    // Game Over Menu
    sf::Text gameOverText;
    sf::Text statsText;
    sf::Text mainMenuButtonText;
    sf::RectangleShape mainMenuButton;

    // Button states
    bool playButtonHovered;
    bool exitButtonHovered;
    bool mainMenuButtonHovered;
    bool mousePressed;

    // Game stats
    int survivalTime;
    int wavesSurvived;
    int enemiesKilled;

    // Helper methods
    void setupIntroMenu();
    void setupGameOverMenu();
    void updateIntroMenu(sf::RenderWindow& window, MenuState& gameState);
    void updateGameOverMenu(sf::RenderWindow& window, MenuState& gameState);
    void drawIntroMenu(sf::RenderWindow& window);
    void drawGameOverMenu(sf::RenderWindow& window);
    bool isMouseOverButton(const sf::RectangleShape& button, sf::RenderWindow& window);
    void updateButtonAppearance(sf::RectangleShape& button, sf::Text& text, bool hovered);
};