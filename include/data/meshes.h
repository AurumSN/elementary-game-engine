#pragma once

#include "data/resources.h"

class Mesh : public Resource {
public:
    Mesh(const wchar_t *full_path);
    ~Mesh();
};