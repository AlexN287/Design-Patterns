#pragma once

#include "IAbstractGeometryImageRenderSettingsItem.h"

class AbstractGeometryImageRenderSettingsItem : IAbstractGeometryImageRenderSettingsItem {
private:
    gem::AbstractGeometryImageRenderSettings m_settings;
public:
    AbstractGeometryImageRenderSettingsItem(const gem::Rgba& colorActiveInner = gem::Rgba(), const gem::Rgba& colorActiveOuter = gem::Rgba(), const gem::Rgba& colorInactiveInner = gem::Rgba(), const gem::Rgba& colorInactiveOuter = gem::Rgba());
    virtual void SetSettings(const gem::Rgba& colorActiveInner = gem::Rgba(), const gem::Rgba& colorActiveOuter = gem::Rgba(), const gem::Rgba& colorInactiveInner = gem::Rgba(), const gem::Rgba& colorInactiveOuter = gem::Rgba()) override;
    virtual gem::AbstractGeometryImageRenderSettings GetSettings() override;
};
