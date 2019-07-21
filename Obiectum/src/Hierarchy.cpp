#include <iostream>
#include <vector>
#include <chrono>

#include "GameObject.hpp"
#include "Component.hpp"

#include "Hierarchy.hpp"

using namespace std;
using namespace obiectum;

uint64_t obiectum::micros()
{
    uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::
                                                                            now()
                                                                                .time_since_epoch())
                    .count();
    return us;
}

void Hierarchy::updateDeltaTime(void) {
    const unsigned long long now = micros();
    Component::deltaTime = ((float)((now - lastTime) / 1000000.0f));
    lastTime = now;
}

Hierarchy::Hierarchy() {
    lastTime = micros();
}

void Hierarchy::Add(GameObject* _gameObject) {
    gameObjects.push_back(_gameObject);
}

void Hierarchy::AddObjects(vector<GameObject*> _gameObjects)
{
    gameObjects.insert(_gameObjects.end(), _gameObjects.begin(), _gameObjects.end());
}

void Hierarchy::updateAllGameObjects() {

    updateDeltaTime();

    for (unsigned int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->updateComponents();
    }
}