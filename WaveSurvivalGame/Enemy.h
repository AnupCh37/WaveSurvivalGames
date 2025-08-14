#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath> // For std::sqrt in Update overloads
#include "Collision.h"
#include "Sound.h" // Include Sound class

class Player; // Forward declaration for Player to break circular include

class Enemy
{
public:
    Enemy();
    ~Enemy();

    void Draw(sf::RenderWindow& window);
    void ChangeHealth(int hp);
    void Update(float deltaTime);
    void Update(float deltaTime, const sf::Vector2f& playerPos, Player& player, const std::vector<int>& tiles);
    void Load(const sf::Vector2f pos);
    void Initialize();
    Collision collision;
    sf::Sprite sprite;
    sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }
    sf::RectangleShape boundingRectangle;
    int getHealth() const { return health; }

    // Sound system access
    Sound* soundSystem; // Pointer to sound system

private:
    sf::Texture idleTexture;
    sf::Texture attackTexture;
    sf::Texture walktexture;
    sf::Text healthtext;
    sf::Font font;

    int health;
    sf::Vector2i size;// Size of enemy sprite frame

    // Attack Cooldown Members
    float attackCooldown; // Time in seconds between attacks
    sf::Clock attackClock; // Clock to manage cooldown
};