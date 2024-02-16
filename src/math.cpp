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

// == VECTORS ==

// -- VEC 2 --

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

// --       --

// -- VEC 3 --

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

// --       --

// -- VEC 4 --

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

vec4 vec4::point(const float vec) {
    return vec4(vec, 0.0f, 0.0f, 1.0f);
}
vec4 vec4::point(const vec2 &vec) {
    return vec4(vec.x, vec.y, 0.0f, 1.0f);
}
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

// ==         ==

// == MATRICES ==

// -- mat4x4 --

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
    vec4 _1, 
    vec4 _2, 
    vec4 _3, 
    vec4 _4
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

mat4x4 operator*(const float a, const mat4x4 &b) {
    return b * a;
}

// --        --

// ==          ==


// // == COLORS ==

// // -- cRGBA --

// cRGBA::cRGBA() : cRGBA(0.0f, 0.0f, 0.0f, 0.0f) {}
// cRGBA::cRGBA(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
// cRGBA::cRGBA(const cRGBA &col) : cRGBA(col.r, col.g, col.b, col.a) {}

// float *cRGBA::asFloats() {
//     float
// }

// // --       --

// // ==        ==