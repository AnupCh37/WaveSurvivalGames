#pragma once
#include<SFML/Graphics.hpp>
#include"Enemy.h"
#include"Weapon.h"

class Player
{
private:
    sf::Texture ptexture;
    sf::Texture bulletTexture;
    std::vector<sf::RectangleShape> bullets;
    std::vector<sf::Sprite> bulletSprites;
    sf::RectangleShape boundingRectangle;
    sf::Vector2i size;
    float bulletSpeed;
    float maxfireRate;
    float fireRateTimer;
    float playerSpeed;

public:
    sf::Sprite psprite;
    Player();
    ~Player();

public:
    Weapon weapon;
    void Initialize();
    void Draw(float deltaTime, sf::RenderWindow& window);
    void load();
    void Update(float deltaTime, Enemy& enemy, sf::RenderWindow& window);

protected:
};
