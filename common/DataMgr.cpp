#include "common/DataMgr.hpp"
#include <storm/Error.hpp>

void DataMgrGetCoord(HDATAMGR mgr, uint32_t fieldId, C3Vector* coord) {
    auto mgrPtr = reinterpret_cast<CDataMgr*>(mgr);

    STORM_ASSERT(mgrPtr);
    STORM_ASSERT(fieldId < mgrPtr->m_managedArray.Count());
    STORM_ASSERT(mgrPtr->m_managedArray[fieldId]);
    STORM_ASSERT(CBaseManaged::COORD == mgrPtr->m_managedArray[fieldId]->m_dataTypeId);

    auto field = static_cast<TManaged<C3Vector>*>(mgrPtr->m_managedArray[fieldId]);

    if (field->m_flags & CBaseManaged::REQUIRESUPDATE) {
        if (field->m_flags & CBaseManaged::READONLY) {
            // TODO
        } else {
            // TODO
        }
    }

    *coord = field->m_data;
}

void DataMgrSetCoord(HDATAMGR mgr, uint32_t fieldId, const C3Vector& coord, uint32_t coordFlags) {
    auto dataMgr = reinterpret_cast<CDataMgr*>(mgr);
    auto typeId = CBaseManaged::COORD;

    C3Vector cur = { 0.0f, 0.0f, 0.0f };
    DataMgrGetCoord(mgr, fieldId, &cur);

    C3Vector setTo = {
        (coordFlags & 0x1) ? cur.x : coord.x,
        (coordFlags & 0x2) ? cur.y : coord.y,
        (coordFlags & 0x4) ? cur.z : coord.z
    };

    STORM_ASSERT(dataMgr);
    STORM_ASSERT(fieldId < dataMgr->m_managedArray.Count());
    STORM_ASSERT(dataMgr->m_managedArray[fieldId]);
    STORM_ASSERT(typeId == dataMgr->m_managedArray[fieldId]->m_dataTypeId);
    STORM_ASSERT(!(dataMgr->m_managedArray[fieldId]->m_flags & CBaseManaged::READONLY));

    auto field = static_cast<TManaged<C3Vector>*>(dataMgr->m_managedArray[fieldId]);

    field->m_updateFcn = nullptr;
    field->m_updateData = nullptr;
    field->m_updatePriority = 0.0f;
    field->Set(setTo);
}

void DataMgrSetFloat(HDATAMGR mgr, uint32_t fieldId, float val) {
    auto dataMgr = reinterpret_cast<CDataMgr*>(mgr);
    auto typeId = CBaseManaged::FLOAT;

    STORM_ASSERT(dataMgr);
    STORM_ASSERT(fieldId < dataMgr->m_managedArray.Count());
    STORM_ASSERT(dataMgr->m_managedArray[fieldId]);
    STORM_ASSERT(typeId == dataMgr->m_managedArray[fieldId]->m_dataTypeId);
    STORM_ASSERT(!(dataMgr->m_managedArray[fieldId]->m_flags & CBaseManaged::READONLY));

    auto field = static_cast<TManaged<float>*>(dataMgr->m_managedArray[fieldId]);

    field->m_updateFcn = nullptr;
    field->m_updateData = nullptr;
    field->m_updatePriority = 0.0f;
    field->Set(val);
}
