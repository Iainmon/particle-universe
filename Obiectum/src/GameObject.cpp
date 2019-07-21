#include <iostream>
#include <string>
#include <vector>

#include "GameObject.hpp"
#include "Component.hpp"

using namespace std;
using namespace obiectum;

const char * ComponentMissingException::what() const throw ()
{
    return "The component could not be found for this GameObject.";
}

GameObjectMetaData::GameObjectMetaData() {
    name = "Generic_GameObject";
    type = "GameObject";
}
GameObjectMetaData::GameObjectMetaData(string _name) {
    name = _name;
    type = _name;
}
GameObjectMetaData::GameObjectMetaData(string _name, string _type) {
    name = _name;
    type = _type;
}

/*
    Constructors
    */
GameObject::GameObject() {}
GameObject::GameObject(GameObjectMetaData _metaData) {
    metaData = _metaData;
}
GameObject::GameObject(string _name) {
    metaData = GameObjectMetaData(_name);
}
GameObject::GameObject(string _name, string _type) {
    metaData = GameObjectMetaData(_name, _type);
}

/*
    Adds the new component to the array of components
*/
void GameObject::AddComponent(Component* _component) {
    //_component->Assign(this);
    components.push_back(_component);
}

Component* GameObject::GetComponentByType(string _type) {
    for (int i = 0; i < components.size(); i++) {
        if (components[i]->type == _type) {
            return components[i];
        }
    }
    throw ComponentMissingException();
}

template<class T>
Component* GameObject::GetComponentByType() {
    for (int i = 0; i < components.size(); i++)
    {
        if (dynamic_cast<T*>(components[i]) != nullptr)
        {
            return components[i];
        }
    }
    return nullptr;
} // RigidBody* rb = gameObject.GetComponentByType<RigidBody>();

void GameObject::updateComponents() {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Update();
    }
}
