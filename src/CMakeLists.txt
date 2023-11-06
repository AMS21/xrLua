project(xrLua)

file(
  GLOB
  XRLUA_SOURCE_FILES
  "xrlua/lexer/lexer.hpp"
  "xrlua/utils/assert.hpp"
  "xrlua/utils/assert.cpp"
  "xrlua/utils/is_space.hpp"
  "xrlua/prelude.hpp")

add_library(${PROJECT_NAME}lib STATIC ${XRLUA_SOURCE_FILES})
target_include_directories(${PROJECT_NAME}lib
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}lib)
