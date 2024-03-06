#include "elementary/math.h"

#include <cmath>

const vec4 vec4::zero = vec4(0.0f, 0.0f, 0.0f, 0.0f);
const vec4 vec4::one = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 vec4::right = vec4(1.0f, 0.0f, 0.0f, 0.0f);
const vec4 vec4::left = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
const vec4 vec4::up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
const vec4 vec4::down = vec4(0.0f, -1.0f, 0.0f, 0.0f);
const vec4 vec4::forward = vec4(0.0f, 0.0f, 1.0f, 0.0f);
const vec4 vec4::back = vec4(0.0f, 0.0f, -1.0f, 0.0f);
const vec4 vec4::wforward = vec4(0.0f, 0.0f, 0.0f, 1.0f);
const vec4 vec4::wback = vec4(0.0f, 0.0f, 0.0f, -1.0f);

vec4 vec4::point(const vec3 &vec) {
    return vec4(vec.x, vec.y, vec.z, 1.0f);
}
float vec4::dot(const vec4 &a, const vec4& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

vec4::vec4() : vec4(0.0f, 0.0f, 0.0f, 0.0f) {}
vec4::vec4(float x) : vec4(x, 0.0f, 0.0f, 0.0f) {}
vec4::vec4(float x, float y) : vec4(x, y, 0.0f, 0.0f) {}
vec4::vec4(float x, float y, float z) : vec4(x, y, w, 0.0f) {}
vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
vec4::vec4(const vec2 &vec) : vec4(vec.x, vec.y, 0.0f, 0.0f) {}
vec4::vec4(const vec2 &vec, float z) : vec4(vec.x, vec.y, z, 0.0f) {}
vec4::vec4(float x, const vec2 &vec) : vec4(x, vec.x, vec.y, 0.0f) {}
vec4::vec4(const vec2 &vec, float z, float w) : vec4(vec.x, vec.y, z, w) {}
vec4::vec4(float x, const vec2 &vec, float w) : vec4(x, vec.x, vec.y, w) {}
vec4::vec4(float x, float y, const vec2 &vec) : vec4(x, y, vec.x, vec.y) {}
vec4::vec4(const vec2 &vec1, const vec2 &vec2) : vec4(vec1.x, vec1.y, vec2.x, vec2.y) {}
vec4::vec4(const vec3 &vec) : vec4(vec.x, vec.y, vec.z, 0.0f) {}
vec4::vec4(const vec3 &vec, float w) : vec4(vec.x, vec.y, vec.z, w) {}
vec4::vec4(float x, const vec3 &vec) : vec4(x, vec.x, vec.y, vec.z) {}
vec4::vec4(const vec4 &vec) : vec4(vec.x, vec.y, vec.z, vec.w) {}
vec4::vec4(const float a[4]) : vec4(a[0], a[1], a[2], a[3]) {}
vec4::~vec4() {}

float vec4::getMagnitude() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}
vec4 vec4::getNormalized() const {
    // float rsqrt = Q_rsqrt(x * x + y * y + z * z + w * w); // Possible optimisation
    float rsqrt = 1 / std::sqrt(x * x + y * y + z * z + w * w);
    vec4 res(x * rsqrt, y * rsqrt, z * rsqrt, w * rsqrt);
    return res;
}

vec4 vec4::operator+() const {
    return vec4(x, y, z, w);
}
vec4 vec4::operator-() const {
    return vec4(-x, -y, -z, -w);
}

vec4 vec4::operator+(const vec2 &b) const {
    return vec4(x + b.x, y + b.y, z, w);
}
vec4 vec4::operator+(const vec3 &b) const {
    return vec4(x + b.x, y + b.y, z + b.z, w);
}
vec4 vec4::operator+(const vec4 &b) const {
    return vec4(x + b.x, y + b.y, z + b.z, w + b.w);
}

vec4 vec4::operator-(const vec2 &b) const {
    return vec4(x - b.x, y - b.y, z, w);
}
vec4 vec4::operator-(const vec3 &b) const {
    return vec4(x - b.x, y - b.y, z - b.z, w);
}
vec4 vec4::operator-(const vec4 &b) const {
    return vec4(x - b.x, y - b.y, z - b.z, w - b.w);
}

vec4 vec4::operator*(const float b) const {
    return vec4(x * b, y * b, z * b, 0.0f);
}
vec4 vec4::operator/(const float b) const {
    return vec4(x / b, y / b, z / b, w / b);
}

vec4 &vec4::operator+=(const vec4 &b) {
    *this = *this + b;
    return *this;
}
vec4 &vec4::operator-=(const vec4 &b) {
    *this = *this - b;
    return *this;
}

vec4 &vec4::operator*=(const float b) {
    *this = *this * b;
    return *this;
}
vec4 &vec4::operator/=(const float b) {
    *this = *this / b;
    return *this;
}

float vec4::operator[](std::size_t i) const {
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else if (i == 2)
        return z;
    else if (i == 3)
        return w;
    
    return 0.0f;
}