#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> // For debug output
#include <cmath>    // For M_PI
#include "Collision.h" // Include Collision.h for the Collision class
#include "Sound.h" // Include Sound class

class Enemy; // Forward declaration to break circular dependency

class Player
{
public:
    Player();
    ~Player();

    void Load();
    void Update(float deltaTime, std::vector<Enemy>& enemies, sf::RenderWindow& window, const std::vector<int>& tiles);
    void Draw(float deltaTime, sf::RenderWindow& window);
    void ChangeHealth(int hp); // Function to change player health

    sf::Sprite psprite; // Public for easy access in main, consider making private with getter
    sf::FloatRect getGlobalBounds() const { return psprite.getGlobalBounds(); } // Getter for player's global bounds

    sf::RectangleShape boundingRectangle; // Declare boundingRectangle here
    int getHealth() const { return health; } // Getter for player health

    // Sound system access
    Sound* soundSystem; // Pointer to sound system

private:
    sf::Texture idleTexture;
    sf::Texture attackTexture;
    sf::Texture walkTexture;
    sf::Texture boneTexture; // Declare boneTexture here

    sf::Vector2i size; // Size of player sprite frame

    float boneSpeed;
    float boneFireRate;
    sf::Clock boneFireClock; // Clock for bone firing rate

    std::vector<sf::Sprite> bones; // Vector to hold bone sprites
    std::vector<sf::Vector2f> boneDirections; // Vector to hold bone directions

    // Animation members
    float animationTimer = 0.0f;
    int currentFrame = 0;
    float frameTime = 0.1f; // Time per frame in seconds
    int totalFrames = 6;    // Total frames in the walk animation (adjust as needed)

    int health; // Player's current health
    sf::Text healthText; // Text to display player's health
    sf::Font font; // Font for health text

    Collision collision; // Declare Collision object here

    // Walking sound tracking
    bool wasMoving = false; // Track if player was moving in previous frame
};