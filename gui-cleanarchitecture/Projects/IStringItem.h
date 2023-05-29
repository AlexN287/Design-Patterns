#pragma once
#include <string>

#include <API/GEM_Position.h>

class IStringItem {
public:
    virtual gem::String& FallBackToLegacyUnicode() = 0;
    virtual bool Empty() = 0;
    virtual std::string ToStdString() = 0;
    virtual void Clear() = 0;
    virtual int Find(const char16_t ch, int from = 0) = 0;
    virtual gem::String Right(int len) = 0;
    virtual gem::String Left(int len) = 0;
    virtual int Size() = 0;
    virtual gem::String& Append(const gem::String& str) = 0;
    virtual char GetElementOnPosition(int pos) = 0;



};
