#ifndef COMMON_INSTANCE_T_SINGLETON_INSTANCE_ID_HPP
#define COMMON_INSTANCE_T_SINGLETON_INSTANCE_ID_HPP

#include "common/instance/TInstanceId.hpp"
#include "common/instance/TInstanceIdTable.hpp"

template <class T, size_t offset>
class TSingletonInstanceId : public TInstanceId<T> {
    public:
    // Static variables
    static TInstanceIdTable<T, offset> s_idTable;
};

#endif
