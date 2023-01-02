#ifndef COMMON_DATA_MGR_HPP
#define COMMON_DATA_MGR_HPP

#include "common/Handle.hpp"
#include "common/datamgr/CDataMgr.hpp"

typedef HOBJECT HDATAMGR;

class C3Vector;

void DataMgrGetCoord(HDATAMGR mgr, uint32_t fieldId, C3Vector* coord);

void DataMgrSetCoord(HDATAMGR mgr, uint32_t fieldId, const C3Vector& coord, uint32_t coordFlags);

void DataMgrSetFloat(HDATAMGR mgr, uint32_t fieldId, float val);

#endif
