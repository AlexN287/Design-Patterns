#include "StringItem.h"

gem::String& StringItem::FallBackToLegacyUnicode() {
    return m_string.fallbackToLegacyUnicode();
}
bool StringItem::Empty() {
    return m_string.empty();
}
std::string StringItem::ToStdString() {
    return m_string.toStdString();
}
void StringItem::Clear() {
    m_string.clear();
}
int StringItem::Find(const char16_t ch, int from) {
    return m_string.find(ch, from);
}
gem::String StringItem::Right(int len) {
    return m_string.right(len);
}
gem::String StringItem::Left(int len) {
    return m_string.left(len);
}
int StringItem::Size() {
    return m_string.size();
}
gem::String& StringItem::Append(const gem::String& str) {
    return m_string.append(str);
}

void StringItem::SetString(const gem::String& str)
{
    m_string = str;
}

gem::String StringItem::GetString()
{
    return m_string;
}

gem::String StringItem::FormatString(const char16_t* format, double args)
{
    return gem::String::formatString(format, args);
}

char StringItem::GetElementOnPosition(int pos)
{
    return m_string[pos];
}
