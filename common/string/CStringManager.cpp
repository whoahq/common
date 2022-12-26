#include "common/string/CStringManager.hpp"
#include <climits>
#include <cstdlib>
#include <cstring>
#include <storm/Memory.hpp>
#include <storm/String.hpp>

CStringManager* CStringManager::s_stringManager;

CStringManager* CStringManager::Get() {
    // If the string manager isn't instantiated yet, do so now
    if (!CStringManager::s_stringManager) {
        void* m = SMemAlloc(sizeof(CStringManager), __FILE__, __LINE__, 0x0);
        CStringManager::s_stringManager = m ? new (m) CStringManager() : nullptr;
    }

    return CStringManager::s_stringManager;
}

CStringManager::CStringManager() {
    this->m_memory.AllocateBlock(0);
    memset(this->m_buckets, 0, sizeof(this->m_buckets));
}

char* CStringManager::Add(const char* str) {
    uint32_t hashval = SStrHashHT(str);
    uint32_t bucketIdx = hashval % 0x209;
    auto bucket = this->m_buckets[bucketIdx];

    if (bucket) {
        auto ele = bucket;

        while (ele) {
            if (!SStrCmp(str, &ele->str, INT_MAX)) {
                return &ele->str;
            }

            ele = ele->next;
        }
    }

    auto newEle = this->m_memory.New(str);

    // Insert new element at start
    newEle->next = this->m_buckets[bucketIdx];
    this->m_buckets[bucketIdx] = newEle;

    return &newEle->str;
}
