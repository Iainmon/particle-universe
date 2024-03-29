#include "Drawable.cpp"

#include <vector>
#include <random>

using namespace physics;
using namespace std;
using namespace obiectum;

struct ParticleAttributes
{

    glDrawing::Color color;
    float radius;
    float mass;
    float charge;

    ParticleAttributes()
    {
        color = glDrawing::colors::White;
        radius = 1;
        mass = 1;
        charge = 1;
    }

    ParticleAttributes(glDrawing::Color _color, float _radius, float _mass, float _charge)
    {
        color = _color;
        radius = _radius;
        mass = _mass;
        charge = _charge;
    }
};

namespace PresetParticleAttributes
{
const ParticleAttributes Positive = ParticleAttributes(glDrawing::colors::Red, 8, 100, 1);
const ParticleAttributes Negative = ParticleAttributes(glDrawing::colors::Blue, 2, 0.1, -1);
const ParticleAttributes Medium = ParticleAttributes(glDrawing::colors::Green, 20, 100, 0);
} // namespace PresetParticleAttributes

class Particle : public Drawable
{

public:
    ParticleAttributes attributes;

    Particle()
    {
        attributes = ParticleAttributes();
        position = Vector2D();
        velocity = Vector2D();
    }

    Particle(const ParticleAttributes _attributes, const Vector2D _position, const Vector2D _velocity)
    {
        attributes = _attributes;
        position = _position;
        velocity = _velocity;
    }

    void AddForce(Vector2D force, const float deltaTime)
    {
        Vector2D accel = force / attributes.mass;
        velocity += accel * deltaTime;
    }

    void Setup() override
    {
    }

    void Step(const float deltaTime) override
    {
        position += velocity * deltaTime;
    }

    void Draw() override
    {
        glDrawing::fcircle(position.x, position.y, attributes.radius, attributes.color);
    }
};

static float GetChargeForce(Particle *a, Particle *b)
{
    float chargeCoef = 100;
    float distance = (a->position - b->position).magnitude();
    return (a->attributes.charge * b->attributes.charge * chargeCoef) / (distance);
}

static float GetGravForce(Particle *a, Particle *b)
{
    float gravCoef = 1000;
    float distance = (a->position - b->position).magnitude();
    return -(a->attributes.mass * b->attributes.mass * gravCoef) / (distance);
}

class ParticleController : public Drawable
{
private:
    float width;
    float height;

public:
    std::vector<Drawable *> particleHierarchy;

    ParticleController(const float _width, const float _height)
    {
        width = _width;
        height = _height;

        std::vector<Drawable *> p, n, e;

        p = spawnParticles(PresetParticleAttributes::Positive, 2, 0);
        e = spawnParticles(PresetParticleAttributes::Negative, 2, 0);
        n = spawnParticles(PresetParticleAttributes::Medium, 2, 0);

        particleHierarchy.insert(particleHierarchy.end(), p.begin(), p.end());
        particleHierarchy.insert(particleHierarchy.end(), e.begin(), e.end());
        particleHierarchy.insert(particleHierarchy.end(), n.begin(), n.end());
    }

    void Setup() override
    {
    }
    void Step(const float deltaTime) override
    {

        Vector2D windowDimensions = glDrawing::getScreenSize();
        width = (int)windowDimensions.x;
        height = (int)windowDimensions.y;

        ManageCollisions(deltaTime);
        ApplyForces(deltaTime);
    }
    void Draw() override
    {
    }

    void ManageCollisions(const float timestep)
    {
        for (int i = 0; i < particleHierarchy.size(); i++)
        {
            Particle *particleA = static_cast<Particle *>(particleHierarchy[i]);
            float radiusA = particleA->attributes.radius;

            if (particleA->position.x < radiusA)
            {
                particleA->velocity.x = -particleA->velocity.x;
                particleA->position.x = radiusA;
            }

            if (particleA->position.x > width - radiusA)
            {
                particleA->velocity.x = -particleA->velocity.x;
                particleA->position.x = width - radiusA;
            }

            if (particleA->position.y < radiusA)
            {
                particleA->velocity.y = -particleA->velocity.y;
                particleA->position.y = radiusA;
            }

            if (particleA->position.y > height - radiusA)
            {
                particleA->velocity.y = -particleA->velocity.y;
                particleA->position.y = height - radiusA;
            }

            for (int j = i + 1; j < particleHierarchy.size(); j++)
            {
                Particle *particleB = static_cast<Particle *>(particleHierarchy[j]);
            }
        }
    }

    void ApplyForces(const float timestep)
    {
        for (int i = 0; i < particleHierarchy.size(); i++)
        {
            Particle *particleA = static_cast<Particle *>(particleHierarchy[i]);
            for (int j = i + 1; j < particleHierarchy.size(); j++)
            {
                Particle *particleB = static_cast<Particle *>(particleHierarchy[j]);

                float chargeForce = GetChargeForce(particleA, particleB);
                float gravForce = GetGravForce(particleA, particleB);

                Vector2D forceVector = (particleA->position - particleB->position).normalized();
                forceVector = forceVector * (chargeForce + gravForce);

                particleA->AddForce(forceVector, timestep);
                particleB->AddForce(-forceVector, timestep);
            }
        }
    }

    std::vector<Drawable *> spawnParticles(ParticleAttributes attributes, int amount, float maxVel)
    {

        std::vector<Drawable *> particleList;

        for (int j = 0; j < amount; j++)
        {
            float randPX = ((double)rand() / (RAND_MAX)) * width;
            float randPY = ((double)rand() / (RAND_MAX)) * width;

            float randVX = maxVel * (((double)rand() / (RAND_MAX)) * 2 - 1);
            float randVY = maxVel * (((double)rand() / (RAND_MAX)) * 2 - 1);

            Drawable *newParticle = new Particle(attributes, Vector2D(randPX, randPY), Vector2D(randVX, randVY));
            particleList.push_back(newParticle);
        }

        return particleList;
    }
};