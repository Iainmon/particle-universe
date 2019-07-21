#include <iostream>
#include <string>
#include <vector>

#include "../Component.cpp"
#include "../physics/Vector.cpp"
#include "Transform.cpp"

using namespace std;

namespace obiectum {
    namespace components {

        using namespace physics;

        class Transform: public Component {
            private:

            // Pointer to the Transform Component
            Transform* transform;

            public:

            const string type override = "RigidBody";

            void Setup(void) override {
                transform = gameObject->getComponentByType("Transform");
            }

            void Update(void) override {
                tansform->position += transform->velocity * deltaTime;
            }

        }
    }
}