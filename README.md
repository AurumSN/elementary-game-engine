# elementary-game-engine

## Math
### Vector classes (`vec2`, `vec3`, `vec4`)
#### Common
> `vecX` represents either `vec2`, `vec3` or `vec4` and sometimes even `float` (equivalent to `vec1`)
 
Constants:
- `zero` - Vector with magnitude of 0
- `one` - Vector with 1 for both coordinates
- `right` - Vector pointing right
- `left` - Vector pointing left
- `up` - Vector pointing up
- `down` - Vector pointing down

Global functions:
- `dot(vecX a, vecX b)` - returns dot product of 2 vectors

Initialization:
- `vecX()` - creating a ***zero*** vector
- `vecX(float x)` - creating a vector with ***x*** as its first coordinate
- `vecX(float x, float y)` - creating a vector with ***x*** as its first coordinate and ***y*** as its second
- `vecX(const vecX& vec)` - creating a vector based on another vector
  
Class functions:
- `float getMagnitude()` - returns the magnitude of the vector
- `vecX getNormalized()` - returns normalized vector

Operators:
- `+a` - returns copy of the vector
- `-a` - returns the opposite vector
- `a + b` - returns sum of 2 vectors
- `a - b` - returns difference of 2 vectors
- `a * b` - if either ***a*** or ***b*** is a `float` the result would be a vector scaled by the factor, otherwise returns the product of 2 vectors
- `a / b` - if ***b*** is a `float` the result would be a vector divided by the factor, otherwise returns the dividend of 2 vectors
- `a = b` - assignes parameters of vector ***b*** to vector ***a***
- `a += b` - assignes the sum of ***a*** and ***b*** to vector ***a***
- `a -= b` - assignes the difference of ***a*** and ***b*** to vector ***a***
- `a *= b` - assignes the product of ***a*** and ***b*** to vector ***a***
- `a /= b` - assignes the dividend of ***a*** and ***b*** to vector ***a***
- `a[i]` - returns the ***i***-th coordinate of the vector


#### 2-D vector class (`vec2`)

Parameters:
- `x`
- `y`

#### 3-D vector class (`vec3`)

Constants:
- `forward` - Vector pointing forward
- `back` - Vector pointing back

Parameters:
- `x`
- `y`
- `z`

Initialization:
- `vec(float x, float y, float z)` - creating a vector with ***x*** as its first coordinate, ***y*** as its second and ***z*** as its third

#### 4-D vector class (`vec4`)

Constants:
- `forward` - Vector pointing forward
- `back` - Vector pointing back
- `wforward` - Vector pointing forward in 4-th dimension
- `wback` - Vector pointing back in 4-th dimension

Global functions:
- `point(vecX vec)` - returns ***vec*** as a 3-D point (aka 4-D vector with 4-th coordinate being equal to 1)

Parameters:
- `x`
- `y`
- `z`
- `w`

Initialization:
- `vec(float x, float y, float z)` - creating a vector with ***x*** as its first coordinate, ***y*** as its second and ***z*** as its third
- `vec(float x, float y, float z, float w)` - creating a vector with ***x*** as its first coordinate, ***y*** as its second, ***z*** as its third and ***w*** as its fourth

### Matrix class (`mat4x4`)

Constants:
- `zero` - Zero matrix
- `one` - Matrix with ones in every cell
- `identity` - Identity matrix

Static functions:
- `mat4x4 translation(const vec3 &t)` - Returns a translation matrix
- `scale(const vec3 &t);` - Returns a scalar matrix
- `rotationX(float angle);` - Return rotation matrix around the X axis
- `rotationY(float angle);` - Return rotation matrix around the Y axis
- `rotationZ(float angle);` - Return rotation matrix around the Z axis
- `rotation(float x, float y, float z);` - Return rotation matrix
- `orthoLH(float width, float height, float near_plane, float far_plane);` - Return orthographics projection matrix

Initialization:
- `mat4x4()` - creating a ***zero*** matrix
- `mat4x4(float _11, ..., float _44)` - creating a matrix with ***_11, ..., _44*** in its cells
- `mat4x4(vec4 _1, ..., vec4 _4)` - creating a matrix with ***_1, ..., _4*** as its rows
- `mat4x4(float _1[4], ..., float _4[4])` - creating a matrix with ***_1, ..., _4*** as its rows
- `mat4x4(const mat4x4 &mat)` - creating a matrix based on another matrix
- `mat4x4(const float mat[4][4])` - creating a matrix based on a 2-D array

Operators:
- `+a` - returns copy of the matrix
- `-a` - returns the opposite matrix
- `a + b` - returns sum of 2 matrices
- `a - b` - returns difference of 2 matrices
- `a * b` - if either ***a*** or ***b*** is a `float` the result would be a matrix scaled by the factor, otherwise returns the product of 2 matrices
- `a / b` - if ***b*** is a `float` the result would be a matrix divided by the factor, otherwise returns the dividend of 2 matrices
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
- `hWnd`
- `bRunning`