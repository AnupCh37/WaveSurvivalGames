#define _USE_MATH_DEFINES // IMPORTANT: Must be before #include <cmath>
#include <cmath> // For std::atan2, M_PI
#include <iostream>
#include "Weapon.h"
#include "Math.h" // For Math::NormalizeVector

Weapon::Weapon() : weaponSpr(wTexture), fireRate(0.2f), bulletSpeed(0.5f), gunAngle(0.0f)
{
}

void Weapon::Initialize()
{
    weaponSpr.setOrigin(weaponSpr.getLocalBounds().width / 2.0f, weaponSpr.getLocalBounds().height / 2.0f);
}

void Weapon::Load()
{
    if (wTexture.loadFromFile("Assets/GunAssets/PNG/assaultrifle.png")) {
        std::cout << "Weapon texture loaded " << std::endl;
    }
    else {
        std::cout << "Failed to load Weapon texture" << std::endl;
    }

    if (bTexture.loadFromFile("Assets/GunAssets/PNG/small_bullet.png")) {
        std::cout << "Bullet texture loaded " << std::endl;
    }
    else {
        std::cout << "Failed to load Bullet texture" << std::endl;
    }
}

void Weapon::Update(float deltaTime, const sf::Vector2f& weaponPos, const sf::Vector2f& target)
{
    weaponSpr.setPosition(weaponPos);

    sf::Vector2f directionToTarget = target - weaponSpr.getPosition();
    gunAngle = std::atan2(directionToTarget.y, directionToTarget.x); // Radians

    weaponSpr.setRotation(gunAngle * 180.0f / static_cast<float>(M_PI));

    // Flip weapon sprite if pointing left
    if (directionToTarget.x < 0.0f && weaponSpr.getScale().y > 0.0f)
        weaponSpr.setScale(weaponSpr.getScale().x, -weaponSpr.getScale().y);
    else if (directionToTarget.x > 0.0f && weaponSpr.getScale().y < 0.0f)
        weaponSpr.setScale(weaponSpr.getScale().x, -weaponSpr.getScale().y);

    // Update bullet positions
    for (std::size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i].move(bulletDirections[i] * bulletSpeed * deltaTime);
    }
}

// Updated definition to match the new signature (only takes startPos and targetPos)
void Weapon::Shoot(const sf::Vector2f& startPos, const sf::Vector2f& targetPos)
{
    if (clock.getElapsedTime().asSeconds() > fireRate) {
        sf::Sprite newBullet(bTexture);
        newBullet.setPosition(startPos);
        newBullet.setOrigin(newBullet.getLocalBounds().width / 2.0f, newBullet.getLocalBounds().height / 2.0f);

        newBullet.setScale(0.5f, 0.5f); // Make the bullet half its original size

        // **Both movement and rotation are now based on the same target: targetPos (mouse)**
        sf::Vector2f direction = Math::NormalizeVector(targetPos - startPos);
        float rotationAngleRad = std::atan2(targetPos.y - startPos.y, targetPos.x - startPos.x);

        // Adjust for the bullet texture pointing UPWARD at 0 degrees
        // Subtract 90 degrees (M_PI/2 radians) from the calculated angle.
        newBullet.setRotation((rotationAngleRad - (static_cast<float>(M_PI) / 2.0f)) * 180.0f / static_cast<float>(M_PI)); // Convert to degrees

        bullets.push_back(newBullet);
        bulletDirections.push_back(direction); // Store movement direction for Update loop

        clock.restart();
    }
}

void Weapon::Draw(sf::RenderWindow& window)
{
    for (const auto& b : bullets) {
        window.draw(b);
    }
    window.draw(weaponSpr);
}

std::vector<sf::Sprite>& Weapon::getBullets() {
    return bullets;
}

sf::Sprite& Weapon::getWeaponSprite() {
    return weaponSpr;
}