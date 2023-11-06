#include <gtest/gtest.h>

#include <xrLua/utils/is_space.hpp>

TEST(utils, is_space)
{
    EXPECT_TRUE(xrlua::is_space(' '));
    EXPECT_TRUE(xrlua::is_space('\f'));
    EXPECT_TRUE(xrlua::is_space('\n'));
    EXPECT_TRUE(xrlua::is_space('\r'));
    EXPECT_TRUE(xrlua::is_space('\t'));
    EXPECT_TRUE(xrlua::is_space('\v'));

    EXPECT_FALSE(xrlua::is_space('\0'));
    EXPECT_FALSE(xrlua::is_space('a'));
    EXPECT_FALSE(xrlua::is_space('z'));
    EXPECT_FALSE(xrlua::is_space('A'));
    EXPECT_FALSE(xrlua::is_space('Z'));
    EXPECT_FALSE(xrlua::is_space('0'));
    EXPECT_FALSE(xrlua::is_space('9'));
    EXPECT_FALSE(xrlua::is_space('!'));
    EXPECT_FALSE(xrlua::is_space('['));
    EXPECT_FALSE(xrlua::is_space(']'));
    EXPECT_FALSE(xrlua::is_space('{'));
    EXPECT_FALSE(xrlua::is_space('}'));
    EXPECT_FALSE(xrlua::is_space('('));
    EXPECT_FALSE(xrlua::is_space(')'));
    EXPECT_FALSE(xrlua::is_space(';'));
    EXPECT_FALSE(xrlua::is_space(':'));
    EXPECT_FALSE(xrlua::is_space(','));
    EXPECT_FALSE(xrlua::is_space('.'));
    EXPECT_FALSE(xrlua::is_space('/'));
    EXPECT_FALSE(xrlua::is_space('\\'));
    EXPECT_FALSE(xrlua::is_space('<'));
    EXPECT_FALSE(xrlua::is_space('>'));
    EXPECT_FALSE(xrlua::is_space('|'));
    EXPECT_FALSE(xrlua::is_space('?'));
    EXPECT_FALSE(xrlua::is_space('\''));
    EXPECT_FALSE(xrlua::is_space('"'));
    EXPECT_FALSE(xrlua::is_space('\b'));
}
