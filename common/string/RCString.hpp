#ifndef COMMON_STRING_RC_STRING_HPP
#define COMMON_STRING_RC_STRING_HPP

#include "common/Ref.hpp"
#include <cstdlib>

class RCString : public TRefCnt {
    public:
    // Member variables
    char* m_str;

    // Member functions
    RCString();
    void Copy(const char* source);
    void Copy(const RCString& source);
    void Get(char* buf, size_t bufSize) const;
    const char* GetString() const;
    operator const char*() const;
};

#endif
