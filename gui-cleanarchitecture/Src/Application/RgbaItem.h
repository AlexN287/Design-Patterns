#pragma once
#include "IRgbaItem.h"
#include "API/GEM_Types.h"

class RgbaItem : IRgbaItem {
private:
    gem::Rgba m_color;
public:
    virtual void SetColor(int, int, int, int) override;
    virtual gem::Rgba GetColor() override;
    RgbaItem(int a, int b, int c, int d);
};
