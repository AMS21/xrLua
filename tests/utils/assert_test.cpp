#include <catch2/catch_test_macros.hpp>

#include <xrLua/utils/assert.hpp>

TEST_CASE("utils::assert")
{
    XRLUA_ASSERT(true, "Should not fail!");
    XRLUA_PEDANTIC_ASSERT(true, "Should not fail");
}
