namespace physics
{

struct Position
{

    float X, Y;

    Position(float _x = 0.0f, float _y = 0.0f)
    {
        X = _x;
        Y = _y;
    }
};

struct Vector
{

    Position position;
    Position dposition;

    float velocity = 0.0f;

    Vector(Position _position = Position(), Position _dposition = Position(), float _velocity = 0.0f)
    {
        position = _position;
        dposition = _dposition;
        velocity = _velocity;
    }
};

void applyGravity(Vector *vector, float strength = 0.95f)
{
    (*vector).dposition.Y += strength;
}
void applyFrictionX(Vector *vector, float strength = 0.005f)
{
    if ((*vector).dposition.X != 0)
    {
        if ((*vector).dposition.X > 0)
        {
            (*vector).dposition.X -= strength;
        }
        else
        {
            (*vector).dposition.X += strength;
        }
    }
}
void applyFrictionY(Vector *vector, float strength = 0.005f)
{
    if ((*vector).dposition.Y != 0)
    {
        if ((*vector).dposition.Y > 0)
        {
            (*vector).dposition.Y -= strength;
        }
        else
        {
            (*vector).dposition.Y += strength;
        }
    }
}

void applyAirFriction(Vector *vector, float strength = 0.0005f)
{
    applyFrictionX(vector, strength);
    applyFrictionY(vector, strength);
}

struct Vector2D
{

    float x, y;

    Vector2D(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    Vector2D()
    {
        x = 0.0f;
        y = 0.0f;
    }

    float magnitude() const
    {
        return sqrt((x * x) + (y * y));
    }

    Vector2D normalized()
    {
        float mag = magnitude();
        float nx = x / mag;
        float ny = y / mag;

        return Vector2D(nx, ny);
    }

    void flip() {
        const float tmpY = y;
        y = x;
        x = tmpY;
    }

    Vector2D &operator+=(const Vector2D &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Vector2D &operator-=(const Vector2D &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2D operator-()
    {
        x = -x;
        y = -y;
        return Vector2D(x, y);
    }
    Vector2D operator+()
    {
        x = +x;
        y = +y;
        return Vector2D(x, y);
    }

    Vector2D operator+(const Vector2D &rhs)
    {
        return Vector2D(this->x + rhs.x, this->y + rhs.y);
    }
    Vector2D operator-(const Vector2D &rhs)
    {
        return Vector2D(this->x - rhs.x, this->y - rhs.y);
    }

    Vector2D operator+(const float rhs)
    {
        return Vector2D(this->x + rhs, this->y + rhs);
    }
    Vector2D operator*(const float rhs)
    {
        return Vector2D(this->x * rhs, this->y * rhs);
    }
    Vector2D operator/(const float rhs)
    {
        return Vector2D(this->x / rhs, this->y / rhs);
    }

    friend std::ostream &operator<<(std::ostream &output, const Vector2D &rhs)
    {
        output << "X : " << rhs.x << " Y : " << rhs.y << " Magnitude : " << rhs.magnitude();
        return output;
    }
    bool operator<(const Vector2D &rhs)
    {
        if (magnitude() < rhs.magnitude())
        {
            return true;
        }
        return false;
    }
    bool operator>(const Vector2D &rhs)
    {
        if (magnitude() > rhs.magnitude())
        {
            return true;
        }
        return false;
    }
    bool operator<=(const Vector2D &rhs)
    {
        if (magnitude() <= rhs.magnitude())
        {
            return true;
        }
        return false;
    }
    bool operator>=(const Vector2D &rhs)
    {
        if (magnitude() >= rhs.magnitude())
        {
            return true;
        }
        return false;
    }

    void operator=(const Vector2D &rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }
};

struct RigidBody2D {

    Vector2D drag;
    Vector2D gravity;

    float bounce = 30;

    RigidBody2D() {
        drag = Vector2D(0.0f, 0.05f);
        gravity = Vector2D(0.0f, 1.5f);
        
        bounce /= 100;
    }
};

struct Transform2D
{
    Vector2D position;
    Vector2D velocity;

    Transform2D() {
        position = Vector2D();
        velocity = Vector2D();
    }
};

} // namespace physics