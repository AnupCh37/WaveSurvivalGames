#pragma once
#include <SFML/Graphics.hpp> // Required for sf::Vector2f and sf::FloatRect

namespace Math {
    sf::Vector2f NormalizeVector(sf::Vector2f vector);
    bool DidRectCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
    sf::Vector2f GetRectCenter(const sf::FloatRect& rect); // Declaration
}