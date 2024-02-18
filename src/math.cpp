#include "elementary/math.h"

#include <cstring>

float Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    y = number;
    std::memcpy(&i, &y, sizeof(float));
    i = 0x5f3759df - (i >> 1);
    std::memcpy(&y, &i, sizeof(float));
    y = y * (threehalfs - (x2 * y * y));
    y = y * (threehalfs - (x2 * y * y));

    return y;
}

vec2 operator*(const float a, const vec2& b) {
    return b * a;
}
vec3 operator*(const float a, const vec3& b) {
    return b * a;
}
vec4 operator*(const float a, const vec4& b) {
    return b * a;
}

std::ostream& operator<<(std::ostream& a, const vec2& b)
{
    a << "(" << b.x << ", " << b.y << ")";
    return a;
}
std::ostream& operator<<(std::ostream& a, const vec3& b)
{
    a << "(" << b.x << ", " << b.y << ", " << b.z << ")";
    return a;
}
std::ostream& operator<<(std::ostream& a, const vec4& b)
{
    a << "(" << b.x << ", " << b.y << ", " << b.z << ", " << b.w << ")";
    return a;
}

std::istream& operator>>(std::istream& a, vec2 &b)
{
    a >> b.x >> b.y;
    return a;
}
std::istream& operator>>(std::istream& a, vec3 &b)
{
    a >> b.x >> b.y >> b.z;
    return a;
}
std::istream& operator>>(std::istream& a, vec4 &b)
{
    a >> b.x >> b.y >> b.z >> b.w;
    return a;
}

mat4x4 operator*(const float a, const mat4x4 &b) {
    return b * a;
}