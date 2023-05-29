#pragma once
#include "API/GEM_Types.h"

class IRgbaItem {
public:
    virtual void SetColor(int, int, int, int) = 0;
    virtual gem::Rgba GetColor() = 0;
};
