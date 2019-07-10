#define TIME_DEBUG 1

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace physics;

namespace obiectum
{

// Drawable class
class Drawable
{
public:
    Vector2D position;
    Vector2D velocity;

    float zoom;

    Drawable()
    {
    }
    void setPosition(const Vector2D _position)
    {
        position = _position;
    }
    void setVelocity(const Vector2D _velocity)
    {
        velocity = _velocity;
    }

    virtual void Setup(void);
    virtual void Step(const float deltaTime);
    virtual void Draw(void);
};

// DrawableController class
class DrawableController
{

private:

    std::vector<Drawable*> obiecta;

    unsigned long long lastTime = util::micros();
    float deltaTime;

public:
    DrawableController()
    {
    }

    void addObject(Drawable* _object) {
        obiecta.push_back(_object);
    }

    void addObjects(std::vector<Drawable*> _objects)
    {
        obiecta.insert(obiecta.end(), _objects.begin(), _objects.end());
    }

    void updateAllObjects(void) {
        #if TIME_DEBUG
        unsigned long long prePhysicsUpdate = util::micros();
        #endif
        // Updates the physics calculations for the objects
        for (unsigned int i = 0; i < obiecta.size(); i++) {
            obiecta[i]->Step(deltaTime);
        }
        #if TIME_DEBUG
        std::cout << "Physics update time was " << (util::micros() - prePhysicsUpdate) / 1000 << "ms." << std::endl;

        unsigned long long preDrawUpdate = util::micros();
        #endif
        // Calls the draw function for all of the objects
        for (unsigned int i = 0; i < obiecta.size(); i++) {
            obiecta[i]->Draw();
        }
        #if TIME_DEBUG
        std::cout << "Graphics draw time was " << (util::micros() - preDrawUpdate) / 1000 << "ms." << std::endl;
        #endif
    }

    void top_call(void) {
        
        // Calculates the delta time of the update
        const unsigned long long now = util::micros();
        deltaTime = ((float)((now - lastTime) / 1000000.0f));
        lastTime = now;

        updateAllObjects();

    }
};

} // namespace obiectum

#ifdef PROGRAM_SHOULD_NOT_COMPILE

// Exaple of inheritance

class ExampleDrawable : public obiectum::Drawable
{

public:
    void Setup() override
    {
    }
    void Step(const float deltaTime) override
    {
    }
    void Draw() override
    {
    }
};

// Example of instantiation

obiectum::Drawable *ball = new ExampleDrawable();

ball->setPosition(Vector2D(1, 1));
ball->setVelocity(Vector2D(1, 1));

// Example of iteration update

std::vector<*Drawable> balls;

balls.push_back(new ExampleDrawable);

for (int i = 0; i < balls.size(); i++)
{
    balls[i]->Setup();
}

#endif