#include <iostream>

#include <Obiectum.hpp>

//#include "../components/Transform.cpp"

using namespace std;
using namespace obiectum;
using namespace physics;

int main()
{

    Hierarchy* h = new Hierarchy();
    
    GameObject* gm1 = new GameObject();
        gm1->AddComponent(new components::Transform());
        components::Transform* transform = gm1->GetComponent<components::Transform>();
        transform->position = Vector2D(1, 1);
        cout << transform->position.magnitude() << endl;

    h->Add(gm1);

    h->updateAllGameObjects();

    return 0;
}