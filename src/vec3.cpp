#include "elementary/math.h"

#include <cmath>

const vec3 vec3::zero = vec3(0.0f, 0.0f, 0.0f);
const vec3 vec3::one = vec3(1.0f, 1.0f, 1.0f);
const vec3 vec3::right = vec3(1.0f, 0.0f, 0.0f);
const vec3 vec3::left = vec3(-1.0f, 0.0f, 0.0f);
const vec3 vec3::up = vec3(0.0f, 1.0f, 0.0f);
const vec3 vec3::down = vec3(0.0f, -1.0f, 0.0f);
const vec3 vec3::forward = vec3(0.0f, 0.0f, 1.0f);
const vec3 vec3::back = vec3(0.0f, 0.0f, -1.0f);

float vec3::dot(const vec3 &a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
vec3 vec3::cross(const vec3 &a, const vec3& b) {
    return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.y);
}

vec3::vec3() : vec3(0.0f, 0.0f, 0.0f) {}
vec3::vec3(float x) : vec3(x, 0.0f, 0.0f) {}
vec3::vec3(float x, float y) : vec3(x, y, 0.0f) {}
vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {}
vec3::vec3(const vec2 &vec) : vec3(vec.x, vec.y, 0.0f) {}
vec3::vec3(const vec2 &vec, float z) : vec3(vec.x, vec.y, z) {}
vec3::vec3(float x, const vec2 &vec) : vec3(x, vec.x, vec.y) {}
vec3::vec3(const vec3 &vec) : vec3(vec.x, vec.y, vec.z) {}
vec3::vec3(const vec4 &vec) : vec3(vec.x, vec.y, vec.z) {}

float vec3::getMagnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}
vec3 vec3::getNormalized() const {
    // float rsqrt = Q_rsqrt(x * x + y * y + z * z); // Possible optimisation
    float rsqrt = 1 / std::sqrt(x * x + y * y + z * z);
    vec3 res(x * rsqrt, y * rsqrt, z * rsqrt);
    return res;
}

vec3 vec3::operator+() const {
    return vec3(x, y, z);
}
vec3 vec3::operator-() const {
    return vec3(-x, -y, -z);
}

vec3 vec3::operator+(const vec2 &b) const {
    return vec3(x + b.x, y + b.y, z);
}
vec3 vec3::operator+(const vec3 &b) const {
    return vec3(x + b.x, y + b.y, z + b.z);
}
vec4 vec3::operator+(const vec4 &b) const {
    return vec4(x + b.x, y + b.y, z + b.z, b.w);
}

vec3 vec3::operator-(const vec2 &b) const {
    return vec3(x - b.x, y - b.y, z);
}
vec3 vec3::operator-(const vec3 &b) const {
    return vec3(x - b.x, y - b.y, z - b.z);
}
vec4 vec3::operator-(const vec4 &b) const {
    return vec4(x - b.x, y - b.y, z - b.z, -b.w);
}

vec3 vec3::operator*(const float b) const {
    return vec3(x * b, y * b, z * b);
}
vec3 vec3::operator/(const float b) const {
    return vec3(x / b, y / b, z / b);
}


vec3 &vec3::operator+=(const vec3 &b) {
    *this = *this + b;
    return *this;
}
vec3 &vec3::operator-=(const vec3 &b) {
    *this = *this - b;
    return *this;
}

vec3 &vec3::operator*=(const float b) {
    *this = *this * b;
    return *this;
}
vec3 &vec3::operator/=(const float b) {
    *this = *this / b;
    return *this;
}

float vec3::operator[](std::size_t i) const {
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else if (i == 2)
        return z;
    
    return 0.0f;
}