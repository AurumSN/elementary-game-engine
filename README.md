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
