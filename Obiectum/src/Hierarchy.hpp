#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "GameObject.hpp"
#include "Component.hpp"

using namespace std;    

namespace obiectum {

    uint64_t micros();

    class Hierarchy {
        private:

        vector<GameObject *> gameObjects;

        unsigned long long lastTime;

        void updateDeltaTime(void);

        public:

        Hierarchy();

        void Add(GameObject* _gameObject);

        void AddObjects(vector<GameObject*> _gameObjects);

        void updateAllGameObjects();
    };
}