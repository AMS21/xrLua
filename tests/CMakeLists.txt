project(xrLuaTests)

file(GLOB XRLUA_TESTS_SOURCES "prelude_test.cpp" "utils/is_space_test.cpp")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # gtests TEST macro triggers this warning
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-global-constructors")
endif()

add_executable(${PROJECT_NAME} ${XRLUA_TESTS_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gtest_main xrLuaLib)
gtest_discover_tests(${PROJECT_NAME})
