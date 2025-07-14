#include "Player.h"
#include "Math.h"
#include <iostream>
#include"Enemy.h"
Player::Player() :
    ptexture(), psprite(ptexture),
    bulletSpeed(0.5f), playerSpeed(1.0f),
    maxfireRate(150.0f), fireRateTimer(0.0f)
{
}

Player::~Player() {}

void Player::Draw(float deltaTime, sf::RenderWindow& window)
{
    window.draw(psprite);
    window.draw(boundingRectangle);
    for (const auto& bullet : bulletSprites)
    {
        window.draw(bullet);
    }
}

void Player::Update(float deltaTime, Enemy& enemy, sf::RenderWindow& window)
{
    sf::Vector2f position = psprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        psprite.move(sf::Vector2f(1.f, 0.f) * this->playerSpeed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        psprite.move(sf::Vector2f(-1.f, 0.f) * this->playerSpeed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        psprite.move(sf::Vector2f(0.f, -1.f) * this->playerSpeed * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        psprite.move(sf::Vector2f(0.f, 1.f) * this->playerSpeed * deltaTime);


    sf::Vector2f newPos = psprite.getPosition();
    sf::Vector2u winSize = window.getSize();
    sf::FloatRect bounds = psprite.getGlobalBounds();


    if (newPos.x < 0) newPos.x = 0;
    if (newPos.x + bounds.width > winSize.x) newPos.x = winSize.x - bounds.width;

    if (newPos.y < 0) newPos.y = 0;
    if (newPos.y + bounds.height > winSize.y) newPos.y = winSize.y - bounds.height;

    psprite.setPosition(newPos);

    fireRateTimer += deltaTime;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireRateTimer >= maxfireRate)
    {
        sf::Sprite bullet(bulletTexture);
        bullet.setPosition(psprite.getPosition());
        bulletSprites.push_back(bullet);
        fireRateTimer = 0;
    }


    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    for (size_t i = 0; i < bulletSprites.size(); )
    {
        sf::Vector2f bulletDir = Math::NormalizeVector(mouseWorldPos - bulletSprites[i].getPosition());
        bulletSprites[i].move(bulletDir * bulletSpeed * deltaTime);

        if (bulletSprites[i].getGlobalBounds().intersects(enemy.sprite.getGlobalBounds()))
        {
            enemy.ChangeHealth(-10);
            bulletSprites.erase(bulletSprites.begin() + i);
        }
        else
        {
            ++i;
        }
    }

    boundingRectangle.setPosition(psprite.getPosition());
}

void Player::load()
{
    if (ptexture.loadFromFile("assets/Player/Texture/spritesheet.png"))
    {
        std::cout << "Player Image loaded\n";
        int Xindex = 2, Yindex = 2;
        psprite.setTextureRect({ Xindex * size.x, Yindex * size.y, size.x, size.y });
        psprite.setScale({ 1.f, 1.f });
        boundingRectangle.setSize({ size.x * psprite.getScale().x, size.y * psprite.getScale().y });
        psprite.setPosition({ 0, 0 });
    }
    else
    {
        std::cout << "Player image cannot be loaded\n";
    }

    if (bulletTexture.loadFromFile("assets/GunAssets/PNG/small_bullet.png"))
    {
        std::cout << "Bullet image loaded\n";
    }
    else
    {
        std::cout << "Failed to load bullet image\n";
    }
}

void Player::Initialize()
{
    boundingRectangle.setFillColor(sf::Color::Transparent);
    boundingRectangle.setOutlineColor(sf::Color::Transparent);
    boundingRectangle.setOutlineThickness(1);
    size = { 64, 64 };
}
