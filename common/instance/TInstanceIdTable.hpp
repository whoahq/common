#ifndef COMMON_INSTANCE_T_INSTANCE_ID_TABLE_HPP
#define COMMON_INSTANCE_T_INSTANCE_ID_TABLE_HPP

#include <cstdint>
#include <storm/List.hpp>
#include <storm/Thread.hpp>

#define INSTANCE_TABLE_SLOT_COUNT 8

template <class T, size_t offset>
class TInstanceIdTable {
    public:
    // Types
    class Iterator {
        public:
        TInstanceIdTable<T, offset>* m_table;
        int32_t m_slot;
        T* m_next;
    };

    // Member variables
    SCritSect m_idCritsect;
    uint32_t m_id;
    int32_t m_idWrapped;
    CSRWLock m_idLock[INSTANCE_TABLE_SLOT_COUNT];
    TSList<T, TSGetLink<T>> m_idList[INSTANCE_TABLE_SLOT_COUNT];

    // Member functions
    void Insert(T* instance);
    T* Ptr(uint32_t id, int32_t lockMode, int32_t* findMask);
    void Unlock(uint32_t slot, int32_t lockMode);

    private:
    uint32_t NextId();
};

template <class T, size_t offset>
void TInstanceIdTable<T, offset>::Insert(T* instance) {
    if (instance->m_id) {
        return;
    }

    this->m_idCritsect.Enter();

    auto id = this->NextId();

    instance->m_id = id;

    uint32_t slot = id & (INSTANCE_TABLE_SLOT_COUNT - 1);

    auto idLock = &this->m_idLock[slot];

    idLock->Enter(1);

    this->m_idList[slot].LinkNode(instance, 2, nullptr);

    idLock->Leave(1);

    this->m_idCritsect.Leave();
}

template <class T, size_t offset>
uint32_t TInstanceIdTable<T, offset>::NextId() {
    uint32_t id;
    int32_t exists;

    do {
        while (1) {
            id = this->m_id + 1;

            this->m_id++;

            if (this->m_id != 0) {
                break;
            }

            this->m_idWrapped = 1;
        }

        if (this->m_idWrapped == 0) {
            break;
        }

        uint32_t slot = id & (INSTANCE_TABLE_SLOT_COUNT - 1);

        auto idLock = &this->m_idLock[slot];

        idLock->Enter(0);

        exists = 0;

        auto idList = &this->m_idList[slot];

        auto node = idList->Head();

        while (node) {
            if (node->m_id == id) {
                exists = 1;
                break;
            }

            node = idList->Link(node)->Next();
        }

        idLock->Leave(0);
    } while (exists);

    return id;
}

template <class T, size_t offset>
T* TInstanceIdTable<T, offset>::Ptr(uint32_t id, int32_t lockMode, int32_t* findMask) {
    if (id) {
        uint32_t slot = id & (INSTANCE_TABLE_SLOT_COUNT - 1);

        auto idLock = &this->m_idLock[slot];

        idLock->Enter(lockMode);

        auto idList = &this->m_idList[slot];

        auto node = idList->Head();

        while (node) {
            if (node->m_id == id) {
                *findMask = slot + (lockMode != 0 ? INSTANCE_TABLE_SLOT_COUNT : 0);
                return node;
            }

            node = idList->Link(node)->Next();
        }

        idLock->Leave(lockMode);
    }

    *findMask = -1;
    return nullptr;
}

template <class T, size_t offset>
void TInstanceIdTable<T, offset>::Unlock(uint32_t slot, int32_t lockMode) {
    this->m_idLock[slot].Leave(lockMode);
}

#endif
