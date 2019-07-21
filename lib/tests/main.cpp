#include <iostream>

#include "../Hierarchy.cpp"
#include "../GameObject.cpp"
#include "../Component.cpp"
#include "../components/Transform.cpp"

using namespace std;

int main() {

    Hierarchy* h = new Hierarchy();
    
    GameObject* gm1 = new GameObject();
        Component* transform = new Transform(gm1);
        gm1->AddComponent(transform);

    h->Add(gm1);

    h->updateAllGameObjects

    return 0;
}