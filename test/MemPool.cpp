#include "common/MemPool.hpp"
#include "test/Test.hpp"

TEST_CASE("MemPool::MemPool", "[mempool]") {
    SECTION("constructs new mem pool") {
        MemPool pool;
        SUCCEED();
    }
}

TEST_CASE("MemPool::Init", "[mempool]") {
    SECTION("inits mem pool") {
        MemPool pool;
        pool.Init(16, 16 << 10);
        SUCCEED();
    }
}

TEST_CASE("MemPool::MemAlloc", "[mempool]") {
    SECTION("allocates pointer to new free memory") {
        MemPool pool;
        pool.Init(16, 16 << 10);
        auto ptr = pool.MemAlloc();
        REQUIRE(ptr);
    }
}

TEST_CASE("MemPool::MemFree", "[mempool]") {
    SECTION("frees allocated pointer") {
        MemPool pool;
        pool.Init(16, 16 << 10);
        auto ptr = pool.MemAlloc();
        pool.MemFree(ptr);
        SUCCEED();
    }
}
