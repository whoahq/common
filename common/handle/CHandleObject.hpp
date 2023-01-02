#ifndef COMMON_HANDLE_C_HANDLE_OBJECT_HPP
#define COMMON_HANDLE_C_HANDLE_OBJECT_HPP

#include <cstdint>

class CHandleObject {
    public:
    // Member variables
    int32_t m_refcount = 0;

    // Virtual member functions
    virtual ~CHandleObject() = default;
};

#endif
