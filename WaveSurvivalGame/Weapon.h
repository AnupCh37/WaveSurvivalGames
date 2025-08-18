#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Math.h" 

class Weapon {
public:
    Weapon();

    void Initialize();
    void Load();
    void Update(float deltaTime, const sf::Vector2f& weaponPos, const sf::Vector2f& target);
    void Draw(sf::RenderWindow& window);

   
    void Shoot(const sf::Vector2f& startPos, const sf::Vector2f& targetPos);

    std::vector<sf::Sprite>& getBullets();
    sf::Sprite& getWeaponSprite();

    std::vector<sf::Vector2f> bulletDirections;

private:
    sf::Texture wTexture;
    sf::Texture bTexture;
    sf::Sprite weaponSpr;

    std::vector<sf::Sprite> bullets;

    float fireRate;
    sf::Clock clock;
    float bulletSpeed;

    float gunAngle; 
};
