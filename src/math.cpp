#include "elementary/math.h"

#include <cstring>
#include <cmath>

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

// -- VEC 2 --

const vec2 vec2::zero = vec2(0.0f, 0.0f);
const vec2 vec2::one = vec2(1.0f, 1.0f);
const vec2 vec2::right = vec2(1.0f, 0.0f);
const vec2 vec2::left = vec2(-1.0f, 0.0f);
const vec2 vec2::up = vec2(0.0f, 1.0f);
const vec2 vec2::down = vec2(0.0f, -1.0f);

float vec2::dot(const vec2 &a, const vec2 &b) {
    return a.x * b.x + a.y * b.y;
}

vec2::vec2() : x(0.0f), y(0.0f) {}
vec2::vec2(float x) : x(x), y(0.0f) {}
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

vec2 vec2::operator+(const float b) const {
    return vec2(x + b, y);
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

vec2 vec2::operator-(const float b) const {
    return vec2(x - b, y);
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
vec2 vec2::operator*(const vec2 &b) const {
    return vec2(x * b.x, y * b.y);
}
vec3 vec2::operator*(const vec3 &b) const {
    return vec3(x * b.x, y * b.y, 0.0f);
}
vec4 vec2::operator*(const vec4 &b) const {
    return vec4(x * b.x, y * b.y, 0.0f, 0.0f);
}

vec2 vec2::operator/(const float b) const {
    return vec2(x / b, y / b);
}
vec2 vec2::operator/(const vec2 &b) const {
    return vec2(x / b.x, y / b.y);
}
vec3 vec2::operator/(const vec3 &b) const {
    return vec3(x / b.x, y / b.y, 0.0f);
}
vec4 vec2::operator/(const vec4 &b) const {
    return vec4(x / b.x, y / b.y, 0.0f);
}

vec2 &vec2::operator=(const float b) {
    x = b;
    y = 0;
    return *this;
}
vec2 &vec2::operator=(const vec2 &b) {
    x = b.x;
    y = b.y;
    return *this;
}
vec2 &vec2::operator=(const vec3 &b) {
    x = b.x;
    y = b.y;
    return *this;
}
vec2 &vec2::operator=(const vec4 &b) {
    x = b.x;
    y = b.y;
    return *this;
}

vec2 &vec2::operator+=(const float b) {
    *this = *this + b;
    return *this;
}
vec2 &vec2::operator+=(const vec2 &b) {
    *this = *this + b;
    return *this;
}
vec2 &vec2::operator+=(const vec3 &b) {
    *this = *this + b;
    return *this;
}
vec2 &vec2::operator+=(const vec4 &b) {
    *this = *this + b;
    return *this;
}

vec2 &vec2::operator-=(const float b) {
    *this = *this - b;
    return *this;
}
vec2 &vec2::operator-=(const vec2 &b) {
    *this = *this - b;
    return *this;
}
vec2 &vec2::operator-=(const vec3 &b) {
    *this = *this - b;
    return *this;
}
vec2 &vec2::operator-=(const vec4 &b) {
    *this = *this - b;
    return *this;
}

vec2 &vec2::operator*=(const float b) {
    *this = *this * b;
    return *this;
}
vec2 &vec2::operator*=(const vec2 &b) {
    *this = *this * b;
    return *this;
}
vec2 &vec2::operator*=(const vec3 &b) {
    *this = *this * b;
    return *this;
}
vec2 &vec2::operator*=(const vec4 &b) {
    *this = *this * b;
    return *this;
}

vec2 &vec2::operator/=(const float b) {
    *this = *this / b;
    return *this;
}
vec2 &vec2::operator/=(const vec2 &b) {
    *this = *this / b;
    return *this;
}
vec2 &vec2::operator/=(const vec3 &b) {
    *this = *this / b;
    return *this;
}
vec2 &vec2::operator/=(const vec4 &b) {
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

// --       --

// -- VEC 3 --

// --       --

// -- VEC 4 --

// --       --

vec2 operator*(const float a, const vec2& b) {
    return b * a;
}
vec3 operator*(const float a, const vec3& b) {
    return b * a;
}
vec4 operator*(const float a, const vec4& b) {
    return b * a;
}
vec2 operator/(const float a, const vec2& b) {
    return vec2(a / b.x, 0.0f);
}
vec3 operator/(const float a, const vec3& b) {
    return vec3(a / b.x, 0.0f, 0.0f);
}
vec4 operator/(const float a, const vec4& b) {
    return vec4(a / b.x, 0.0f, 0.0f, 0.0f);
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