#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

    struct Frame {
        
        unsigned int width = WIDTH;
        unsigned int height = HEIGHT;

        sf::Color pixels[WIDTH][HEIGHT];

        void clear() {
            for (unsigned int x = 0; x < WIDTH; x++)
            {
                for (unsigned int y = 0; y < HEIGHT; y++)
                {
                    setPixel(x, y, sf::Color::Black);
                }
            }
        }

        void setPixel(unsigned int x, unsigned int y, const sf::Color color) {
            pixels[x][y] = color;
        }
        sf::Color getPixel(unsigned int x, unsigned int y) {
            return pixels[x][y];
        }
    };

    class Stroke {
        private:

            Frame *frame;

            void drawCircle( int xc,  int yc,  int x,  int y, sf::Color color) {
                dot(xc+x, yc+y, color);
                dot(xc-x, yc+y, color);
                dot(xc+x, yc-y, color);
                dot(xc-x, yc-y, color);
                dot(xc+y, yc+x, color);
                dot(xc-y, yc+x, color);
                dot(xc+y, yc-x, color);
                dot(xc-y, yc-x, color);
            }
            
        public:

            float deltaTime = 0.0f;

            Stroke(Frame *drawingFrame) {
                this->frame = drawingFrame;
            }
            bool isInBounds(const int x, const int y) {
                return ( x <= WIDTH && y <= HEIGHT && x >= 0 && y >= 0 );
            }
            void dot(const int x, const int y, sf::Color color) {
                if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0) {
                    this->frame->pixels[x][y] = color;
                }
            }
            void unsafe_dot(const int x, const int y, sf::Color color) {
                this->frame->pixels[x][y] = color;
            }
            sf::Color pix(const int x, const int y) {
                if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0) {
                    return this->frame->pixels[x][y];
                }
            }
            sf::Color unsafe_pix(const int x, const int y) {
                return this->frame->pixels[x][y];
            }

            void line( int x1, int y1, int x2, int y2, const sf::Color& color ){
                // Bresenham's line algorithm
                const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
                if(steep)
                {
                    swap(x1, y1);
                    swap(x2, y2);
                }
                
                if(x1 > x2)
                {
                    swap(x1, x2);
                    swap(y1, y2);
                }
                
                const float dx = x2 - x1;
                const float dy = fabs(y2 - y1);
                
                float error = dx / 2.0f;
                const int ystep = (y1 < y2) ? 1 : -1;
                int y = (int)y1;
                
                const int maxX = (int)x2;
                
                for(int x=(int)x1; x<maxX; x++)
                {
                    if(steep)
                    {
                        dot(y,x, color);
                    }
                    else
                    {
                        dot(x,y, color);
                    }
                
                    error -= dy;
                    if(error < 0)
                    {
                        y += ystep;
                        error += dx;
                    }
                }
            }
 
            void lr_line(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                
                const int dx = x2 - x1;
                const int dy = y2 - y1;

                int z1 = x1;
                int z2 = x2;
                int w1 = y1;
                int w2 = y2;

                if (dx < 0) {
                    swap(z1, z2);
                }
                if (dy < 0) {
                    swap(w1, w2);
                }

                unsigned_lr_line(z1, w1, z2, w2, color);

            }
            void ud_line(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                
                const int dx = x2 - x1;
                const int dy = y2 - y1;

                int z1 = x1;
                int z2 = x2;
                int w1 = y1;
                int w2 = y2;

                if (dx < 0) {
                    swap(z1, z2);
                }
                if (dy < 0) {
                    swap(w1, w2);
                }

                unsigned_ud_line(z1, w1, z2, w2, color);

            }
            void swap(int& x, int& y) {
                int tmp = x;
                x = y;
                y = tmp;
            }


            void unsigned_ud_line(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                
                int dx = x2 - x1;
                int dy = y2 - y1;
                int D = 2 * dy - dx;
                int x = x1;
                
                for (int y = y1; y <= y2; y++) {
                    dot(x, y, color);

                    if (D > 0) {
                        x++;
                        D -= dy * 2;
                    }
                    D += dx * 2;
                }
            }

            void unsigned_lr_line(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                
                int dx = x2 - x1;
                int dy = y2 - y1;
                int D = 2 * dy - dx;
                int y = y1;
                
                for (int x = x1; x <= x2; x++) {
                    dot(x, y, color);

                    if (D > 0) {
                        y++;
                        D -= dx * 2;
                    }
                    D += dy * 2;
                }
            }
            void rect(const int x1, const int y1, const int x2, const int y2, sf::Color color) {
                for (int x = x1; x < x2; x++) {
                    for (int y = y1; y < y2; y++) {
                        this->frame->pixels[x][y] = color;
                    }
                }
            }
            void background(sf::Color color = sf::Color::Black) {
                for (unsigned int x = 0; x < WIDTH; x++) {
                    for (unsigned int y = 0; y < HEIGHT; y++) {
                        this->frame->pixels[x][y] = color;
                    }
                }
            }
            
            void circle( int xc,  int yc,  int r, sf::Color color) 
            {
                 int x = 0, y = r;
                 int d = 3 - 2 * r;
                drawCircle(xc, yc, x, y, color);
                while (y >= x)
                {
                    // for each pixel we will 
                    // draw all eight pixels 
                    
                    x++; 
            
                    // check for decision parameter 
                    // and correspondingly  
                    // update d, x, y 
                    if (d > 0) 
                    { 
                        y--;  
                        d = d + 4 * (x - y) + 10; 
                    } 
                    else
                        d = d + 4 * x + 6; 
                    drawCircle(xc, yc, x, y, color); 
                } 
            }
    };

using namespace physics;
using namespace std;

//the library of the universe, an infinite one, a beuatiful one, it is gods kingdomn, nigerlisous
namespace Universe {


    struct ParticleAttributes {
        
        sf::Color color;
        float radius;
        float mass;
        float charge;

        ParticleAttributes() {
            color = sf::Color::White;
            radius = 1;
            mass = 1;
            charge = 1;
        }

        ParticleAttributes(sf::Color _color, float _radius, float _mass, float _charge){
            color = _color;
            radius = _radius;
            mass = _mass;
            charge = _charge;
        }
    };



    namespace PresetParticleAttributes {
        ParticleAttributes Positive = ParticleAttributes(sf::Color::Red, 10, 1, 1);
        ParticleAttributes Negative = ParticleAttributes(sf::Color::Blue, 3, 0.5, -1);
        ParticleAttributes Medium = ParticleAttributes(sf::Color::Green, 1, 0.1, 0);
    }
    


    struct Particle {
        ParticleAttributes attributes;
        Vector2D pos;
        Vector2D vel;

        Particle() {
            attributes = ParticleAttributes();
            pos = Vector2D();
            vel = Vector2D();
        }

        Particle(ParticleAttributes _attributes, Vector2D _pos, Vector2D _vel) {
            attributes = _attributes;
            pos = _pos;
            vel = _vel;
        }

        void Move(float timestep){
            pos += vel * timestep;
        }

        void AddForce(Vector2D force, float timestep){
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

            Universe Preset1(float _width, float _height){
                particleHierarchy = vector<Particle>();
                SpawnParticles(PresetParticleAttributes::Positive, 50, 10);
                SpawnParticles(PresetParticleAttributes::Negative, 50, 10);
                SpawnParticles(PresetParticleAttributes::Medium, 1000, 1);


                width = _width;
                height = _height;
            }


            void SpawnParticles(ParticleAttributes attributes, int amount, float maxVel){
                for(int j = 0; j < amount; j++){
                    float randPX = ((double) rand() / (RAND_MAX)) * width;
                    float randPY = ((double) rand() / (RAND_MAX)) * height;

                    float randVX = maxVel * (((double) rand() / (RAND_MAX)) * 2 - 1);
                    float randVY = maxVel * (((double) rand() / (RAND_MAX)) * 2 - 1);

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

            void ApplyForces(float timestep){
                for (int i = 0; i < particleHierarchy.size(); i++){
                    Particle particleA = particleHierarchy[i];
                    for (int j = i + 1; j < particleHierarchy.size(); j++){
                        Particle particleB = particleHierarchy[j];

                        float force = GetChargeForce(particleA, particleB);
                        Vector2D forceVector = (particleA.pos - particleB.pos).normalized() * force;

                        particleA.AddForce(forceVector, timestep);
                        particleB.AddForce(-forceVector, timestep);
                    }
                }
            }


            void MoveParticles(float timestep){
                for (int i = 0; i < particleHierarchy.size(); i++){
                    Particle currentParticle = particleHierarchy[i];
                    currentParticle.Move(timestep);
                }
            }


            void Step(float timestep){
                ApplyForces(timestep);
                MoveParticles(timestep);
            }


            void GetFrame(Stroke *stroke){
                Step(stroke->deltaTime);

                for (int i = 0; i < particleHierarchy.size(); i++){
                    Particle currentParticle = particleHierarchy[i];
                    stroke->circle(currentParticle.pos.x, currentParticle.pos.y, 
                                   currentParticle.attributes.radius, currentParticle.attributes.color);
                }                
            }

            float GetChargeForce(Particle a, Particle b){
                float chargeCoef = 10;
                float aCharge = a.attributes.charge;
                float bCharge = b.attributes.charge;
                float distance = (a.pos - b.pos).magnitude();
                return (aCharge * bCharge * chargeCoef) / (distance * distance);
            }
    };



















    
}