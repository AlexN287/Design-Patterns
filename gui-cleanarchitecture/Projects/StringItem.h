#pragma once
#include "IStringItem.h"

class StringItem : IStringItem {
private:
    gem::String m_string;
public:
    StringItem(gem::String string) : m_string{ string } {};
    StringItem() = default;
    virtual gem::String& FallBackToLegacyUnicode() override;
    virtual bool Empty() override;
    virtual std::string ToStdString() override;
    virtual void Clear() override;
    virtual int Find(const char16_t ch, int from = 0) override;
    virtual gem::String Right(int len) override;
    virtual gem::String Left(int len) override;
    virtual int Size() override;
    virtual gem::String& Append(const gem::String& str) override;

    void SetString(const gem::String& str);
    gem::String GetString();

    gem::String FormatString(const char16_t* format, double args);

    virtual char GetElementOnPosition(int pos) override;
};
