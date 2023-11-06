#include "gtest/gtest.h"
#include <gtest/gtest.h>

#include <xrLua/prelude.hpp>

TEST(prelude, asserts)
{
    XRLUA_ASSERT(true, "Should not fail!");
    XRLUA_PEDANTIC_ASSERT(true, "Should not fail");

    EXPECT_DEATH(XRLUA_ASSERT(false, "Should fail!"), "Should fail!");
    EXPECT_DEATH(XRLUA_ASSERT(1 == 0, ""), "1 == 0");
    EXPECT_DEATH(XRLUA_PEDANTIC_ASSERT(false, "Pedantic fail"), "Pedantic fail");
    EXPECT_DEATH(XRLUA_ASSERT_NOT_REACHED(), "This could should not be reachable");
    EXPECT_DEATH(
        switch (1) {
            case 0:
                XRLUA_NO_DEFAULT();
        },
        "Default case should not be reachable!");

    EXPECT_DEATH(xrlua::detail::assertion_failure_handler("~message~", "~condition~", "~file~", 1337, "~function~"),
        "XRLUA ASSERTION VIOLATION");
    EXPECT_DEATH(xrlua::detail::assertion_failure_handler("~message~", "~condition~", "~file~", 1337, "~function~"),
        "~message~");
    EXPECT_DEATH(xrlua::detail::assertion_failure_handler("~message~", "~condition~", "~file~", 1337, "~function~"),
        "~condition~");
    EXPECT_DEATH(
        xrlua::detail::assertion_failure_handler("~message~", "~condition~", "~file~", 1337, "~function~"), "~file~");
    EXPECT_DEATH(
        xrlua::detail::assertion_failure_handler("~message~", "~condition~", "~file~", 1337, "~function~"), "1337");
    EXPECT_DEATH(xrlua::detail::assertion_failure_handler("~message~", "~condition~", "~file~", 1337, "~function~"),
        "~function~");
}
