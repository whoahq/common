#ifndef COMMON_INSTANCE_T_INSTANCE_ID_HPP
#define COMMON_INSTANCE_T_INSTANCE_ID_HPP

#include <cstdint>
#include <storm/List.hpp>

template <class T>
class TInstanceId : public TSLinkedNode<T> {
    public:
    // Member variables
    uint32_t m_id;
};

#endif
