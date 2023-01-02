#ifndef COMMON_DATAMGR_T_MANAGED_HPP
#define COMMON_DATAMGR_T_MANAGED_HPP

#include "common/datamgr/CBaseManaged.hpp"

template <class T>
class TManaged : public CBaseManaged {
    public:
    // Member variables
    T m_data;

    // Virtual member functions
    virtual void Set(const T& val);

    // Member functions
    TManaged() = default;
    TManaged(const T& val)
        : m_data(val) {};
};

template <class T>
void TManaged<T>::Set(const T& val) {
    if (this->m_data != val) {
        this->m_data = val;
        this->m_flags |= CBaseManaged::UPDATED;
    }
}

#endif
