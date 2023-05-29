#include "AbstractGeometryImageRenderSettingsItem.h"

AbstractGeometryImageRenderSettingsItem::AbstractGeometryImageRenderSettingsItem(const gem::Rgba& colorActiveInner, const gem::Rgba& colorActiveOuter, const gem::Rgba& colorInactiveInner, const gem::Rgba& colorInactiveOuter) {
    gem::AbstractGeometryImageRenderSettings settings(colorActiveInner, colorActiveOuter, colorInactiveInner, colorInactiveOuter);
    m_settings = settings;
}
void AbstractGeometryImageRenderSettingsItem::SetSettings(const gem::Rgba& colorActiveInner, const gem::Rgba& colorActiveOuter, const gem::Rgba& colorInactiveInner, const gem::Rgba& colorInactiveOuter) {
    gem::AbstractGeometryImageRenderSettings settings(colorActiveInner, colorActiveOuter, colorInactiveInner, colorInactiveOuter);
    m_settings = settings;
}
gem::AbstractGeometryImageRenderSettings AbstractGeometryImageRenderSettingsItem::GetSettings() {
    return m_settings;
}
