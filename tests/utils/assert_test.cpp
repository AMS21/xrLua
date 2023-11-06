#include "gtest/gtest.h"
#include <gtest/gtest.h>

#include <xrLua/utils/assert.hpp>

TEST(utils, assert)
{
    XRLUA_ASSERT(true, "Should not fail!");
    XRLUA_PEDANTIC_ASSERT(true, "Should not fail");

    EXPECT_DEATH(XRLUA_ASSERT(false, "Should fail!"), "Should fail!");
    EXPECT_DEATH(XRLUA_PEDANTIC_ASSERT(false, "Pedantic fail"), "Pedantic fail");
    EXPECT_DEATH(XRLUA_ASSERT_NOT_REACHED(), "This could should not be reachable");
}
