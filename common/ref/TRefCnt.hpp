#ifndef COMMON_T_REF_CNT_HPP
#define COMMON_T_REF_CNT_HPP

#include <cstdint>

class TRefCnt {
    public:
    // Member variables
    uint32_t m_refcnt;
};

template <class T>
class TRefCntPtr {
    public:
    // Member variables
    T* m_ptr;
};

#endif
