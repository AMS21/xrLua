project(xrLua)

file(GLOB XRLUA_SOURCE_FILES "main.cpp")

add_executable(${PROJECT_NAME} ${XRLUA_SOURCE_FILES})
