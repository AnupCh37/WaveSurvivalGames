#pragma once
#include <SFML/Graphics.hpp>

class FrameRate {
public:
    FrameRate();
    ~FrameRate();

    void Initialize();
    void Load(); // Standardized to capital L
    void Update(float deltaTime); // Changed to float deltaTime
    void Draw(sf::RenderWindow& window);

private:
    sf::Text text;
    sf::Font font;
    float timer; // Changed to float
    int frameCount; // Added for more accurate FPS calculation
};