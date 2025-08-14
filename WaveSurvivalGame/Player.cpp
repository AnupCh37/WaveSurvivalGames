#define _USE_MATH_DEFINES
#include "Player.h"
#include "Math.h"
#include <iostream>
#include <string> // Required for std::to_string
#include <cmath>
#include "Enemy.h"

// Global function getTileAtPosition (assuming it's intended to be global)
int getTileAtPosition(const sf::Vector2f& pos, const std::vector<int>& level)
{
    const int tilew = 16;
    const int inttileh = 16;
    const int mapw = 50;
    const int maph = 38;
    int x = static_cast<int>(pos.x) / tilew;
    int y = static_cast<int>(pos.y) / inttileh;

    if (x < 0 || x >= mapw || y < 0 || y >= maph)
        return -1; // Indicate out of bounds

    return level[y * mapw + x];
}


Player::Player() :
    idleTexture(), attackTexture(), walkTexture(), psprite(idleTexture),
    size({ 100, 100 }),
    boneSpeed(0.4f),
    boneFireRate(0.3f),
    health(100),
    healthText(),
    animationTimer(0.0f),
    currentFrame(0),
    frameTime(0.1f),
    totalFrames(6),
    soundSystem(nullptr), // Initialize sound system pointer
    wasMoving(false)
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Transparent);
    boundingRectangle.setOutlineThickness(1.0f); // Use float literal
    boundingRectangle.setSize(sf::Vector2f(32.0f, 32.0f)); // Use float literals
    psprite.setOrigin(size.x / 2.0f, size.y / 2.0f);

    //  Configure Player Health Text
    healthText.setCharacterSize(20); // Smaller font size for HP
    healthText.setFillColor(sf::Color::Green); // Green color for player HP
    healthText.setString(std::to_string(health)); // Set initial health string
}

Player::~Player()
{
    // Destructor definition
}
void Player::ChangeHealth(int hp) {
    int oldHealth = health;
    health += hp;
    if (health < 0)
    {
        health = 0;
    }
    healthText.setString(std::to_string(health));

    // Play hurt sound when taking damage
    if (hp < 0 && soundSystem) {
        soundSystem->playSound("playerHurt", 80.0f);
    }

    // Play death sound when health reaches 0
    if (oldHealth > 0 && health == 0 && soundSystem) {
        soundSystem->playSound("playerDeath", 100.0f);
    }

    std::cout << "Player Health Changed to: " << health << std::endl;
}


void Player::Load()
{
    if (idleTexture.loadFromFile("assets/Player/Texture/idle.png"))
    {

        int Xindex = 2, Yindex = 2;
        psprite.setTextureRect({ 0, 0 , size.x, size.y });
        psprite.setScale(2.0f, 2.0f);
        boundingRectangle.setSize(sf::Vector2f(static_cast<float>(size.x) / 4.0f, static_cast<float>(size.y) / 4.0f)); // Use float literals
        boundingRectangle.setPosition(400.0f, 300.0f);
        boundingRectangle.setOrigin(sf::Vector2f(static_cast<float>(size.x) / 8.0f, static_cast<float>(size.y) / 8.0f)); // Use float literals
        psprite.setPosition(400.0f, 300.0f);
    }
    else
    {
        std::cout << "Player image cannot be loaded\n";
    }

    if (boneTexture.loadFromFile("Assets/GunAssets/PNG/arrow.png")) {
        // Bone texture loaded message removed
    }
    else {
        std::cout << "Failed to load Bone texture. Make sure 'Assets/GunAssets/PNG/arrow.png' exists.\n";
    }

    //  Load Font for Player Health Text
    if (font.loadFromFile("Assets/Fonts/arial.ttf")) { // Assuming this path is correct for your font
        healthText.setFont(font);
        healthText.setCharacterSize(16);
        // std::cout << "Player health font loaded successfully." << std::endl; // Debug print removed
    }
    else {
        std::cout << "Failed to load font for player health. Make sure 'Assets/Fonts/arial.ttf' exists.\n";
    }
}
void Player::Update(float deltaTime, std::vector<Enemy>& enemies, sf::RenderWindow& window, const std::vector<int>& tiles)
{
    sf::Vector2f velocity(0.0f, 0.0f); // Use float literals
    float baseSpeed = 300.0f;
    bool Moving = false;
    float moveAmount = baseSpeed * deltaTime / 1000.0f;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y -= moveAmount;
        Moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y += moveAmount;
        Moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x -= moveAmount;
        psprite.setScale(-2.0f, 2.0f);
        Moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x += moveAmount;
        psprite.setScale(2.0f, 2.0f);
        Moving = true;
    }

    if (Moving) {
        if (!wasMoving && soundSystem) {
            // Start walking sound when player starts moving
            soundSystem->playSound("playerWalk", 60.0f, 1.2f);
        }
        wasMoving = true;

        // Continue existing animation code...
        animationTimer += deltaTime / 1000.0f;
        if (animationTimer >= frameTime) {
            animationTimer = 0.0f;
            currentFrame = (currentFrame + 1) % totalFrames;
            walkTexture.loadFromFile("assets/Player/Texture/walk.png");
            psprite.setTexture(walkTexture);
            psprite.setTextureRect(sf::IntRect(currentFrame * 100, 0, 100, 100));
        }
    }
    else {
        if (wasMoving && soundSystem) {
            // Stop walking sound when player stops moving
            soundSystem->stopSound("playerWalk");
        }
        wasMoving = false;

        // Continue existing idle animation code...
        if (currentFrame != 0) {
            currentFrame = 0;
            animationTimer = 0.0f;
            psprite.setTexture(idleTexture);
            psprite.setTextureRect({ 0, 0, 100, 100 });
        }
    }

    sf::FloatRect bounds = boundingRectangle.getGlobalBounds();

    // Try horizontal move
    sf::FloatRect testXBounds = bounds;
    testXBounds.left += velocity.x;
    bool canMoveX = !collision.checkCollision(testXBounds, tiles);

    // Try vertical move
    sf::FloatRect testYBounds = bounds;
    testYBounds.top += velocity.y;
    bool canMoveY = !collision.checkCollision(testYBounds, tiles);

    if (canMoveX) psprite.move(velocity.x, 0.0f); // Use float literal
    if (canMoveY) psprite.move(0.0f, velocity.y); // Use float literal
    if (canMoveX) boundingRectangle.move(velocity.x, 0.0f); // Use float literal
    if (canMoveY) boundingRectangle.move(0.0f, velocity.y); // Use float literal

    // Update health text position
    healthText.setPosition(
        boundingRectangle.getPosition().x - healthText.getLocalBounds().width / 2.0f,
        boundingRectangle.getPosition().y - healthText.getLocalBounds().height / 2.0f - 35.0f
    );

    // Bone shooting
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && boneFireClock.getElapsedTime().asSeconds() > boneFireRate)
    {
        // Play arrow shooting sound
        if (soundSystem) {
            soundSystem->playSound("arrowShoot", 70.0f, 1.1f);
        }

        // Continue existing bone shooting code...
        sf::Sprite newBone(boneTexture);
        newBone.setPosition(psprite.getPosition());
        newBone.setOrigin(newBone.getLocalBounds().width / 2.0f, newBone.getLocalBounds().height / 2.0f);
        newBone.setScale(1.5f, 1.5f);

        sf::Vector2f direction = Math::NormalizeVector(mouseWorldPos - psprite.getPosition());
        float rotationAngleRad = std::atan2(direction.y, direction.x);
        newBone.setRotation(rotationAngleRad * 180.0f / static_cast<float>(M_PI));

        bones.push_back(newBone);
        boneDirections.push_back(direction);
        boneFireClock.restart();
    }

    // Bone movement and collision
    for (size_t i = 0; i < bones.size(); /* no increment here */) {
        bones[i].move(boneDirections[i] * boneSpeed * deltaTime);
        bool hit = false;

        for (auto& enemy : enemies)
        {
            if (enemy.getHealth() > 0 && Math::DidRectCollision(bones[i].getGlobalBounds(), enemy.boundingRectangle.getGlobalBounds())) {
                enemy.ChangeHealth(-10);
                std::cout << "Enemy hit! Current Enemy Health: " << enemy.getHealth() << std::endl; // Debug print
                bones.erase(bones.begin() + i);
                boneDirections.erase(boneDirections.begin() + i);
                hit = true;
                break;
            }
        }
        if (hit)
        {
            continue;
        }
        else {
            sf::FloatRect boneBounds = bones[i].getGlobalBounds();
            sf::Vector2u windowSize = window.getSize();

            if (boneBounds.left > windowSize.x || boneBounds.left + boneBounds.width < 0 ||
                boneBounds.top > windowSize.y || boneBounds.top + boneBounds.height < 0)
            {
                bones.erase(bones.begin() + i);
                boneDirections.erase(boneDirections.begin() + i);
            }
            else {
                ++i;
            }
        }
    }
}




void Player::Draw(float deltaTime, sf::RenderWindow& window)
{
    window.draw(psprite);
    window.draw(boundingRectangle);

    for (const auto& bone : bones) {
        window.draw(bone);
    }
 
    window.draw(healthText);
}