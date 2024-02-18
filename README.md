# elementary-game-engine

## Math
### Vector classes (`vec2`, `vec3`, `vec4`)

#### 2-D vector class (`vec2`)

Constants:
- `vec2 vec2::zero` - Vector with magnitude of 0
- `vec2 vec2::one` - Vector with 1 for both coordinates
- `vec2 vec2::right` - Vector pointing right
- `vec2 vec2::left` - Vector pointing left
- `vec2 vec2::up` - Vector pointing up
- `vec2 vec2::down` - Vector pointing down

Static functions:
- `vec2::dot(vec2 a, vec2 b)` - returns dot product of 2 vectors (aka $a_xb_x+a_yb_y$ or $|a||b|cos\alpha$ where $\alpha$ is angle between vector a and b)

Parameters:
- `float x`
- `float y`

Initialization:
- `vec2()` - creating a ***zero*** vector
- `vec2(float x)` - creating a vector with ***x*** as its first coordinate
- `vec2(float x, float y)` - creating a vector with ***x*** as its first coordinate and ***y*** as its second
- `vec2(const vec2& vec)` - creating a vector based on another vector
- `vec2(const vec3& vec)` - creating a vector based on another vector
- `vec2(const vec4& vec)` - creating a vector based on another vector

Class functions:
- `float getMagnitude()` - returns the magnitude of the vector
- `vec2 getNormalized()` - returns normalized vector

Operators:
- `+a` - returns copy of the vector
- `-a` - returns the opposite vector
- `a + b` - returns sum of 2 vectors
- `a - b` - returns difference of 2 vectors
- `a * b` - returns **a** with length multiplied by **b**
- `a / b` - returns **a** with length divided by **b**
- `a += b` - assignes the sum of ***a*** and ***b*** to vector ***a***
- `a -= b` - assignes the difference of ***a*** and ***b*** to vector ***a***
- `a *= b` - assignes the product of ***a*** and ***b*** to vector ***a***
- `a /= b` - assignes the dividend of ***a*** and ***b*** to vector ***a***
- `a[i]` - returns the ***i***-th coordinate of the vector

#### 3-D vector class (`vec3`)

Constants:
- `vec3 vec3::zero` - Vector with magnitude of 0
- `vec3 vec3::one` - Vector with 1 for both coordinates
- `vec3 vec3::right` - Vector pointing right
- `vec3 vec3::left` - Vector pointing left
- `vec3 vec3::up` - Vector pointing up
- `vec3 vec3::down` - Vector pointing down
- `vec3 vec3::forward` - Vector pointing forward
- `vec3 vec3::back` - Vector pointing back

Static functions:
- `float vec3::dot(const vec3 &a, const vec3 &b)` - returns dot product of 2 vectors (aka $a_xb_x+a_yb_y+a_zb_z$ or $|a||b|cos\alpha$ where $\alpha$ is angle between vector a and b)
- `vec3 vec3::cross(const vec3 &a, const vec3 &b)` - returns cross product of 2 vectors (aka a vector peerpendicular to a and b and whose length is equal to $|a||b|sin\alpha$ where $\alpha$ is angle between vector a and b)

Parameters:
- `float x`
- `float y`
- `float z`

Initialization:
- `vec3()` - creating a ***zero*** vector
- `vec3(float x)` - creating a vector with ***x*** as its first coordinate
- `vec3(float x, float y)` - creating a vector with ***x*** as its first coordinate and ***y*** as its second
- `vec3(float x, float y, float z)` - creating a vector with ***x*** as its first coordinate, ***y*** as its second and ***z*** as its third
- `vec3(const vec2& vec)` - creating a vector with ***vec*** as its first 2 coordinates
- `vec3(const vec2& vec, float z)` - creating a vector with ***vec*** as its first 2 coordinates and ***z*** as third
- `vec3(float x, const vec2& vec)` - creating a vector with ***x*** as its first coordinate and ***vec*** as last 2
- `vec3(const vec3& vec)` - creating a vector based on another vector
- `vec3(const vec4& vec)` - creating a vector based on another vector

Class functions:
- `float getMagnitude()` - returns the magnitude of the vector
- `vec3 getNormalized()` - returns normalized vector

Operators:
- `+a` - returns copy of the vector
- `-a` - returns the opposite vector
- `a + b` - returns sum of 2 vectors
- `a - b` - returns difference of 2 vectors
- `a * b` - returns **a** with length multiplied by **b**
- `a / b` - returns **a** with length divided by **b**
- `a += b` - assignes the sum of ***a*** and ***b*** to vector ***a***
- `a -= b` - assignes the difference of ***a*** and ***b*** to vector ***a***
- `a *= b` - assignes the product of ***a*** and ***b*** to vector ***a***
- `a /= b` - assignes the dividend of ***a*** and ***b*** to vector ***a***
- `a[i]` - returns the ***i***-th coordinate of the vector

#### 4-D vector class (`vec4`)

Constants:
- `vec4 vec4::zero` - Vector with magnitude of 0
- `vec4 vec4::one` - Vector with 1 for both coordinates
- `vec4 vec4::right` - Vector pointing right
- `vec4 vec4::left` - Vector pointing left
- `vec4 vec4::up` - Vector pointing up
- `vec4 vec4::down` - Vector pointing down
- `vec4 vec4::forward` - Vector pointing forward
- `vec4 vec4::back` - Vector pointing back
- `vec4 vec4::wforward` - Vector pointing forward in 4-th dimension
- `vec4 vec4::wback` - Vector pointing back in 4-th dimension

Global functions:
- `vec4 vec4::point(const vec3 &vec)` - returns ***vec*** as a 3-D point (aka 4-D vector with 4-th coordinate being equal to 1)
- `float vec4::dot(const vec4 &a, const vec4 &b)` - returns dot product of 2 vectors (aka $a_xb_x+a_yb_y+a_zb_z+a_wb_w$ or $|a||b|cos\alpha$ where $\alpha$ is angle between vector a and b)

Parameters:
- `float x`
- `float y`
- `float z`
- `float w`

Initialization:
- `vec4()` - creating a ***zero*** vector
- `vec4(float x)` - creating a vector with ***x*** as its first coordinate
- `vec4(float x, float y)` - creating a vector with ***x*** as its first coordinate and ***y*** as its second
- `vec4(float x, float y, float z)` - creating a vector with ***x*** as its first coordinate, ***y*** as its second and ***z*** as its third
- `vec4(float x, float y, float z, float w)` - creating a vector with ***x*** as its first coordinate, ***y*** as its second, ***z*** as its third and ***w*** as its fourth
- `vec4(const vec2& vec)` - creating a vector with ***vec*** as its first 2 coordinates
- `vec4(const vec2& vec, float z)` - creating a vector with ***vec*** as its first 2 coordinates and ***z*** as third
- `vec4(float x, const vec2& vec)` - creating a vector with ***x*** as its first coordinate and ***vec*** as middle 2
- `vec4(const vec2& vec, float z, float w)` - creating a vector with ***vec*** as its first 2 coordinates and ***z*** and ***w*** as its last 2
- `vec4(float x, const vec2& vec, float w)` - creating a vector with ***x*** as its first coordinate, ***vec*** as middle 2 and ***w*** as fourth
- `vec4(float x, float y, const vec2& vec)` - creating a vector with ***x*** and ***y*** as its first 2 coordinates and ***vec*** as its last 2
- `vec4(const vec3& vec)` - creating a vector with ***vec*** as its first 3 coordinates
- `vec4(const vec3& vec, float w)` - creating a vector with ***vec*** as its first 3 coordinates and ***w*** as fourth
- `vec4(float x, const vec3& vec)` - creating a vector with ***x*** as its first coordinate and ***vec*** as last 3
- `vec4(const vec4& vec)` - creating a vector based on another vector

Class functions:
- `float getMagnitude()` - returns the magnitude of the vector
- `vec4 getNormalized()` - returns normalized vector

Operators:
- `+a` - returns copy of the vector
- `-a` - returns the opposite vector
- `a + b` - returns sum of 2 vectors
- `a - b` - returns difference of 2 vectors
- `a * b` - returns **a** with length multiplied by **b**
- `a / b` - returns **a** with length divided by **b**
- `a += b` - assignes the sum of ***a*** and ***b*** to vector ***a***
- `a -= b` - assignes the difference of ***a*** and ***b*** to vector ***a***
- `a *= b` - assignes the product of ***a*** and ***b*** to vector ***a***
- `a /= b` - assignes the dividend of ***a*** and ***b*** to vector ***a***
- `a[i]` - returns the ***i***-th coordinate of the vector

### Matrix class (`mat4x4`)

Constants:
- `mat4x4::zero` - Zero matrix
- `mat4x4::one` - Matrix with ones in every cell
- `mat4x4::identity` - Identity matrix

Static functions:
- `mat4x4 mat4x4::translation(const vec3 &t)` - Returns a translation matrix
- `mat4x4 mat4x4::scale(const vec3 &t);` - Returns a scalar matrix
- `mat4x4 mat4x4::rotationX(float angle);` - Return rotation matrix around the X axis
- `mat4x4 mat4x4::rotationY(float angle);` - Return rotation matrix around the Y axis
- `mat4x4 mat4x4::rotationZ(float angle);` - Return rotation matrix around the Z axis
- `mat4x4 mat4x4::rotation(float x, float y, float z);` - Return rotation matrix
- `mat4x4 mat4x4::orthoLH(float width, float height, float near_plane, float far_plane);` - Return orthographics projection matrix

Initialization:
- `mat4x4()` - creating a ***zero*** matrix
- `mat4x4(float _11, ..., float _44)` - creating a matrix with ***_11, ..., _44*** in its cells
- `mat4x4(const vec4 &vec4 _1, ..., const vec4 &vec4 _4)` - creating a matrix with ***_1, ..., _4*** as its rows
- `mat4x4(float _1[4], ..., float _4[4])` - creating a matrix with ***_1, ..., _4*** as its rows
- `mat4x4(const mat4x4 &mat)` - creating a matrix based on another matrix
- `mat4x4(const float mat[4][4])` - creating a matrix based on a 2-D array

Operators:
- `+a` - returns copy of the matrix
- `-a` - returns the opposite matrix
- `a + b` - returns sum of 2 matrices
- `a - b` - returns difference of 2 matrices
- `a * b` - if either ***a*** or ***b*** is a `float` the result would be a matrix scaled by the factor, otherwise returns the product of 2 matrices or of a matrix and a vector
- `a / b` - returns matrix ***a*** scaled down by ***b***
- `a = b` - assignes parameters of matrix ***b*** to matrix ***a***
- `a += b` - assignes the sum of ***a*** and ***b*** to matrix ***a***
- `a -= b` - assignes the difference of ***a*** and ***b*** to matrix ***a***
- `a *= b` - assignes the product of ***a*** and ***b*** to matrix ***a***
- `a /= b` - assignes the dividend of ***a*** and ***b*** to matrix ***a***
- `a[i]` - returns the ***i***-th row of the matrix

## Window
### `WindowProc`
Function used for window procedure.

### Window class (`Window`)
Initialization:
- `Window()`

Class functions:
- `bool Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)` - Initializes the window class
- `bool Release()` - Releases the data
- `int MessageLoop()` - Loops through messages
- `bool isRunning()` - Returns true if the window is running, false otherwise
- `void onCreate()` - Runs every time the window is created
- `void onUpdate()` - Runs every time the window is updated
- `void onDestroy()` - Runs every time the window is destroyed
- `void onFocus()` - Runs every time the window is focused
- `void onKillFocus()` - Runs every time the focuse is killed
- `RECT getClientWindowRect()` - Returns the size of the window
- `HWND getHWND()` - Returns the `hWnd` of the class
- `void setHWND(HWND hWnd)` - Sets the `hWnd` of the class

Protected parameters:
- `HWND hWnd`
- `bool bRunning`