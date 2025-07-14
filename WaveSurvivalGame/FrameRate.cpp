#include "FrameRate.h"
#include <iostream>
#include <string>


FrameRate::FrameRate() : timer(0.0f) {
    std::cout << "FrameRate system initialized.\n";
}


FrameRate::~FrameRate() {
    std::cout << "FrameRate system destroyed.\n";
}


void FrameRate::Initialize() {
    timer = 0.0f;
}


void FrameRate::Load() {
    if (font.loadFromFile("C://Users//anup3//OneDrive//Desktop//rpg game//assets//Fonts//arial.ttf")) {
        std::cout << "Arial.ttf font loaded successfully.\n";
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setString("");
        text.setPosition(10.f, 10.f);
    }
    else {
        std::cout << "Failed to load Arial.ttf font.\n";
    }
}


void FrameRate::Update(double deltaTime) {
    timer += deltaTime;


    if (timer >= 1000.0) {
        double fps = 1000.0 / deltaTime;
        std::string frameRateString = "FPS: " + std::to_string(static_cast<int>(fps)) +
            " | Frame Time: " + std::to_string(static_cast<int>(deltaTime)) + " ms";
        text.setString(frameRateString);
        timer = 0.0f;
    }
}


void FrameRate::Draw(sf::RenderWindow& window) {
    window.draw(text);
}
