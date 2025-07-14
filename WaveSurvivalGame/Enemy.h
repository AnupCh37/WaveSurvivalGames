#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Enemy
{
private:
    sf::Texture texture;
    sf::Font font;
    sf::Text healthtext;

    sf::Vector2i size;
    sf::RectangleShape boundingRectangle;

    int health;

public:
    sf::Sprite sprite;

    Enemy();
    ~Enemy();

    void Initialize();
    void Load();
    void Update(float deltaTime);
    void Update(float deltaTime, const sf::Vector2f& playerPos);
    void Draw(sf::RenderWindow& window);
    void ChangeHealth(int hp);


    int GetHealth() const { return health; }
    sf::FloatRect GetBounds() const { return sprite.getGlobalBounds(); }
};
