using namespace physics;

class Drawable {
    public:

    Vector2D position;
    Vector2D velocity;

    Drawable() {
        
    }
    void setPosition(const Vector2D _position) {
        position = _position;
    }
    void setVelocity(const Vector2D _velocity) {
        velocity = _velocity;
    }

    virtual void Setup(void);
    virtual void Step(const float deltaTime);
    virtual void Draw(void);
};

// Exaple of inheritance

class ExampleDrawable: public Drawable {

    public:

    void Setup() override {

    }
    void Step(const float deltaTime) override {

    }
    void Draw() override {

    }

};

// Example of instantiation

Drawable* ball = new ExampleDrawable();

ball->setPosition(Vector2D(1, 1));
ball->setVelocity(Vector2D(1, 1));


// Example of iteration update

std::vector<*Drawable> balls;

balls.push_back(new ExampleDrawable);

for (int i = 0; i < balls.size(); i++) {
    balls[i]->Setup();
}
