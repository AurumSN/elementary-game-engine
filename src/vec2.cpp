#include "elementary/math.h"

#include <cmath>

const vec2 vec2::zero = vec2(0.0f, 0.0f);
const vec2 vec2::one = vec2(1.0f, 1.0f);
const vec2 vec2::right = vec2(1.0f, 0.0f);
const vec2 vec2::left = vec2(-1.0f, 0.0f);
const vec2 vec2::up = vec2(0.0f, 1.0f);
const vec2 vec2::down = vec2(0.0f, -1.0f);

float vec2::dot(const vec2 &a, const vec2& b) {
    return a.x * b.x + a.y * b.y;
}

vec2::vec2() : vec2(0.0f, 0.0f) {}
vec2::vec2(float x) : vec2(x, 0.0f) {}
vec2::vec2(float x, float y) : x(x), y(y) {}
vec2::vec2(const vec2 &vec) : vec2(vec.x, vec.y) {}
vec2::vec2(const vec3 &vec) : vec2(vec.x, vec.y) {}
vec2::vec2(const vec4 &vec) : vec2(vec.x, vec.y) {}

float vec2::getMagnitude() const {
    return std::sqrt(x * x + y * y);
}
vec2 vec2::getNormalized() const {
    // float rsqrt = Q_rsqrt(x * x + y * y); // Possible optimisation
    float rsqrt = 1 / std::sqrt(x * x + y * y);
    vec2 res(x * rsqrt, y * rsqrt);
    return res;
}

vec2 vec2::operator+() const {
    return vec2(x, y);
}
vec2 vec2::operator-() const {
    return vec2(-x, -y);
}

vec2 vec2::operator+(const vec2 &b) const {
    return vec2(x + b.x, y + b.y);
}
vec3 vec2::operator+(const vec3 &b) const {
    return vec3(x + b.x, y + b.y, b.z);
}
vec4 vec2::operator+(const vec4 &b) const {
    return vec4(x + b.x, y + b.y, b.z, b.w);
}

vec2 vec2::operator-(const vec2 &b) const {
    return vec2(x - b.x, y - b.y);
}
vec3 vec2::operator-(const vec3 &b) const {
    return vec3(x - b.x, y - b.y, -b.z);
}
vec4 vec2::operator-(const vec4 &b) const {
    return vec4(x - b.x, y - b.y, -b.z, -b.w);
}

vec2 vec2::operator*(const float b) const {
    return vec2(x * b, y * b);
}
vec2 vec2::operator/(const float b) const {
    return vec2(x / b, y / b);
}

vec2 &vec2::operator+=(const vec2 &b) {
    *this = *this + b;
    return *this;
}
vec2 &vec2::operator-=(const vec2 &b) {
    *this = *this - b;
    return *this;
}

vec2 &vec2::operator*=(const float b) {
    *this = *this * b;
    return *this;
}
vec2 &vec2::operator/=(const float b) {
    *this = *this / b;
    return *this;
}

float vec2::operator[](std::size_t i) const {
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    
    return 0.0f;
}