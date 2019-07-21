#include <iostream>
#include <string>
#include <vector>

#include "../Component.cpp"
#include "../physics/Vector.cpp"

using namespace std;

namespace obiectum {
    namespace components {

        using namespace physics;

        class Transform: public Component {
            private:

            public:

            const string type override = "Transform";

            Vector2D position;
            Vector2D velocity;

            void Setup(void) override {
                
            }

            void Update(void) override {
                
            }

        }
    }
}