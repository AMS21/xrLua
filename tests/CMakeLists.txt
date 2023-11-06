project(xrLuaTests)

file(GLOB XRLUA_TESTS_SOURCES "utils/assert_test.cpp" "utils/is_space_test.cpp")

add_executable(${PROJECT_NAME} ${XRLUA_TESTS_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain xrLuaLib)
catch_discover_tests(${PROJECT_NAME})
