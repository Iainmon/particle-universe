#pragma once

#include <iostream>
#include <string>
#include "../Component.hpp"
#include "../Physics.hpp"

namespace obiectum {

    namespace components {

        using namespace std;
        using namespace physics;

        class Transform: public Component {
            public:

            const string type = "Transform";

            Vector2D position;
            Vector2D velocity;

            void Setup(void) override;
            void Update(void) override;
        };

        class RigidBody: public Component {

            // Pointer to the Transform Component
            Transform* transform;

            public:

            const string type = "RigidBody";

            void Setup(void) override;
            void Update(void) override;

        };
    }
}