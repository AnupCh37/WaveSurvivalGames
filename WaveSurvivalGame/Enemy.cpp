#include "Enemy.h"
#include <iostream>
#include <cmath>

Enemy::Enemy()
    : sprite(texture), health(100), healthtext()
{
    // Basic text settings
    healthtext.setCharacterSize(30);
    healthtext.setFillColor(sf::Color::Red);
}

Enemy::~Enemy() {}

void Enemy::Draw(sf::RenderWindow& window)
{
    if (health > 0) {
        window.draw(sprite);
        window.draw(boundingRectangle);
        window.draw(healthtext);
    }
}

void Enemy::ChangeHealth(int hp) {
    health += hp;
    healthtext.setString(std::to_string(health));
}

void Enemy::Update(float deltaTime)
{
    if (health > 0) {
        boundingRectangle.setPosition(sprite.getPosition());
        healthtext.setPosition(sprite.getPosition().x, sprite.getPosition().y - 30);
    }
}

void Enemy::Update(float deltaTime, const sf::Vector2f& playerPos)
{
    float speed = 0.1f;
    sf::Vector2f direction = playerPos - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;
    sprite.move(direction * speed * deltaTime);
}

void Enemy::Load()
{
    if (font.loadFromFile("Assets/Fonts/arial.ttf")) {
        std::cout << "Arial.ttf font loaded successfully." << std::endl;
        healthtext.setFont(font);
        healthtext.setString(std::to_string(health));
    }
    else {
        std::cout << "Failed to load Arial.ttf font." << std::endl;
    }

    if (texture.loadFromFile("Assets/Player/Texture/spritesheet.png")) {
        std::cout << "Enemy image loaded." << std::endl;

        sprite.setPosition(sf::Vector2f(1000.f, 730.f));
        int Xindex = 0;
        int Yindex = 2;
        sprite.setTextureRect(sf::IntRect(Xindex * size.x, Yindex * size.y, size.x, size.y));
        sprite.setScale(1.f, 1.f);

        boundingRectangle.setSize(sf::Vector2f(size.x, size.y));
    }
    else {
        std::cout << "Enemy image could not be loaded." << std::endl;
    }
}

void Enemy::Initialize()
{
    size = sf::Vector2i(64, 64);
    boundingRectangle.setSize(sf::Vector2f(size.x, size.y));
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Red);
    boundingRectangle.setOutlineThickness(1);
}