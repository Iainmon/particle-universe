#include <iostream>
#include <vector>
#include <chrono>

#include "GameObject.cpp"
#include "Component.cpp"

using namespace std;

namespace obiectum {

    uint64_t micros()
    {
        uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::
                                                                                now()
                                                                                    .time_since_epoch())
                        .count();
        return us;
    }

    class Hierarchy {
        private:

        vector<GameObject *> gameObjects;

        unsigned long long lastTime = micros();

        void updateDeltaTime(void) {
            const unsigned long long now = micros();
            Component.deltaTime = ((float)((now - lastTime) / 1000000.0f));
            lastTime = now;
        }

        public:

        Hierarchy() {}

        void Add(GameObject* _gameObject) {
            gameObjects.push_back(_gameObject);
        }

        void AddObjects(vector<GameObjects*> _gameObjects)
        {
            gameObjects.insert(_gameObjects.end(), _gameObjects.begin(), _gameObjects.end());
        }

        void updateAllGameObjects() {

            updateDeltaTime();

            for (unsigned int i = 0; i < gameObjects.size(); i++) {
                gameObjects[i]->updateComponents();
            }
        }
    };
}