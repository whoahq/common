#ifndef COMMON_REF_T_REF_CNT_PTR_HPP
#define COMMON_REF_T_REF_CNT_PTR_HPP

#include <cstdint>

template <class T>
class TRefCntPtr {
    public:
    // Member variables
    T* m_ptr;
};

#endif
