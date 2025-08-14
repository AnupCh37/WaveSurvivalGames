#define _USE_MATH_DEFINES // IMPORTANT: Add this line at the very top for M_PI
#include "Enemy.h"
#include <iostream>
#include <cmath>
#include "Player.h"
#include "Collision.h"

Enemy::Enemy()
    : 
    sprite(idleTexture), health(100), healthtext(), size({ 100, 100 }),
    attackCooldown(1.0f),
    attackClock(),
    soundSystem(nullptr)
{
    healthtext.setCharacterSize(30);
    healthtext.setFillColor(sf::Color::Red);
    // Initialize boundingRectangle
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1.0f); // Use float literal
    boundingRectangle.setSize(sf::Vector2f(size.x / 4.0f, size.y / 4.0f)); // Use float literals
}

Enemy::~Enemy() {}
void Enemy::Draw(sf::RenderWindow& window)
{
    if (health > 0) {
        window.draw(sprite);
        window.draw(boundingRectangle);
        window.draw(healthtext); // Ensure healthtext is drawn
    }
}

void Enemy::ChangeHealth(int hp) {
    health += hp;
    if (health < 0) health = 0; // Prevent health from going below zero
    healthtext.setString(std::to_string(health));
    std::cout << "Enemy Health (in ChangeHealth): " << health << std::endl; // Debug print
}

void Enemy::Update(float deltaTime) // Changed to float deltaTime
{
    if (health > 0) {
        boundingRectangle.setPosition(sprite.getPosition());



    }
}

// --- UPDATED: Update signature to include Player& player ---
void Enemy::Update(float deltaTime, const sf::Vector2f& playerPos, Player& player, const std::vector<int>& tiles)
{
    if (health <= 0)
        return; // If health is 0 or less, stop updating this enemy

    float speed = 0.066f;
    sf::Vector2f direction = playerPos - sprite.getPosition();
    if (direction.x < 0)
    {
        sprite.setScale(-1.8f, 1.8f);
    }
    else
    {
        sprite.setScale(1.8f, 1.8f);
    }
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); // Declared here
    if (length != 0.0f) // Use float literal
        direction /= length;

    sf::Vector2f velocity = direction * speed * deltaTime;

    // --- Collision-aware movement ---

    // Try horizontal move
    sf::Vector2f tryMoveX(velocity.x, 0.0f); // Use float literal
    sf::FloatRect testXBounds = boundingRectangle.getGlobalBounds();
    testXBounds.left += tryMoveX.x;

    if (!collision.checkCollision(testXBounds, tiles)) {
        sprite.move(tryMoveX);
    }

    // Try vertical move
    sf::Vector2f tryMoveY(0.0f, velocity.y); // Use float literal
    sf::FloatRect testYBounds = boundingRectangle.getGlobalBounds();
    testYBounds.top += tryMoveY.y;

    if (!collision.checkCollision(testYBounds, tiles)) {
        sprite.move(tryMoveY);
    }

    // --- Position updates ---
    boundingRectangle.setPosition(sprite.getPosition());
    healthtext.setPosition(boundingRectangle.getPosition().x - healthtext.getLocalBounds().width / 2.0f,
        boundingRectangle.getPosition().y - healthtext.getLocalBounds().height / 2.0f - 35.0f);

    float distanceToPlayer = length;
    if (distanceToPlayer < 50.0f) {
        if (attackClock.getElapsedTime().asSeconds() >= attackCooldown) {
            if (player.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
                
                if (soundSystem) {
                    soundSystem->playSound("axeHit", 85.0f);
                }

                player.ChangeHealth(-10);
                attackClock.restart();
                std::cout << "Enemy attacked player! Player Health: " << player.getHealth() << std::endl;
            }
        }
    }
}

void Enemy::Load(const sf::Vector2f pos)
{
    if (font.loadFromFile("Assets/Fonts/arial.ttf")) {
        healthtext.setFont(font);
        healthtext.setCharacterSize(16);
        healthtext.setString(std::to_string(health));
    }
    else {
        std::cout << "Failed to load Arial.ttf font." << std::endl;
    }

    if (idleTexture.loadFromFile("Assets/Player/Texture/Orc_idle.png")) { // Assuming enemy uses player spritesheet for now
        sprite.setPosition(sf::Vector2f(pos.x, pos.y));
        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
        sprite.setScale(1.8f, 1.8f);
        sprite.setOrigin(size.x / 2.0f, size.y / 2.0f);
        boundingRectangle.setOrigin(size.x / 8.0f, size.y / 8.0f);// Set origin for proper positioning
    }
    else {
        std::cout << "Failed to load enemy image." << std::endl;
    }
}

void Enemy::Initialize()
{
    // All initialization moved to constructor or Load()
}