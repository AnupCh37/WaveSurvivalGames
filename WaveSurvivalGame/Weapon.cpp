#include "Weapon.h"
#include <cmath>
#include <iostream>

Weapon::Weapon() : weaponSpr(wTexture), bullet(bTexture)
{
    weaponSpr.setTexture(wTexture);
    bullet.setTexture(bTexture);
}

void Weapon::shoot(float deltaTime, const sf::Vector2f& weaponPos, const sf::Vector2f& target)
{
    weaponSpr.setPosition(weaponPos);

    gunAngle = std::atan2(target.y - weaponSpr.getPosition().y, target.x - weaponSpr.getPosition().x);
    weaponSpr.setRotation(gunAngle * 180.f / 3.1415926f);

    if (target.x < weaponSpr.getPosition().x && weaponSpr.getScale().y > 0)
        weaponSpr.setScale(weaponSpr.getScale().x, -weaponSpr.getScale().y);
    else if (target.x > weaponSpr.getPosition().x && weaponSpr.getScale().y < 0)
        weaponSpr.setScale(weaponSpr.getScale().x, -weaponSpr.getScale().y);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clock.getElapsedTime().asSeconds() > fireRate) {
        bullet.setPosition(weaponSpr.getPosition());
        bullets.push_back(bullet);

        float angle = std::atan2(target.y - weaponSpr.getPosition().y, target.x - weaponSpr.getPosition().x);
        angles.push_back(angle);

        float rot = angle * 180.f / 3.1415926f;
        rotation.push_back(rot);

        clock.restart();
    }

    for (std::size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i].move(std::cos(angles[i]) * bulletSpeed * deltaTime, std::sin(angles[i]) * bulletSpeed * deltaTime);
        bullets[i].setRotation(rotation[i]);
    }
}

void Weapon::drawBullets(sf::RenderWindow& window)
{
    for (const auto& b : bullets) {
        window.draw(b);
    }
    window.draw(weaponSpr);
}

void Weapon::load()
{
    if (wTexture.loadFromFile("Assets/GunAssets/PNG/assaultrifle.png")) {
        std::cout << "Weapon loaded " << std::endl;
    }
    else {
        std::cout << "Failed to load Weapon texture" << std::endl;
    }

    if (bTexture.loadFromFile("Assets/GunAssets/PNG/small_bullet.png")) {
        std::cout << "Bullets loaded " << std::endl;
    }
    else {
        std::cout << "Failed to load Bullet texture" << std::endl;
    }
}

void Weapon::Initialize()
{
}

void Weapon::Update(float deltaTime)
{
}