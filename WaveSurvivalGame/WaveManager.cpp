#include "WaveManager.h"
#include <SFML/System.hpp>  
#include <iostream>

WaveManager::WaveManager(Sound* soundSys)
    : currentWave(1), soundSystem(soundSys)
{
}

void WaveManager::Update(std::vector<Enemy>& enemies)
{
    
    if (waveTimer.isActive()) {
        if (waveTimer.isFinished()) {
           
            spawnWave(enemies, currentWave);
            currentWave++;
        }
        return; 
    }

   
    bool allDead = true;
    for (size_t i = 0; i < enemies.size(); i++) {
        if (enemies[i].getHealth() > 0) {
            allDead = false;
            break;
        }
    }

    if (allDead && !enemies.empty()) { 
        
        float delayTime = 3.0f; 
        waveTimer.start(delayTime);
    }
    else if (enemies.empty() && currentWave == 1) {
       
        spawnWave(enemies, currentWave);
        currentWave++;
    }
}

float WaveManager::getPlayerSpeed()
{
    float speed = 150.0f + (currentWave - 1) * 30;
    return speed;
}

float WaveManager::getPlayerDamage()
{
    float damage = 10.0f + (currentWave - 1) * 1;
    return damage;
}
void WaveManager::spawnWave(std::vector<Enemy>& enemies, int waveNum)
{
    enemies.clear();
    std::cout << "Spawning Wave " << waveNum << std::endl;

    if (waveNum == 1) {
        Enemy e1(0.1f);
        if (e1.Load({ 100.0f, 100.0f })) {
            e1.soundSystem = soundSystem;
            enemies.push_back(e1);
        }
        Enemy e2(0.11f);
        if (e2.Load({ 300.0f, 200.0f })) {
            e2.soundSystem = soundSystem;
            enemies.push_back(e2);
        }

    }
    else if (waveNum == 6) {
        Enemy e1(0.12f);
        if (e1.Load({ 300.0f, 300.0f })) {
            e1.soundSystem = soundSystem;
            enemies.push_back(e1);
        }
        Enemy e2(0.13f);
        if (e2.Load({ 200.0f, 100.0f })) {
            e2.soundSystem = soundSystem;
            enemies.push_back(e2);
        }
        Enemy e3(0.14f);
        if (e3.Load({ 400.0f, 150.0f })) {
            e3.soundSystem = soundSystem;
            enemies.push_back(e3);
        }
    }
    else if (waveNum == 3) {
        for (int i = 0; i < 4; i++) {
            Enemy e(0.1f + i * 0.03f);
            if (e.Load({ 100 + i * 100.0f, 100.0f + i * 50.0f })) {
                e.soundSystem = soundSystem;
                enemies.push_back(e);
            }
        }
    }
    else if (waveNum == 4) {
        for (int i = 0; i < 6; i++) {
            Enemy e(0.1f + i * 0.02f);
            if (e.Load({ 100 + i * 100.0f, 100.0f + i * 50.0f })) {
                e.soundSystem = soundSystem;
                enemies.push_back(e);
            }
        }
    }
    else if (waveNum == 5) {
        for (int i = 0; i < 7; i++) {
            Enemy e(0.1f + i * 0.02f);
            if (e.Load({ 100 + i * 100.0f, 100.0f + i * 50.0f })) {
                e.soundSystem = soundSystem;
                enemies.push_back(e);
            }
        }
    }
    else if (waveNum == 2)
    {
        for (int i = 0; i < 8; i++)
        {
            Enemy e(0.1f + i * 0.015f);
            if (e.Load({ 100.0f,100.0f }))
            {
                e.soundSystem = soundSystem;
                enemies.push_back(e);
            }
        }
        for (int i = 0; i < 8; i++)
        {
            Enemy e(0.1f + i * 0.015f);
            if (e.Load({ 400.0f,400.0f }))
            {
                e.soundSystem = soundSystem;
                enemies.push_back(e);
            }
        }

    }
    else {
        std::cout << "No more waves defined!" << std::endl;
    }
}

bool WaveManager::isWaveLoading() const
{
    return waveTimer.isActive();
}

float WaveManager::getTimeRemaining() const
{
    return waveTimer.getTimeRemaining();
}

int WaveManager::getCurrentWave() const
{
    return currentWave;
}
