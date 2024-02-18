#include "elementary/math.h"

#include <cstring>
#include <cmath>

const mat4x4 mat4x4::zero = mat4x4(
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f
);
const mat4x4 mat4x4::one = mat4x4(
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f
);
const mat4x4 mat4x4::identity = mat4x4(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

mat4x4 mat4x4::translation(const vec3 &t) {
    mat4x4 retval = identity;

    retval[3][0] = t.x;
    retval[3][1] = t.y;
    retval[3][2] = t.z;

    return retval;
}

mat4x4 mat4x4::scale(const vec3 &t) {
    mat4x4 retval = identity;

    retval[0][0] = t.x;
    retval[1][1] = t.y;
    retval[2][2] = t.z;

    return retval;
}

mat4x4 mat4x4::rotationX(float angle) {
    mat4x4 retval = identity;

    retval[1][1] = cos(angle);
    retval[1][2] = sin(angle);
    retval[2][1] = -sin(angle);
    retval[2][2] = cos(angle);

    return retval;
}

mat4x4 mat4x4::rotationY(float angle) {
    mat4x4 retval = identity;

    retval[0][0] = cos(angle);
    retval[2][0] = sin(angle);
    retval[0][2] = -sin(angle);
    retval[2][2] = cos(angle);

    return retval;
}

mat4x4 mat4x4::rotationZ(float angle) {
    mat4x4 retval = identity;

    retval[0][0] = cos(angle);
    retval[0][1] = sin(angle);
    retval[1][0] = -sin(angle);
    retval[1][1] = cos(angle);

    return retval;
}

mat4x4 mat4x4::rotation(float x, float y, float z) {
    return rotationZ(z) * rotationY(y) * rotationX(x);
}
mat4x4 mat4x4::orthoLH(float width, float height, float near_plane, float far_plane) {
    mat4x4 retval = identity;

    retval[0][0] = 2.0f / width;
    retval[1][1] = 2.0f / height;
    retval[2][2] = 1.0f / (far_plane - near_plane);
    retval[3][2] = -near_plane / (far_plane - near_plane);

    return retval;
}

mat4x4::mat4x4() : mat4x4(
    0.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 0.0f
) {}
mat4x4::mat4x4(
    float _11, float _12, float _13, float _14,
    float _21, float _22, float _23, float _24,
    float _31, float _32, float _33, float _34,
    float _41, float _42, float _43, float _44
) {
    mat[0][0] = _11;
    mat[0][1] = _12;
    mat[0][2] = _13;
    mat[0][3] = _14;
    mat[1][0] = _21;
    mat[1][1] = _22;
    mat[1][2] = _23;
    mat[1][3] = _24;
    mat[2][0] = _31;
    mat[2][1] = _32;
    mat[2][2] = _33;
    mat[2][3] = _34;
    mat[3][0] = _41;
    mat[3][1] = _42;
    mat[3][2] = _43;
    mat[3][3] = _44;
}
mat4x4::mat4x4(
    const vec4 &_1, 
    const vec4 &_2, 
    const vec4 &_3, 
    const vec4 &_4
) : mat4x4(
    _1.x, _1.y, _1.z, _1.w, 
    _2.x, _2.y, _2.z, _2.w, 
    _3.x, _3.y, _3.z, _3.w, 
    _4.x, _4.y, _4.z, _4.w
) {}
mat4x4::mat4x4(
    float _1[4], 
    float _2[4], 
    float _3[4], 
    float _4[4]
) : mat4x4(
    _1[0], _1[1], _1[2], _1[3], 
    _2[0], _2[1], _2[2], _2[3], 
    _3[0], _3[1], _3[2], _3[3], 
    _4[0], _4[1], _4[2], _4[3]
) {}
mat4x4::mat4x4(const mat4x4 &mat) : mat4x4(mat.mat) {}
mat4x4::mat4x4(const float mat[4][4]) {
    std::memcpy(this->mat, mat, sizeof(float) * 4 * 4);
}

mat4x4 mat4x4::operator+() const {
    return mat4x4(
        mat[0][0], mat[0][1], mat[0][2], mat[0][3],
        mat[1][0], mat[1][1], mat[1][2], mat[1][3],
        mat[2][0], mat[2][1], mat[2][2], mat[2][3],
        mat[3][0], mat[3][1], mat[3][2], mat[3][3]
    );
}
mat4x4 mat4x4::operator-() const {
    return mat4x4(
        -mat[0][0], -mat[0][1], -mat[0][2], -mat[0][3],
        -mat[1][0], -mat[1][1], -mat[1][2], -mat[1][3],
        -mat[2][0], -mat[2][1], -mat[2][2], -mat[2][3],
        -mat[3][0], -mat[3][1], -mat[3][2], -mat[3][3]
    );
}

mat4x4 mat4x4::operator+(const mat4x4 &b) const {
    mat4x4 retval = zero;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            retval[i][j] = mat[i][j] + b[i][j];
    return retval;
}
mat4x4 mat4x4::operator*(const mat4x4 &b) const {
    mat4x4 retval = zero;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            retval[i][j] = mat[i][0] * b[0][j] + mat[i][1] * b[1][j] + mat[i][2] * b[2][j] + mat[i][3] * b[3][j];
    return retval;
}
vec4 mat4x4::operator*(const vec4 &b) const {
    vec4 retval = vec4::zero;
    retval.x = mat[0][0] * b.x + mat[0][1] * b.y + mat[0][2] * b.z + mat[0][3] * b.w;
    retval.y = mat[1][0] * b.x + mat[1][1] * b.y + mat[1][2] * b.z + mat[1][3] * b.w;
    retval.z = mat[2][0] * b.x + mat[2][1] * b.y + mat[2][2] * b.z + mat[2][3] * b.w;
    retval.w = mat[3][0] * b.x + mat[3][1] * b.y + mat[3][2] * b.z + mat[3][3] * b.w;
    return retval;
}
mat4x4 mat4x4::operator*(const float b) const {
    mat4x4 retval = zero;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            retval[i][j] = mat[i][j] * b;
    return retval;
}
mat4x4 mat4x4::operator/(const float b) const {
    mat4x4 retval = zero;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            retval[i][j] = mat[i][j] / b;
    return retval;
}

mat4x4 &mat4x4::operator+=(const mat4x4 &b) {
    *this = *this + b;
    return *this;
}
mat4x4 &mat4x4::operator*=(const mat4x4 &b) {
    *this = *this * b;
    return *this;
}
mat4x4 &mat4x4::operator*=(const float b) {
    *this = *this * b;
    return *this;
}
mat4x4 &mat4x4::operator/=(const float b) {
    *this = *this / b;
    return *this;
}

const float *mat4x4::operator[](std::size_t i) const {
    return &mat[i][0];
}

float *mat4x4::operator[](std::size_t i) {
    return &mat[i][0];
}