#ifndef COMMON_DATASTORE_C_DATA_STORE_HPP
#define COMMON_DATASTORE_C_DATA_STORE_HPP

#include <cstdint>

class CDataStore {
    public:
    // Member variables
    uint8_t* m_data = nullptr;
    uint32_t m_base = 0;
    uint32_t m_alloc = 0;
    uint32_t m_size = 0;
    uint32_t m_read = -1;

    // Virtual member functions
    virtual void InternalInitialize(uint8_t*& data, uint32_t& base, uint32_t& alloc) {};
    virtual void InternalDestroy(uint8_t*& data, uint32_t& base, uint32_t& alloc);
    virtual int32_t InternalFetchRead(uint32_t pos, uint32_t bytes, uint8_t*& data, uint32_t& base, uint32_t& alloc);
    virtual int32_t InternalFetchWrite(uint32_t pos, uint32_t bytes, uint8_t*& data, uint32_t& base, uint32_t& alloc, const char* fileName, int32_t lineNumber);
    // TODO
    // virtual ~CDataStore();
    virtual int32_t IsRead() const;
    virtual void Reset();
    virtual void Finalize();
    virtual void GetBufferParams(const void** data, uint32_t* size, uint32_t* alloc) const;
    virtual void DetachBuffer(void** data, uint32_t* size, uint32_t* alloc);
    virtual uint32_t GetHeaderSpace();

    // Member functions
    int32_t FetchRead(uint32_t pos, uint32_t bytes);
    int32_t FetchWrite(uint32_t pos, uint32_t bytes, const char* fileName, int32_t lineNumber);
    CDataStore& Get(uint8_t& val);
    CDataStore& Get(uint32_t& val);
    CDataStore& Get(uint64_t& val);
    CDataStore& GetDataInSitu(void*& val, uint32_t bytes);
    int32_t IsFinal();
    CDataStore& Put(uint8_t val);
    CDataStore& Put(uint16_t val);
    CDataStore& Put(uint32_t val);
    CDataStore& Put(uint64_t val);
    CDataStore& PutArray(const uint8_t* val, uint32_t count);
    CDataStore& PutData(const void* val, uint32_t bytes);
    CDataStore& Set(uint32_t pos, uint16_t val);
    bool Sub8CBBF0(uint32_t a2);
};

#endif
