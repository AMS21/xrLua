#include <catch2/catch_test_macros.hpp>

#include <xrLua/utils/is_space.hpp>

TEST_CASE("utils::is_space")
{
    REQUIRE(xrlua::is_space(' '));
    REQUIRE(xrlua::is_space('\f'));
    REQUIRE(xrlua::is_space('\n'));
    REQUIRE(xrlua::is_space('\r'));
    REQUIRE(xrlua::is_space('\t'));
    REQUIRE(xrlua::is_space('\v'));

    REQUIRE_FALSE(xrlua::is_space('\0'));
    REQUIRE_FALSE(xrlua::is_space('a'));
    REQUIRE_FALSE(xrlua::is_space('z'));
    REQUIRE_FALSE(xrlua::is_space('A'));
    REQUIRE_FALSE(xrlua::is_space('Z'));
    REQUIRE_FALSE(xrlua::is_space('0'));
    REQUIRE_FALSE(xrlua::is_space('9'));
    REQUIRE_FALSE(xrlua::is_space('!'));
    REQUIRE_FALSE(xrlua::is_space('['));
    REQUIRE_FALSE(xrlua::is_space(']'));
    REQUIRE_FALSE(xrlua::is_space('{'));
    REQUIRE_FALSE(xrlua::is_space('}'));
    REQUIRE_FALSE(xrlua::is_space('('));
    REQUIRE_FALSE(xrlua::is_space(')'));
    REQUIRE_FALSE(xrlua::is_space(';'));
    REQUIRE_FALSE(xrlua::is_space(':'));
    REQUIRE_FALSE(xrlua::is_space(','));
    REQUIRE_FALSE(xrlua::is_space('.'));
    REQUIRE_FALSE(xrlua::is_space('/'));
    REQUIRE_FALSE(xrlua::is_space('\\'));
    REQUIRE_FALSE(xrlua::is_space('<'));
    REQUIRE_FALSE(xrlua::is_space('>'));
    REQUIRE_FALSE(xrlua::is_space('|'));
    REQUIRE_FALSE(xrlua::is_space('?'));
    REQUIRE_FALSE(xrlua::is_space('\''));
    REQUIRE_FALSE(xrlua::is_space('"'));
    REQUIRE_FALSE(xrlua::is_space('\b'));
}
