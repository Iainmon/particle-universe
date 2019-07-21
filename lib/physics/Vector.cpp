#include <iostream>
#include <cmath>

namespace obiectum {
namespace physics
{

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

}
}