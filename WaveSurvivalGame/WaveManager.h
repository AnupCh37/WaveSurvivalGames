#pragma once
#include <SFML/System.hpp>
#include <vector>
#include "Enemy.h"
#include "Sound.h"

class DelayTimer {
private:
    mutable sf::Clock clock;  
    float duration;
    bool active;

public:
    DelayTimer() : duration(0.0f), active(false) {}

    void start(float delaySeconds) {
        duration = delaySeconds;
        clock.restart();
        active = true;
    }

    bool isFinished() {
        if (!active) return true;
        if (clock.getElapsedTime().asSeconds() >= duration) {
            active = false;
            return true;
        }
        return false;
    }

    float getTimeRemaining() const {
        if (!active) return 0.0f;
        float remaining = duration - clock.getElapsedTime().asSeconds();
        return remaining > 0 ? remaining : 0.0f;
    }

    bool isActive() const { return active; }
};

class WaveManager {
private:
    int currentWave;
    Sound* soundSystem;
    DelayTimer waveTimer;  

public:
    WaveManager(Sound* soundSys);
    void Update(std::vector<Enemy>& enemies);
    float getPlayerSpeed();
    void spawnWave(std::vector<Enemy>& enemies, int waveNum);
    bool isWaveLoading() const;
    float getTimeRemaining() const;
    int getCurrentWave() const;
};
