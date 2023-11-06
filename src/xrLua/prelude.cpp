#include "xrLua/prelude.hpp"

#include <cstdio>
#include <cstdlib>

namespace xrlua::detail
{

[[noreturn]]
XRLUA_ATTR_COLD void assertion_failure_handler(
    const char* message, const char* condition, const char* file, int line_number, const char* function)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    (void)std::fprintf(stderr,
        "XRLUA ASSERTION VIOLATION\n"
        "message:   %s\n"
        "condition: %s\n"
        "file:      %s (%d)\n"
        "function:  %s\n",
        message, condition, file, line_number, function);

    // Ensure all streams are flushed before aborting
    (void)std::fflush(nullptr);

    std::abort();
}

} // namespace xrlua::detail
