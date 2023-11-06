project(xrLua)

file(GLOB XRLUA_SOURCE_FILES "xrLua/lexer/lexer.hpp" "xrLua/utils/is_space.hpp"
     "xrLua/prelude.cpp" "xrLua/prelude.hpp")

add_library(${PROJECT_NAME}Lib STATIC ${XRLUA_SOURCE_FILES})
target_include_directories(${PROJECT_NAME}Lib
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)
