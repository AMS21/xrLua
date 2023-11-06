#pragma once

namespace xrlua
{

[[nodiscard]]
constexpr bool is_space(char character)
{
    switch (character)
    {
    case ' ':
    case '\f':
    case '\n':
    case '\r':
    case '\t':
    case '\v':
        return true;
    default:
        return false;
    }
}

} // namespace xrlua
