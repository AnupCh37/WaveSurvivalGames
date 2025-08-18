#define _USE_MATH_DEFINES 
#include <cmath> 
#include <iostream>
#include "Weapon.h"
#include "Math.h"

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
    gunAngle = std::atan2(directionToTarget.y, directionToTarget.x); 

    weaponSpr.setRotation(gunAngle * 180.0f / static_cast<float>(M_PI));

  
    if (directionToTarget.x < 0.0f && weaponSpr.getScale().y > 0.0f)
        weaponSpr.setScale(weaponSpr.getScale().x, -weaponSpr.getScale().y);
    else if (directionToTarget.x > 0.0f && weaponSpr.getScale().y < 0.0f)
        weaponSpr.setScale(weaponSpr.getScale().x, -weaponSpr.getScale().y);


    for (std::size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i].move(bulletDirections[i] * bulletSpeed * deltaTime);
    }
}


void Weapon::Shoot(const sf::Vector2f& startPos, const sf::Vector2f& targetPos)
{
    if (clock.getElapsedTime().asSeconds() > fireRate) {
        sf::Sprite newBullet(bTexture);
        newBullet.setPosition(startPos);
        newBullet.setOrigin(newBullet.getLocalBounds().width / 2.0f, newBullet.getLocalBounds().height / 2.0f);

        newBullet.setScale(0.5f, 0.5f); 

      
        sf::Vector2f direction = Math::NormalizeVector(targetPos - startPos);
        float rotationAngleRad = std::atan2(targetPos.y - startPos.y, targetPos.x - startPos.x);

 
        newBullet.setRotation((rotationAngleRad - (static_cast<float>(M_PI) / 2.0f)) * 180.0f / static_cast<float>(M_PI)); 

        bullets.push_back(newBullet);
        bulletDirections.push_back(direction); 

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
