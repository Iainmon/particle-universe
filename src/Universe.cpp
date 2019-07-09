#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

using namespace physics;
using namespace std;

//the library of the universe, an infinite one, a beuatiful one, it is gods kingdomn, nigerlisous
namespace universe
{

struct ParticleAttributes
{

    sf::Color color;
    float radius;
    float mass;
    float charge;

    ParticleAttributes()
    {
        color = sf::Color::White;
        radius = 1;
        mass = 1;
        charge = 1;
    }

    ParticleAttributes(sf::Color _color, float _radius, float _mass, float _charge)
    {
        color = _color;
        radius = _radius;
        mass = _mass;
        charge = _charge;
    }
};

namespace PresetParticleAttributes
{
ParticleAttributes Positive = ParticleAttributes(sf::Color::Red, 8, 100, 1);
ParticleAttributes Negative = ParticleAttributes(sf::Color::Blue, 2, 0.1, -1);
ParticleAttributes Medium = ParticleAttributes(sf::Color::Green, 16, 0.1, -0.1);
} // namespace PresetParticleAttributes

struct Particle
{
    ParticleAttributes attributes;
    Vector2D pos;
    Vector2D vel;

    Particle()
    {
        attributes = ParticleAttributes();
        pos = Vector2D();
        vel = Vector2D();
    }

    Particle(ParticleAttributes _attributes, Vector2D _pos, Vector2D _vel)
    {
        attributes = _attributes;
        pos = _pos;
        vel = _vel;
    }

    void Move(float timestep)
    {
        pos += vel * timestep;
    }

    void AddForce(Vector2D force, float timestep)
    {
        Vector2D accel = force / attributes.mass;
        vel += accel * timestep;
    }
};

/* 
    struct ParticleSpawnData {
        ParticleAttributes attributes;
        int amount;
        float maxVel;
        ParticleSpawnData(ParticleAttributes _attributes, int _amount, float _maxVel){
            attributes = _attributes;
            amount = _amount;
            maxVel = _maxVel;
        }
    };
    */

class Universe
{
    vector<Particle> particleHierarchy;
    float width;
    float height;

public:
    Universe(float _width, float _height)
    {
        particleHierarchy = vector<Particle>();
        width = _width;
        height = _height;
        SpawnParticles(PresetParticleAttributes::Positive, 50, 1);
        SpawnParticles(PresetParticleAttributes::Negative, 100, 20);
        //SpawnParticles(PresetParticleAttributes::Medium, 100, 1);
    }

    void SpawnParticles(ParticleAttributes attributes, int amount, float maxVel)
    {
        for (int j = 0; j < amount; j++)
        {
            float randPX = ((double)rand() / (RAND_MAX)) * width;
            float randPY = ((double)rand() / (RAND_MAX)) * height;

            float randVX = maxVel * (((double)rand() / (RAND_MAX)) * 2 - 1);
            float randVY = maxVel * (((double)rand() / (RAND_MAX)) * 2 - 1);

            Particle newParticle = Particle(attributes, Vector2D(randPX, randPY), Vector2D(randVX, randVY));
            particleHierarchy.push_back(newParticle);
        }
    }

    /* 
            void SpawnParticles(vector<ParticleSpawnData> spawnDataList){
                for(int i = 0; i < spawnDataList.size(); i++){
                    
                    ParticleSpawnData spawnData = spawnDataList[i];

                    for(int j = 0; j < spawnData.amount; j++){
                        float randPX = ((double) rand() / (RAND_MAX)) * width;
                        float randPY = ((double) rand() / (RAND_MAX)) * height;

                        float randVX = spawnData.maxVel * (((double) rand() / (RAND_MAX)) * 2 - 1);
                        float randVY = spawnData.maxVel * (((double) rand() / (RAND_MAX)) * 2 - 1);

                        Particle newParticle = Particle(spawnData.attributes, Vector2D(randPX, randPY), Vector2D(randVX, randVY));
                        particleHierarchy.push_back(newParticle);
                    }
                }
            }
            */

    void ApplyForces(float timestep)
    {
        for (int i = 0; i < particleHierarchy.size(); i++)
        {
            Particle *particleA = &particleHierarchy[i];
            for (int j = i + 1; j < particleHierarchy.size(); j++)
            {
                Particle *particleB = &particleHierarchy[j];

                float force = GetChargeForce(*particleA, *particleB);
                Vector2D forceVector = (particleA->pos - particleB->pos).normalized() * force;

                particleA->AddForce(forceVector, timestep);
                particleB->AddForce(-forceVector, timestep);
            }
        }
    }

    void MoveParticles(float timestep)
    {
        for (int i = 0; i < particleHierarchy.size(); i++)
        {
            Particle *currentParticle = &particleHierarchy[i];
            currentParticle->Move(timestep);
        }
    }

    void Step(const float timestep)
    {
        ApplyForces(timestep);
        MoveParticles(timestep);
    }

    void Draw(const float deltaTime)
    {

        //stroke->background();

        Step(deltaTime);

        for (int i = 0; i < particleHierarchy.size(); i++)
        {
            Particle *currentParticle = &particleHierarchy[i];
            //stroke->circle(currentParticle->pos.x, currentParticle->pos.y, currentParticle->attributes.radius, currentParticle->attributes.color);
            glDrawing::fcircle(currentParticle->pos.x, currentParticle->pos.y, currentParticle->attributes.radius, currentParticle->attributes.color);
        }
    }

    float GetChargeForce(Particle a, Particle b)
    {
        float chargeCoef = 10;
        float aCharge = a.attributes.charge;
        float bCharge = b.attributes.charge;
        float distance = (a.pos - b.pos).magnitude();
        return (aCharge * bCharge * chargeCoef) / (distance);
    }
};

} // namespace Universe