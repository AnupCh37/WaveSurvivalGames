#pragma once
#include<SFML/Graphics.hpp>
class Math
{
public:
    static sf::Vector2f NormalizeVector(sf::Vector2f vector);
    static bool DidRectCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);

};

