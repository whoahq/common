#include "common/string/RCString.hpp"
#include "common/string/CStringManager.hpp"
#include <storm/String.hpp>
#include "RCString.hpp"

RCString::RCString()
    : TRefCnt() {
    this->Copy(nullptr);
}

void RCString::Copy(const char* source) {
    if (source) {
        this->m_str = CStringManager::Get()->Add(source);
    } else {
        this->m_str = nullptr;
    }
}

void RCString::Copy(const RCString& source) {
    this->Copy(source.GetString());
}

void RCString::Get(char* buf, size_t bufSize) const {
    const char* str = this->GetString();

    if (str) {
        SStrCopy(buf, str, bufSize);
    } else {
        *buf = 0;
    }
}

const char* RCString::GetString() const {
    if (this->m_str) {
        return this->m_str;
    } else {
        return nullptr;
    }
}
<<<<<<< 9a5e71de2207be9368428a3bff147b9bcd51d94a
=======

void RCString::operator=(const char* rval) {
    this->Copy(rval);
}

RCString::operator const char*() const {
    return this->GetString();
}
>>>>>>> feat(string): add RCString::operator=(const char*) method
