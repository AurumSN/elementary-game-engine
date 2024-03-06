#pragma once

#include "data/resources.h"

class Texture : public Resource {
public:
    Texture(const wchar_t *full_path);
    ~Texture();
};