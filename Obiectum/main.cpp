#include <iostream>

#include <Obiectum.hpp>

//#include "../components/Transform.cpp"

using namespace std;
using namespace obiectum;
using namespace physics;

int main() {

    Hierarchy* h = new Hierarchy();
    
    GameObject* gm1 = new GameObject();
        Component* transformComponent = new components::Transform();
        transformComponent->Assign(gm1);
        gm1->AddComponent(transformComponent);
                components::Transform* transform = static_cast<components::Transform*>(transformComponent);
                transform->position = Vector2D(1, 1);
                cout << transform->position.magnitude() << endl;

    h->Add(gm1);

    h->updateAllGameObjects();



    return 0;
}