#include <algorithm>
#include <cmath>

#include "math.h"
#include "vector.h"

Vector math::vector_angles(const Vector& forward)
{
    Vector view;
    if (forward.y == 0.0f && forward.x == 0.0f)
    {
        view.x = 0.0f;
        view.y = 0.0f;
    }
    else
    {
        view.y = std::atan2(forward.y, forward.x) * 180.0f / static_cast<float>(3.14159265358979323846);

        if (view.y < 0.0f)
            view.y += 360.0f;

        view.z = std::sqrt(forward.x * forward.x + forward.y * forward.y);

        view.x = std::atan2(forward.z, view.z) * 180.0f / static_cast<float>(3.14159265358979323846);
    }

    return Vector{ -view.x, view.y, 0.0f };
}

Vector math::angle_vector(const Vector& angles)
{
    float sp = std::sin(degree_to_radian(angles.x));
    float cp = std::cos(degree_to_radian(angles.x));
    float sy = std::sin(degree_to_radian(angles.y));
    float cy = std::cos(degree_to_radian(angles.y));

    return Vector{ cp * cy, cp * sy, -sp };
}

void Vector::normalize()
{
    while (x < -180.f) x += 360.f;
    while (x > 180.f) x -= 360.f;
    
    while (y < -180.f) y += 360.f;
    while (y > 180.f) y -= 360.f;
    
    z = 0.0f;
}

void Vector::clamp()
{
    x = std::clamp(x, -89.f, 89.f);
    y = std::clamp(std::remainder(y, 360.f), -180.f, 180.f);
    z = std::clamp(z, -50.f, 50.f);
}