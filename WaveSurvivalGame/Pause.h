#pragma once
#include <SFML/Graphics.hpp>

class Pause
{
private:
    sf::Font font;
    sf::Text pauseText;
    sf::RectangleShape pauseButton;

    bool isPaused = false;

public:
    Pause();
    ~Pause();

    void load();
    void Draw(sf::RenderWindow& window);
    void Update(float deltaTime, sf::RenderWindow& window);


    bool GetPaused() const { return isPaused; }

    void SetPaused(bool paused) { isPaused = paused; }
};
