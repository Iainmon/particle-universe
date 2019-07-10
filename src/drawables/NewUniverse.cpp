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
ParticleAttributes Positive = ParticleAttributes(glDrawing::colors::Red, 8, 100, 1);
ParticleAttributes Negative = ParticleAttributes(glDrawing::colors::Blue, 2, 0.1, -1);
ParticleAttributes Medium = ParticleAttributes(glDrawing::colors::Green, 20, 100, 0);
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

static float GetChargeForce(Particle a, Particle b)
{
    float chargeCoef = 100;
    float distance = (a.pos - b.pos).magnitude();
    return (a.attributes.charge * b.attributes.charge * chargeCoef) / (distance);
}


static float GetGravForce(Particle a, Particle b)
{
    float gravCoef = 1000;
    float distance = (a.pos - b.pos).magnitude();
    return -(a.attributes.mass * b.attributes.mass * gravCoef) / (distance);
}



class Universe: public Drawable
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
        //SpawnParticles(PresetParticleAttributes::Positive, 100, 5);
        //SpawnParticles(PresetParticleAttributes::Negative, 1000, 20);
        SpawnParticles(PresetParticleAttributes::Medium, 3, 0);
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

    void ManageCollisions(const float timestep)
    {
        for (int i = 0; i < particleHierarchy.size(); i++)
        {
            Particle *particleA = &particleHierarchy[i];
            float radiusA = particleA->attributes.radius;

            if(particleA->pos.x < radiusA){
                particleA->vel.x = -particleA->vel.x;
                particleA->pos.x = radiusA;
            }

            if(particleA->pos.x > width - radiusA){
                particleA->vel.x = -particleA->vel.x;
                particleA->pos.x = width - radiusA;
            }

            if(particleA->pos.y < radiusA){
                particleA->vel.y = -particleA->vel.y;
                particleA->pos.y = radiusA;
            }

            if(particleA->pos.y > height - radiusA){
                particleA->vel.y = -particleA->vel.y;
                particleA->pos.y = height - radiusA;
            }

            
            for (int j = i + 1; j < particleHierarchy.size(); j++)
            {
                Particle *particleB = &particleHierarchy[j];
            }
        }
    }


    void ApplyForces(const float timestep)
    {
        for (int i = 0; i < particleHierarchy.size(); i++)
        {
            Particle *particleA = &particleHierarchy[i];
            for (int j = i + 1; j < particleHierarchy.size(); j++)
            {
                Particle *particleB = &particleHierarchy[j];

                float chargeForce = GetChargeForce(*particleA, *particleB);
                float gravForce = GetGravForce(*particleA, *particleB);

                Vector2D forceVector = (particleA->pos - particleB->pos).normalized();
                forceVector = forceVector * (chargeForce + gravForce);

                particleA->AddForce(forceVector, timestep);
                particleB->AddForce(-forceVector, timestep);
            }
        }
    }

    void MoveParticles(const float timestep)
    {
        for (int i = 0; i < particleHierarchy.size(); i++)
        {
            Particle *currentParticle = &particleHierarchy[i];
            currentParticle->Move(timestep);
        }
    }

    void Step(const float timestep)
    {
        ManageCollisions(timestep);
        ApplyForces(timestep);
        MoveParticles(timestep);
    }

    void Draw(const float deltaTime)
    {
        //stroke->background();

        // Step(deltaTime);

        for (int i = 0; i < particleHierarchy.size(); i++)
        {
            Particle *currentParticle = &particleHierarchy[i];
            //stroke->circle(currentParticle->pos.x, currentParticle->pos.y, currentParticle->attributes.radius, currentParticle->attributes.color);
            glDrawing::fcircle(currentParticle->pos.x, currentParticle->pos.y, currentParticle->attributes.radius, currentParticle->attributes.color);
        }
    }
};
