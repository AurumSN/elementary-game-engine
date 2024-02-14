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

    float x;
    float y;

    vec2();
    vec2(float x);
    vec2(float x, float y);
    vec2(const vec2 &vec);
    vec2(const vec3 &vec);
    vec2(const vec4 &vec);
    
    float getMagnitude() const;
    vec2 getNormalized() const;

    vec2 operator+() const;
    vec2 operator-() const;

    vec2 operator+(const float b) const;
    vec2 operator+(const vec2 &b) const;
    vec3 operator+(const vec3 &b) const;
    vec4 operator+(const vec4 &b) const;

    vec2 operator-(const float b) const;
    vec2 operator-(const vec2 &b) const;
    vec3 operator-(const vec3 &b) const;
    vec4 operator-(const vec4 &b) const;

    vec2 operator*(const float b) const;
    vec2 operator*(const vec2 &b) const;
    vec3 operator*(const vec3 &b) const;
    vec4 operator*(const vec4 &b) const;

    vec2 operator/(const float b) const;
    vec2 operator/(const vec2 &b) const;
    vec3 operator/(const vec3 &b) const;
    vec4 operator/(const vec4 &b) const;

    vec2 &operator=(const float b);
    vec2 &operator=(const vec2 &b);
    vec2 &operator=(const vec3 &b);
    vec2 &operator=(const vec4 &b);

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

class vec3 {
public:
    static const vec3 zero;
    static const vec3 one;
    static const vec3 right;
    static const vec3 left;
    static const vec3 up;
    static const vec3 down;
    static const vec3 forward;
    static const vec3 back;

    float x;
    float y;
    float z;
    
    vec3();
    vec3(float x);
    vec3(float x, float y);
    vec3(float x, float y, float z);
    vec3(const vec2 &vec);
    vec3(const vec3 &vec);
    vec3(const vec4 &vec);
    
    float getMagnitude() const;
    vec3 getNormalized() const;

    vec3 operator+() const;
    vec3 operator-() const;

    vec3 operator+(const float b) const;
    vec3 operator+(const vec2 &b) const;
    vec3 operator+(const vec3 &b) const;
    vec4 operator+(const vec4 &b) const;

    vec3 operator-(const float b) const;
    vec3 operator-(const vec2 &b) const;
    vec3 operator-(const vec3 &b) const;
    vec4 operator-(const vec4 &b) const;

    vec3 operator*(const float b) const;
    vec3 operator*(const vec2 &b) const;
    vec3 operator*(const vec3 &b) const;
    vec4 operator*(const vec4 &b) const;

    vec3 operator/(const float b) const;
    vec3 operator/(const vec2 &b) const;
    vec3 operator/(const vec3 &b) const;
    vec4 operator/(const vec4 &b) const;

    vec3 &operator=(const float b);
    vec3 &operator=(const vec2 &b);
    vec3 &operator=(const vec3 &b);
    vec3 &operator=(const vec4 &b);

    vec3 &operator+=(const float b);
    vec3 &operator+=(const vec2 &b);
    vec3 &operator+=(const vec3 &b);
    vec3 &operator+=(const vec4 &b);

    vec3 &operator-=(const float b);
    vec3 &operator-=(const vec2 &b);
    vec3 &operator-=(const vec3 &b);
    vec3 &operator-=(const vec4 &b);

    vec3 &operator*=(const float b);
    vec3 &operator*=(const vec2 &b);
    vec3 &operator*=(const vec3 &b);
    vec3 &operator*=(const vec4 &b);

    vec3 &operator/=(const float b);
    vec3 &operator/=(const vec2 &b);
    vec3 &operator/=(const vec3 &b);
    vec3 &operator/=(const vec4 &b);

    float operator[](std::size_t i) const;
};

class vec4 {
public:
    static const vec4 zero;
    static const vec4 one;
    static const vec4 right;
    static const vec4 left;
    static const vec4 up;
    static const vec4 down;
    static const vec4 forward;
    static const vec4 back;
    static const vec4 wforward;
    static const vec4 wback;

    static vec4 point(const float vec);
    static vec4 point(const vec2 &vec);
    static vec4 point(const vec3 &vec);

    float x;
    float y;
    float z;
    float w;

    vec4();
    vec4(float x);
    vec4(float x, float y);
    vec4(float x, float y, float z);
    vec4(float x, float y, float z, float w);
    vec4(const vec2 &vec);
    vec4(const vec3 &vec);
    vec4(const vec4 &vec);
    
    float getMagnitude() const;
    vec4 getNormalized() const;

    vec4 operator+() const;
    vec4 operator-() const;

    vec4 operator+(const float b) const;
    vec4 operator+(const vec2 &b) const;
    vec4 operator+(const vec3 &b) const;
    vec4 operator+(const vec4 &b) const;

    vec4 operator-(const float b) const;
    vec4 operator-(const vec2 &b) const;
    vec4 operator-(const vec3 &b) const;
    vec4 operator-(const vec4 &b) const;

    vec4 operator*(const float b) const;
    vec4 operator*(const vec2 &b) const;
    vec4 operator*(const vec3 &b) const;
    vec4 operator*(const vec4 &b) const;

    vec4 operator/(const float b) const;
    vec4 operator/(const vec2 &b) const;
    vec4 operator/(const vec3 &b) const;
    vec4 operator/(const vec4 &b) const;

    vec4 &operator=(const float b);
    vec4 &operator=(const vec2 &b);
    vec4 &operator=(const vec3 &b);
    vec4 &operator=(const vec4 &b);

    vec4 &operator+=(const float b);
    vec4 &operator+=(const vec2 &b);
    vec4 &operator+=(const vec3 &b);
    vec4 &operator+=(const vec4 &b);

    vec4 &operator-=(const float b);
    vec4 &operator-=(const vec2 &b);
    vec4 &operator-=(const vec3 &b);
    vec4 &operator-=(const vec4 &b);

    vec4 &operator*=(const float b);
    vec4 &operator*=(const vec2 &b);
    vec4 &operator*=(const vec3 &b);
    vec4 &operator*=(const vec4 &b);

    vec4 &operator/=(const float b);
    vec4 &operator/=(const vec2 &b);
    vec4 &operator/=(const vec3 &b);
    vec4 &operator/=(const vec4 &b);

    float operator[](std::size_t i) const;
};

float dot(const float a, const float b);
float dot(const float a, const vec2 &b);
float dot(const float a, const vec3 &b);
float dot(const float a, const vec4 &b);
float dot(const vec2 &a, const float b);
float dot(const vec2 &a, const vec2 &b);
float dot(const vec2 &a, const vec3 &b);
float dot(const vec2 &a, const vec4 &b);
float dot(const vec3 &a, const float b);
float dot(const vec3 &a, const vec2 &b);
float dot(const vec3 &a, const vec3 &b);
float dot(const vec3 &a, const vec4 &b);
float dot(const vec4 &a, const float b);
float dot(const vec4 &a, const vec2 &b);
float dot(const vec4 &a, const vec3 &b);
float dot(const vec4 &a, const vec4 &b);

vec2 operator*(const float a, const vec2& b);
vec3 operator*(const float a, const vec3& b);
vec4 operator*(const float a, const vec4& b);
vec2 operator/(const float a, const vec2& b);
vec3 operator/(const float a, const vec3& b);
vec4 operator/(const float a, const vec4& b);

std::ostream& operator<<(std::ostream &a, const vec2 &b);
std::ostream& operator<<(std::ostream &a, const vec3 &b);
std::ostream& operator<<(std::ostream &a, const vec4 &b);

std::istream& operator>>(std::istream &a, vec2 &b);
std::istream& operator>>(std::istream &a, vec3 &b);
std::istream& operator>>(std::istream &a, vec4 &b);