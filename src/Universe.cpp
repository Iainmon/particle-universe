#include <SFML/Graphics.hpp>
#include <vector>
#include <random>



using namespace physics;
using namespace std;

//the library of the universe, an infinite one, a beuatiful one, it is gods kingdomn, nigerlisous
namespace Universe {


    float GetChargeForce(Particle a, Particle b){
        float chargeCoef = 10;
        float aCharge = a.attributes.charge;
        float bCharge = b.attributes.charge;
        float distance = (a.pos - b.pos).magnitude();
        return (aCharge * bCharge * chargeCoef) / (distance * distance);
    }


    struct ParticleAttributes {
        sf::Color color;
        float radius;
        float mass;
        float charge;
    };


    struct Particle {
        ParticleAttributes attributes;
        Vector2D pos;
        Vector2D vel;

        Particle(ParticleAttributes _attributes, Vector2D _pos, Vector2D _vel){
            attributes = _attributes;
            pos = _pos;
            vel = _vel;
        }

        void Move(float timestep){
            pos += vel * timestep;
        }

        void AddForce(Vector2D force, float timestep){
            float accel = force / attributes.mass;
            vel += accel * timestep;
        }
    };


    struct ParticleSpawnData {
        ParticleAttributes attributes;
        int amount;
        float maxVel;
    };



    class Universe {
        vector<Particle> particleHierarchy;
        float width;
        float height;

        public:
            Universe (float _width, float _height){
                particleHierarchy = vector<Particle>();
                width = _width;
                height = _height;
            }


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


            void Step(float timestep){
                ApplyForces(timestep);
                ApplyVelocities(timestep);
            }


            void ApplyForces(float timestep){
                for (int i = 0; i < particleHierarchy.size(); i++){
                    Particle particleA = particleHierarchy[i];
                    for (int j = i + 1; j < particleHierarchy.size(); j++){
                        Particle particleB = particleHierarchy[i];

                        float force = GetChargeForce(particleA, particleB);
                        
                        



                    }
                }
            }


            void ApplyVelocities(float timestep){
                for (int i = 0; i < particleHierarchy.size(); i++){
                    Particle currentParticle = particleHierarchy[i];
                    currentParticle.Move(timestep);
                }
            }


            Frame GetFrame(Stroke stroke){





                for (int i = 0; i < particleHierarchy.size(); i++){
                    Particle currentParticle = particleHierarchy[i];

                }

                stroke.circle(10, 100, 10, BlAKV);
                return stroke.frame;
            }
    };



















    
}