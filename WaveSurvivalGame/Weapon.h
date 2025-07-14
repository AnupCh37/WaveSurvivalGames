#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

class Weapon
{
public:
    Weapon();
    void shoot(float deltaTime, const sf::Vector2f& weaponPos, const sf::Vector2f& target);
    void drawBullets(sf::RenderWindow& window);
    void load();
    void Initialize();
    void Update(float deltaTime);

private:
    sf::Sprite weaponSpr;
    sf::Sprite bullet;
    sf::Clock clock;
    sf::Texture wTexture;
    sf::Texture bTexture;
    float gunAngle = 0.f;
    float fireRate = 0.2f;
    float bulletSpeed = 500.f;
    std::vector<sf::Sprite> bullets;
    std::vector<float> angles;
    std::vector<float> rotation;
};
