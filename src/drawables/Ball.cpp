#include <math.h>

namespace drawables
{

using namespace physics;

class Ball : public graphics::Drawable
{

public:
    unsigned int prevCollisions = 0;
    unsigned int collisions = 0;

    int raidius = 10;

    float xfriction = 0.95f;
    float yfriction = 0.90f; // Gravity

    float xdampenning = 0.60f;
    float ydampenning = 0.60f;

    //Vector v = Vector( Position(WIDTH/2 - 10, HEIGHT/2), Position(5, 1), 4);
    Transform2D transform = Transform2D();
    RigidBody2D rb = RigidBody2D();
    //Vector* pv;

    static std::vector<Vector *> occupiedLocations;

    int id;

    float lastCollisionDistance = 0.0f;

    void setup() override
    {
        transform.position = Vector2D(300, 50);
        transform.velocity = Vector2D(15, 2);
    }
    void draw(graphics::Stroke *stroke) override
    {

        if (transform.position.x - raidius < 0 || transform.position.x + raidius > WIDTH)
        {
            if (transform.position.x - raidius < 0)
            {
                transform.position.x = raidius + 1;
            }
            else
            {
                transform.position.x = WIDTH - raidius - 1;
            }

            transform.velocity.x *= -rb.bounce;
        }
        if (transform.position.y - raidius < 0 || transform.position.y + raidius > HEIGHT)
        {
            if (transform.position.y - raidius < 0)
            {
                transform.position.y = raidius + 1;
            }
            else
            {
                transform.position.y = HEIGHT - raidius - 1;
            }

            transform.velocity.y *= -rb.bounce;
        }
        if (transform.position.x - raidius < transform.position.y + raidius)
        {

            transform.position.y = transform.position.x - (raidius * 2) - 1;
            transform.velocity.flip();

            transform.velocity.y *= rb.bounce * 2;
            transform.velocity.x *= rb.bounce * 2;

        }

        /*
            Drawing and physics
        */


        // Drawing gradient triangle
        for (int x = 1; x <= WIDTH; x++) {
            for (int y = x; y <= HEIGHT; y++) {
                (*stroke).dot(x, y, sf::Color(util::map(y,0,HEIGHT,0,255),util::map(x,0,HEIGHT,0,255),util::map(y,0,HEIGHT,0,120)));
            }
        }

        // Moving object
        (*stroke).rect(transform.position.x - raidius, transform.position.y - raidius, transform.position.x + raidius, transform.position.y + raidius, sf::Color::Cyan);


#if DEBUG_PHYSICS
        // Draws visual vector lines
        (*stroke).line(transform.position.x, transform.position.y, transform.position.x + (transform.velocity.x * 3), transform.position.y, sf::Color::Blue);
        (*stroke).line(transform.position.x, transform.position.y, transform.position.x, transform.position.y + (transform.velocity.y * 3), sf::Color::Red);
#endif

        std::cout << transform.velocity << std::endl;
        transform.position += transform.velocity;

        if (transform.velocity.magnitude() > 0.5f) {
            transform.velocity.y += 0.173f;
        } else {
            transform.velocity = Vector2D(0, 0);
        }

    }
    // float f(int x) {
    //     // return (((ypos - (ypos/4)) * 0.001) * (x) * (x)) * 0.1;
    //     return pow(x, 2) * (0.5 / (ypos*0.1));
    // }
    // Vector* getVector() {
    //     return &v;
    // }

    bool didCollide(const Position foregnPosition)
    {

        const float dx = foregnPosition.X - transform.position.x;
        const float dy = foregnPosition.Y - transform.position.y;

        return raidius * 2 >= sqrt((dx * dx) + (dy * dy));
    }
    float distance(const Position foregnPosition)
    {
        const float dx = foregnPosition.X - transform.position.x;
        const float dy = foregnPosition.Y - transform.position.y;
        return sqrt((dx * dx) + (dy * dy));
    }
    float lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    }
    void setRaidius(const int x) override
    {
        raidius = x;
    }

    Position *getPosition() override
    {
        return &(v.position);
    }
};
std::vector<Vector *> Ball::occupiedLocations;
} // namespace drawables