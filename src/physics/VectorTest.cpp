#include <iostream>
#include <math.h>
#include "./Vector.cpp"

using namespace physics;

int main() {

    Vector2D v1 = Vector2D(10, 10);
    Vector2D v2 = Vector2D(10, 10);

    //v2 += v1;

    Vector2D v3 = v1 + v2;

    std::cout << v3.magnitude() << "\n";
    std::cout << v3.x << "\n";
    std::cout << v3.y << "\n";
    //std::cout << v1.magnitude() << "\n";

}