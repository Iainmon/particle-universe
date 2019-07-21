#include <iostream>

#include <Obiectum.hpp>

//#include "../components/Transform.cpp"

using namespace std;
using namespace obiectum;

int main() {

    Hierarchy* h = new Hierarchy();
    
    GameObject* gm1 = new GameObject();
        //Component* transform = new Transform(gm1);
        //gm1->AddComponent(transform);

    h->Add(gm1);

    h->updateAllGameObjects();

    return 0;
}