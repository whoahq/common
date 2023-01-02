#include "common/datamgr/CDataMgr.hpp"

void CDataMgr::AddManaged(CBaseManaged* managed, uint32_t fieldId, uint32_t flags, uint32_t dataTypeId) {
    managed->m_flags = flags;
    managed->m_dataTypeId = dataTypeId;

    this->m_managedArray[fieldId] = managed;

    if (flags & CBaseManaged::ALWAYSUPDATE) {
        this->LinkManaged(managed);
    }
}

void CDataMgr::AddManaged(TManaged<C3Vector>* managed, uint32_t fieldId, uint32_t flags) {
    this->AddManaged(managed, fieldId, flags, CBaseManaged::COORD);
}

void CDataMgr::AddManaged(TManaged<float>* managed, uint32_t fieldId, uint32_t flags) {
    this->AddManaged(managed, fieldId, flags, CBaseManaged::FLOAT);
}

void CDataMgr::LinkManaged(CBaseManaged* managed) {
    // TODO
}
