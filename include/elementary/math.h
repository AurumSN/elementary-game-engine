#pragma once

#include <cstring>
#include <iostream>

float Q_rsqrt(float number);

class vec2;
class vec3;
class vec4;

class vec2 {
public:
    static const vec2 zero;
    static const vec2 one;
    static const vec2 right;
    static const vec2 left;
    static const vec2 up;
    static const vec2 down;

    static float dot(const vec2 &a, const float b);
    static float dot(const vec2 &a, const vec2 &b);
    static float dot(const vec2 &a, const vec3 &b);
    static float dot(const vec2 &a, const vec4 &b);

    float x;
    float y;

    vec2();
    vec2(float x);
    vec2(float x, float y);
    vec2(const vec2 &vec);
    vec2(const vec3 &vec);
    vec2(const vec4 &vec);
    
    float getMagnitude()  const;
    vec2  getNormalized() const;

    vec2  operator+ ()              const;
    vec2  operator- ()              const;

    vec2  operator+ (const float b) const;
    vec2  operator+ (const vec2 &b) const;
    vec3  operator+ (const vec3 &b) const;
    vec4  operator+ (const vec4 &b) const;

    vec2  operator- (const float b) const;
    vec2  operator- (const vec2 &b) const;
    vec3  operator- (const vec3 &b) const;
    vec4  operator- (const vec4 &b) const;

    vec2  operator* (const float b) const;
    vec2  operator* (const vec2 &b) const;
    vec3  operator* (const vec3 &b) const;
    vec4  operator* (const vec4 &b) const;

    vec2  operator/ (const float b) const;
    vec2  operator/ (const vec2 &b) const;
    vec3  operator/ (const vec3 &b) const;
    vec4  operator/ (const vec4 &b) const;

    vec2 &operator= (const float b);
    vec2 &operator= (const vec2 &b);
    vec2 &operator= (const vec3 &b);
    vec2 &operator= (const vec4 &b);

    vec2 &operator+=(const float b);
    vec2 &operator+=(const vec2 &b);
    vec2 &operator+=(const vec3 &b);
    vec2 &operator+=(const vec4 &b);

    vec2 &operator-=(const float b);
    vec2 &operator-=(const vec2 &b);
    vec2 &operator-=(const vec3 &b);
    vec2 &operator-=(const vec4 &b);

    vec2 &operator*=(const float b);
    vec2 &operator*=(const vec2 &b);
    vec2 &operator*=(const vec3 &b);
    vec2 &operator*=(const vec4 &b);

    vec2 &operator/=(const float b);
    vec2 &operator/=(const vec2 &b);
    vec2 &operator/=(const vec3 &b);
    vec2 &operator/=(const vec4 &b);

    float operator[](std::size_t i) const;
};

// TODO
class vec3 {
public:
    float x;
    float y;
    float z;
    
    vec3();
    vec3(float);
    vec3(float, float);
    vec3(float, float, float);
    vec3(const vec2&);
    vec3(const vec3&);
    vec3(const vec4&);

    vec3 operator*(const float b) const;
};

// TODO
class vec4 {
public:
    float x;
    float y;
    float z;
    float w;

    vec4();
    vec4(float);
    vec4(float, float);
    vec4(float, float, float);
    vec4(float, float, float, float);
    vec4(const vec2&);
    vec4(const vec3&);
    vec4(const vec4&);
    
    vec4 operator*(const float b) const;
};

vec2 operator*(const float a, const vec2& b);
vec3 operator*(const float a, const vec3& b);
vec4 operator*(const float a, const vec4& b);
vec2 operator/(const float a, const vec2& b);
vec3 operator/(const float a, const vec3& b);
vec4 operator/(const float a, const vec4& b);

std::ostream& operator<<(std::ostream &a, const vec2 &b);
std::ostream& operator<<(std::ostream &a, const vec3 &b);
std::ostream& operator<<(std::ostream &a, const vec4 &b);
std::istream& operator>>(std::istream &a,       vec2 &b);
std::istream& operator>>(std::istream &a,       vec3 &b);
std::istream& operator>>(std::istream &a,       vec4 &b);