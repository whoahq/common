#ifndef COMMON_DATASTORE_C_DATA_STORE_CACHE_HPP
#define COMMON_DATASTORE_C_DATA_STORE_CACHE_HPP

#include "common/datastore/CDataStore.hpp"
#include <cstdlib>

template <size_t size>
class CDataStoreCache : public CDataStore {
    public:
    // Member variables
    uint8_t m_cache[size];

    // Virtual member functions
    virtual void InternalInitialize(uint8_t*& data, uint32_t& base, uint32_t& alloc);

    // Member functions
    CDataStoreCache() {
        this->InternalInitialize(this->m_data, this->m_base, this->m_alloc);
    }
};

template <size_t size>
void CDataStoreCache<size>::InternalInitialize(uint8_t*& data, uint32_t& base, uint32_t& alloc) {
    data = this->m_cache;
    alloc = size;
}

#endif
