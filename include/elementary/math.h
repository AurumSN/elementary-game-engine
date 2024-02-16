#pragma once

#include <cstring>
#include <iostream>

float Q_rsqrt(float number);

struct vec2;
struct vec3;
struct vec4;

struct vec2 {
    static const vec2 zero;
    static const vec2 one;
    static const vec2 right;
    static const vec2 left;
    static const vec2 up;
    static const vec2 down;

    static float dot(const vec2 &a, const vec2& b);

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

    vec2 operator+(const vec2 &b) const;
    vec3 operator+(const vec3 &b) const;
    vec4 operator+(const vec4 &b) const;

    vec2 operator-(const vec2 &b) const;
    vec3 operator-(const vec3 &b) const;
    vec4 operator-(const vec4 &b) const;

    vec2 operator*(const float b) const;
    vec2 operator/(const float b) const;

    vec2 &operator+=(const vec2 &b);
    vec2 &operator-=(const vec2 &b);

    vec2 &operator*=(const float b);
    vec2 &operator/=(const float b);

    float operator[](std::size_t i) const;
};

struct vec3 {
    static const vec3 zero;
    static const vec3 one;
    static const vec3 right;
    static const vec3 left;
    static const vec3 up;
    static const vec3 down;
    static const vec3 forward;
    static const vec3 back;

    static float dot(const vec3 &a, const vec3& b);
    static vec3 cross(const vec3 &a, const vec3& b);

    float x;
    float y;
    float z;
    
    vec3();
    vec3(float x);
    vec3(float x, float y);
    vec3(float x, float y, float z);
    vec3(const vec2 &vec);
    vec3(const vec2 &vec, float z);
    vec3(float x, const vec2 &vec);
    vec3(const vec3 &vec);
    vec3(const vec4 &vec);
    
    float getMagnitude() const;
    vec3 getNormalized() const;

    vec3 operator+() const;
    vec3 operator-() const;

    vec3 operator+(const vec2 &b) const;
    vec3 operator+(const vec3 &b) const;
    vec4 operator+(const vec4 &b) const;

    vec3 operator-(const vec2 &b) const;
    vec3 operator-(const vec3 &b) const;
    vec4 operator-(const vec4 &b) const;

    vec3 operator*(const float b) const;
    vec3 operator/(const float b) const;

    vec3 &operator+=(const vec3 &b);
    vec3 &operator-=(const vec3 &b);

    vec3 &operator*=(const float b);
    vec3 &operator/=(const float b);

    float operator[](std::size_t i) const;
};

struct vec4 {
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
    static float dot(const vec4 &a, const vec4& b);

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
    vec4(const vec2 &vec, float z);
    vec4(float x, const vec2 &vec);
    vec4(const vec2 &vec, float z, float w);
    vec4(float x, const vec2 &vec, float w);
    vec4(float x, float y, const vec2 &vec);
    vec4(const vec2 &vec1, const vec2 &vec2);
    vec4(const vec3 &vec);
    vec4(const vec3 &vec, float w);
    vec4(float x, const vec3 &vec);
    vec4(const vec4 &vec);
    
    float getMagnitude() const;
    vec4 getNormalized() const;

    vec4 operator+() const;
    vec4 operator-() const;

    vec4 operator+(const vec2 &b) const;
    vec4 operator+(const vec3 &b) const;
    vec4 operator+(const vec4 &b) const;

    vec4 operator-(const vec2 &b) const;
    vec4 operator-(const vec3 &b) const;
    vec4 operator-(const vec4 &b) const;

    vec4 operator*(const float b) const;

    vec4 operator/(const float b) const;

    vec4 &operator+=(const vec4 &b);
    vec4 &operator-=(const vec4 &b);

    vec4 &operator*=(const float b);
    vec4 &operator/=(const float b);

    float operator[](std::size_t i) const;
};

vec2 operator*(const float a, const vec2& b);
vec3 operator*(const float a, const vec3& b);
vec4 operator*(const float a, const vec4& b);

std::ostream& operator<<(std::ostream &a, const vec2 &b);
std::ostream& operator<<(std::ostream &a, const vec3 &b);
std::ostream& operator<<(std::ostream &a, const vec4 &b);

std::istream& operator>>(std::istream &a, vec2 &b);
std::istream& operator>>(std::istream &a, vec3 &b);
std::istream& operator>>(std::istream &a, vec4 &b);

struct mat4x4 {
    static const mat4x4 zero;
    static const mat4x4 one;
    static const mat4x4 identity;

    static mat4x4 translation(const vec3 &t);
    static mat4x4 scale(const vec3 &t);
    static mat4x4 rotationX(float angle);
    static mat4x4 rotationY(float angle);
    static mat4x4 rotationZ(float angle);
    static mat4x4 rotation(float x, float y, float z);
    static mat4x4 orthoLH(float width, float height, float near_plane, float far_plane);

    float mat[4][4] = {}; 
    
    mat4x4();
    mat4x4(
        float _11, float _12, float _13, float _14,
        float _21, float _22, float _23, float _24,
        float _31, float _32, float _33, float _34,
        float _41, float _42, float _43, float _44
    );
    mat4x4(
        vec4 _1, 
        vec4 _2, 
        vec4 _3, 
        vec4 _4
    );
    mat4x4(
        float _1[4], 
        float _2[4], 
        float _3[4], 
        float _4[4]
    );
    mat4x4(const mat4x4 &mat);
    mat4x4(const float mat[4][4]);

    mat4x4 operator+() const;
    mat4x4 operator-() const;

    mat4x4 operator+(const mat4x4 &b) const;
    mat4x4 operator*(const mat4x4 &b) const;
    vec4 operator*(const vec4 &b) const;
    mat4x4 operator*(const float b) const;
    mat4x4 operator/(const float b) const;

    mat4x4 &operator+=(const mat4x4 &b);
    mat4x4 &operator*=(const mat4x4 &b);
    mat4x4 &operator*=(const float b);
    mat4x4 &operator/=(const float b);

    const float *operator[](std::size_t i) const;
    float *operator[](std::size_t i);
};

mat4x4 operator*(const float a, const mat4x4& b);

typedef float cRGBA[4];
typedef float cRGB[3];

struct VERTEX {
    vec3 pos;
    cRGB col;
    cRGB col1;
};