#ifndef COMMON_DATAMGR_C_BASE_MANAGED_HPP
#define COMMON_DATAMGR_C_BASE_MANAGED_HPP

#include <cstdint>
#include <storm/List.hpp>

class CBaseManaged {
    public:
    // Types
    enum ManagedTypeIds {
        // TODO
        COORD = 3,
        FLOAT = 6,
        DATATYPEIDS = 7,
    };

    enum ManagedFlags {
        ALWAYSUPDATE = 0x1,
        READONLY = 0x2,
        REQUIRESUPDATE = 0x4,
        UPDATED = 0x8,
    };

    // Member variables
    TSLink<CBaseManaged> m_link;
    uint8_t m_dataTypeId = 0;
    uint8_t m_flags = 0;
    void (*m_updateFcn)(float, void*, void*) = nullptr;
    void* m_updateData = nullptr;
    float m_updatePriority = 0.0f;
};

#endif
