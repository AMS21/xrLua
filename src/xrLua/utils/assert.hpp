#pragma once

namespace xrlua::detail
{

[[noreturn]]
void assertion_failure_handler(
    const char* message, const char* condition, const char* file, int line_number, const char* function);

} // namespace xrlua::detail

#define XRLUA_ASSERT(condition, message)                                                                               \
    if (!(condition))                                                                                                  \
    {                                                                                                                  \
        ::xrlua::detail::assertion_failure_handler(message, #condition, __FILE__, __LINE__, __PRETTY_FUNCTION__);      \
    }                                                                                                                  \
    (void)0

#define XRLUA_ASSERT_NOT_REACHED() XRLUA_ASSERT(false, "This could should not be reachable")

#define XRLUA_NO_DEFAULT()                                                                                             \
    break;                                                                                                             \
    default:                                                                                                           \
        XRLUA_ASSERT(false, "Default case should not be reachable")

#define XRLUA_PEDANTIC_ASSERT(condition, msg) XRLUA_ASSERT(condition, msg)
