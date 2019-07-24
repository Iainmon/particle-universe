#include <iostream>
#include "../Obiectum.hpp"
#include "Components.hpp"

using namespace std;
using namespace obiectum;
using namespace components;
using namespace physics;


void RigidBody::Setup(void)
{
    transform = static_cast<Transform*>(gameObject->GetComponentByType<Transform>());
}

void RigidBody::Update(void)
{
    transform->position += transform->velocity * deltaTime;
}