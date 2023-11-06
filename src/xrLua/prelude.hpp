#pragma once

#include "xrLua/utils/assert.hpp"

// Platform

// TODO

// MSVC compiler
#if defined(_MSC_VER) && !defined(__clang__)
#    define XRLUA_MSVC() 1
#    define XRLUA_MSVC_MAJOR() (_MSC_FULL_VER / 10000000)
#    define XRLUA_MSVC_MINOR() (_MSC_FULL_VER % 10000000 / 100000)
#    define XRLUA_MSVC_PATCH() (_MSC_FULL_VER % 100000)
#else
#    define XRLUA_MSVC() 0
#    define XRLUA_MSVC_MAJOR() 0
#    define XRLUA_MSVC_MINOR() 0
#    define XRLUA_MSVC_PATCH() 0
#endif

// Clang compiler
#ifdef __clang__
#    define XRLUA_CLANG() 1
#    define XRLUA_CLANG_MAJOR() __clang_major__
#    define XRLUA_CLANG_MINOR() __clang_minor__
#    define XRLUA_CLANG_PATCH() __clang_patchlevel__
#else
#    define XRLUA_CLANG() 0
#    define XRLUA_CLANG_MAJOR() 0
#    define XRLUA_CLANG_MINOR() 0
#    define XRLUA_CLANG_PATCH() 0
#endif

// GCC compiler
#if (defined(__GNUC__) || defined(__GNUG__)) && !XRLUA_CLANG()
#    define XRLUA_GCC() 1
#    define XRLUA_GCC_MAJOR() __GNUC__
#    define XRLUA_GCC_MINOR() __GNUC_MINOR__
#    define XRLUA_GCC_PATCH() __GNUC_PATCHLEVEL__
#else
#    define XRLUA_GCC() 0
#    define XRLUA_GCC_MAJOR() 0
#    define XRLUA_GCC_MINOR() 0
#    define XRLUA_GCC_PATCH() 0
#endif

// XRLUA_COMPILER_NAME
#if XRLUA_CLANG()
#    define XRLUA_COMPILER_NAME() "Clang"
#elif XRLUA_GCC()
#    define XRLUA_COMPILER_NAME() "GCC"
#elif XRLUA_MSVC()
#    define XRLUA_COMPILER_NAME() "MSVC"
#endif

// XRLUA_ASSUME
#if XRLUA_CLANG()
#    define XRLUA_ASSUME(condition) __builtin_assume(condition)
#elif XRLUA_GCC()
// clang-format off
#    define XRLUA_ASSUME(condition) if (condition){} else __builtin_unreachable()
// clang-format on
#elif XRLUA_MSVC()
#    define XRLUA_ASSUME(condition) __assume(condition)
#endif

// XRLUA_CURRENT_FUNCTION
#if XRLUA_CLANG() || XRLUA_GCC()
#    define XRLUA_CURRENT_FUNCTION() __PRETTY_FUNCTION__
#elif XRLUA_MSVC()
#    define XRLUA_CURRENT_FUNCTION() __FUNCSIG__
#endif

// Attributes

// XRLUA_ATTR_CONST
#if XRLUA_CLANG() || XRLUA_GCC()
#    define XRLUA_ATTR_CONST __attribute__((const))
#else
#    define XRLUA_ATTR_CONST
#endif

// XRLUA_ATTR_FLATTEN
#if XRLUA_CLANG() || XRLUA_GCC()
#    define XRLUA_ATTR_FLATTEN __attribute__((flatten))
#else
#    define XRLUA_ATTR_FLATTEN
#endif

// XRLUA_ATTR_PURE
#if XRLUA_CLANG() || XRLUA_GCC()
#    define XRLUA_ATTR_PURE __attribute__((pure))
#else
#    define XRLUA_ATTR_PURE
#endif

// XRLUA_ATTR_RET_NONNULL
#if XRLUA_CLANG() || XRLUA_GCC()
#    define XRLUA_ATTR_RET_NONNULL __attribute__((returns_nonnull))
#else
#    define XRLUA_ATTR_RET_NONNULL
#endif

// XRLUA_ATTR_NONNULL
#if XRLUA_CLANG() || XRLUA_GCC()
#    define XRLUA_ATTR_NONNULL __attribute__((nonnull))
#else
#    define XRLUA_ATTR_NONNULL
#endif
