#include "common/datastore/CDataStore.hpp"
#include <algorithm>
#include <cstring>
#include <storm/Error.hpp>
#include <storm/Memory.hpp>

void CDataStore::DetachBuffer(void** data, uint32_t* size, uint32_t* alloc) {
    // TODO
}

int32_t CDataStore::FetchRead(uint32_t pos, uint32_t bytes) {
    if (pos + bytes <= this->m_size) {
        if (pos >= this->m_base && pos + bytes <= this->m_base + this->m_alloc) {
            return 1;
        }

        if (this->InternalFetchRead(pos, bytes, this->m_data, this->m_base, this->m_alloc)) {
            return 1;
        }
    }

    this->m_read = this->m_size + 1;

    return 0;
}

int32_t CDataStore::FetchWrite(uint32_t pos, uint32_t bytes, const char* fileName, int32_t lineNumber) {
    if (pos >= this->m_base && pos + bytes <= this->m_base + this->m_alloc) {
        return 1;
    }

    if (this->InternalFetchWrite(pos, bytes, this->m_data, this->m_base, this->m_alloc, fileName, lineNumber)) {
        return 1;
    }

    return 0;
}

void CDataStore::Finalize() {
    STORM_ASSERT(!this->IsFinal());

    this->m_read = 0;
}

CDataStore& CDataStore::Get(uint8_t& val) {
    STORM_ASSERT(this->IsFinal());

    auto bytes = sizeof(val);

    if (this->FetchRead(this->m_read, bytes)) {
        auto ofs = this->m_read - this->m_base;
        auto ptr = &this->m_data[ofs];
        val = *reinterpret_cast<uint8_t*>(ptr);

        this->m_read += bytes;
    }

    return *this;
}

CDataStore& CDataStore::Get(uint32_t& val) {
    STORM_ASSERT(this->IsFinal());

    auto bytes = sizeof(val);

    if (this->FetchRead(this->m_read, bytes)) {
        auto ofs = this->m_read - this->m_base;
        auto ptr = &this->m_data[ofs];
        val = *reinterpret_cast<uint32_t*>(ptr);

        this->m_read += bytes;
    }

    return *this;
}

CDataStore& CDataStore::Get(uint64_t& val) {
    STORM_ASSERT(this->IsFinal());

    auto bytes = sizeof(val);

    if (this->FetchRead(this->m_read, bytes)) {
        auto ofs = this->m_read - this->m_base;
        auto ptr = &this->m_data[ofs];
        val = *reinterpret_cast<uint64_t*>(ptr);

        this->m_read += bytes;
    }

    return *this;
}

void CDataStore::GetBufferParams(const void** data, uint32_t* size, uint32_t* alloc) const {
    if (data) {
        *data = this->m_data;
    }

    if (size) {
        *size = this->m_size;
    }

    if (alloc) {
        *alloc = this->m_alloc;
    }
}

CDataStore& CDataStore::GetDataInSitu(void*& val, uint32_t bytes) {
    STORM_ASSERT(this->IsFinal());

    if (this->FetchRead(this->m_read, bytes)) {
        auto ofs = this->m_read - this->m_base;
        auto ptr = &this->m_data[ofs];
        val = ptr;

        this->m_read += bytes;
    }

    return *this;
}

uint32_t CDataStore::GetHeaderSpace() {
    return 0;
}

void CDataStore::InternalDestroy(uint8_t*& data, uint32_t& base, uint32_t& alloc) {
    if (alloc && data) {
        SMemFree(data, __FILE__, __LINE__, 0);
    }

    data = nullptr;
    base = 0;
    alloc = 0;
}

int32_t CDataStore::InternalFetchRead(uint32_t pos, uint32_t bytes, uint8_t*& data, uint32_t& base, uint32_t& alloc) {
    return 0;
}

int32_t CDataStore::InternalFetchWrite(uint32_t pos, uint32_t bytes, uint8_t*& data, uint32_t& base, uint32_t& alloc, const char* fileName, int32_t lineNumber) {
    alloc = (pos + bytes + 0xFF) & 0xFFFFFF00;

    data = static_cast<uint8_t*>(SMemReAlloc(
        data,
        alloc,
        fileName == nullptr ? __FILE__ : fileName,
        fileName == nullptr ? __LINE__ : lineNumber,
        0x0));

    return 1;
}

int32_t CDataStore::IsFinal() {
    return this->m_read != -1;
}

int32_t CDataStore::IsRead() const {
    return this->m_size == this->m_read;
}

CDataStore& CDataStore::Put(uint8_t val) {
    STORM_ASSERT(!this->IsFinal());

    this->FetchWrite(this->m_size, sizeof(val), nullptr, 0);

    auto ofs = this->m_size - this->m_base;
    auto ptr = &this->m_data[ofs];
    *reinterpret_cast<uint8_t*>(ptr) = val;

    this->m_size += sizeof(val);

    return *this;
}

CDataStore& CDataStore::Put(uint16_t val) {
    STORM_ASSERT(!this->IsFinal());

    this->FetchWrite(this->m_size, sizeof(val), nullptr, 0);

    auto ofs = this->m_size - this->m_base;
    auto ptr = &this->m_data[ofs];
    *reinterpret_cast<uint16_t*>(ptr) = val;

    this->m_size += sizeof(val);

    return *this;
}

CDataStore& CDataStore::Put(uint32_t val) {
    STORM_ASSERT(!this->IsFinal());

    this->FetchWrite(this->m_size, sizeof(val), nullptr, 0);

    auto ofs = this->m_size - this->m_base;
    auto ptr = &this->m_data[ofs];
    *reinterpret_cast<uint32_t*>(ptr) = val;

    this->m_size += sizeof(val);

    return *this;
}

CDataStore& CDataStore::Put(uint64_t val) {
    STORM_ASSERT(!this->IsFinal());

    this->FetchWrite(this->m_size, sizeof(val), nullptr, 0);

    auto ofs = this->m_size - this->m_base;
    auto ptr = &this->m_data[ofs];
    *reinterpret_cast<uint64_t*>(ptr) = val;

    this->m_size += sizeof(val);

    return *this;
}

CDataStore& CDataStore::PutArray(const uint8_t* val, uint32_t count) {
    STORM_ASSERT(!this->IsFinal());
    STORM_ASSERT(val || !count);

    if (val) {
        auto src = val;
        auto bytes = count;

        this->FetchWrite(this->m_size, bytes, nullptr, 0);

        while (count) {
            bytes = std::max(1u, std::min(bytes, this->m_alloc));

            this->FetchWrite(this->m_size, bytes, nullptr, 0);

            auto ofs = this->m_size - this->m_base;
            auto ptr = &this->m_data[ofs];

            if (ptr != src) {
                memcpy(ptr, src, bytes);
            }

            src += bytes;
            this->m_size += bytes;
            count -= bytes;
        }
    }

    return *this;
}

CDataStore& CDataStore::PutData(const void* val, uint32_t bytes) {
    return this->PutArray(static_cast<const uint8_t*>(val), bytes);
}

void CDataStore::Reset() {
    if (this->m_alloc == -1) {
        this->m_data = nullptr;
        this->m_alloc = 0;
    }

    this->m_size = 0;
    this->m_read = -1;
}

CDataStore& CDataStore::Set(uint32_t pos, uint16_t val) {
    STORM_ASSERT(!this->IsFinal());
    STORM_ASSERT(pos + sizeof(val) <= this->m_size);

    this->FetchWrite(pos, sizeof(val), nullptr, 0);

    auto ofs = pos - this->m_base;
    auto ptr = &this->m_data[ofs];
    *reinterpret_cast<uint16_t*>(ptr) = val;

    return *this;
}

bool CDataStore::Sub8CBBF0(uint32_t a2) {
    return this->m_read <= this->m_size && this->m_size - this->m_read >= a2;
}
