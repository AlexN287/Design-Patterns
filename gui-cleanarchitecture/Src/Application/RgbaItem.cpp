#include "RgbaItem.h"

void RgbaItem::SetColor(int a, int b, int c, int d) {
    gem::Rgba color(a, b, c, d);
    m_color = color;
}
RgbaItem::RgbaItem(int a, int b, int c, int d) {
    gem::Rgba color(a, b, c, d);
    m_color = color;
}
gem::Rgba RgbaItem::GetColor() {
    return this->m_color;
}
