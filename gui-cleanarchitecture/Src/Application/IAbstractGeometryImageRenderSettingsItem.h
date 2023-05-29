#pragma once

#include "API/GEM_Images.h"

class IAbstractGeometryImageRenderSettingsItem {
public:
    virtual void SetSettings(const gem::Rgba& colorActiveInner = gem::Rgba(), const gem::Rgba& colorActiveOuter = gem::Rgba(), const gem::Rgba& colorInactiveInner = gem::Rgba(), const gem::Rgba& colorInactiveOuter = gem::Rgba()) = 0;
    virtual gem::AbstractGeometryImageRenderSettings GetSettings() = 0;
};
