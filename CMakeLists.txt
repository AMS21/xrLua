cmake_minimum_required(VERSION 3.16)

# Policy
if(${CMAKE_VERSION} VERSION_LESS 3.28)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
  cmake_policy(VERSION 3.28)
endif()

project(xrLua)

set(CMAKE_CXX_STANDARD 17)

# Check if xrLua is being used directly or via add_subdirectory, but allow
# overriding
if(NOT DEFINED XRLUA_MAIN_PROJECT)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(XRLUA_MAIN_PROJECT TRUE)
  else()
    set(XRLUA_MAIN_PROJECT FALSE)
  endif()
endif()

# Options
option(XRLUA_COVERAGE_BUILD "Enable coverage flags" OFF)

# Settings
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CheckIPOSupported)
check_ipo_supported(RESULT XRLUA_LTO_SUPPORTED)

# Determine compiler flags
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  set(XRLUA_FLAGS
      -fno-exceptions
      -fno-rtti
      -fstrong-eval-order
      -pipe
      # Warnings
      -Waligned-new=all
      -Wall
      -Walloc-zero
      -Walloca
      -Warray-bounds
      -Wcast-align
      -Wcast-qual
      -Wconversion
      -Wctor-dtor-privacy
      -Wdate-time
      -Wdelete-non-virtual-dtor
      -Wdisabled-optimization
      -Wdouble-promotion
      -Wduplicated-branches
      -Wduplicated-cond
      -Wextra
      -Wfloat-equal
      -Wformat-overflow=2
      -Wformat-signedness
      -Wformat-truncation=2
      -Wformat=2
      -Wimplicit-fallthrough=5
      -Winit-self
      -Winvalid-pch
      -Wlogical-op
      -Wmisleading-indentation
      -Wmissing-declarations
      -Wmissing-field-initializers
      -Wmissing-format-attribute
      -Wmissing-include-dirs
      -Wmissing-noreturn
      -Wnoexcept
      -Wnon-virtual-dtor
      -Wnormalized
      -Wnull-dereference
      -Wold-style-cast
      -Woverloaded-virtual
      -Wpacked
      -Wpedantic
      -Wplacement-new=2
      -Wpointer-arith
      -Wredundant-decls
      -Wregister
      -Wreorder
      -Wrestrict
      -Wshadow
      -Wshift-overflow=2
      -Wsign-conversion
      -Wsign-promo
      -Wstack-protector
      -Wstrict-aliasing=2
      -Wstrict-null-sentinel
      -Wstringop-overflow=2
      -Wsuggest-attribute=format
      -Wsuggest-attribute=noreturn
      -Wsuggest-final-methods
      -Wsuggest-final-types
      -Wsuggest-override
      -Wswitch-enum
      -Wsync-nand
      -Wtrampolines
      -Wundef
      -Wuninitialized
      -Wunreachable-code
      -Wunsafe-loop-optimizations
      -Wunused
      -Wunused-const-variable=2
      -Wunused-parameter
      -Wvector-operation-performance
      -Wvla
      -Wwrite-strings
      -Wzero-as-null-pointer-constant
      -Werror
      -Wno-padded
      -Wno-switch-enum
      -Wno-unused-macros
      -Wno-variadic-macros
      -Wno-unused-function
      -pedantic
      -pedantic-errors)
  set(XRLUA_DEBUG_FLAGS -fcheck-new -fvar-tracking -fvar-tracking-assignments
                        -grecord-gcc-switches)
  set(XRLUA_OPT_FLAGS
      -fallow-store-data-races
      -fdeclone-ctor-dtor
      -fdevirtualize-speculatively
      -fgcse-las
      -fgcse-sm
      -fisolate-erroneous-paths-attribute
      -fivopts
      -fmerge-all-constants
      -fmodulo-sched
      -fmodulo-sched-allow-regmoves
      -fnothrow-opt
      -fstdarg-opt
      -fstrict-enums
      -ftree-loop-im
      -ftree-loop-ivcanon)
  set(XRLUA_COVERAGE_FLAGS
      --coverage
      -fno-common
      -fno-inline
      -fno-inline-functions
      -fno-omit-frame-pointer
      -fprofile-arcs
      -ftest-coverage)
  if(XRLUA_LTO_SUPPORTED)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
    set(XRLUA_OPT_FLAGS -fdevirtualize-at-ltrans -fipa-pta -fwhole-program)
  endif()

  # GCC-8 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8)
    set(XRLUA_FLAGS ${XRLUA_FLAGS} -Wsuggest-attribute=cold
                    -Wsuggest-attribute=malloc -Wcatch-value=3 -Wextra-semi)
    set(XRLUA_COVERAGE_FLAGS ${XRLUA_COVERAGE_FLAGS} -fprofile-abs-path)
  endif()

  # GCC-9 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 9)
    set(XRLUA_FLAGS ${XRLUA_FLAGS} -Wattribute-alias=2 -Wuseless-cast
                    -Wclass-conversion -Wdeprecated-copy)
  elseif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8)
    set(XRLUA_FLAGS ${XRLUA_FLAGS} -Wattribute-alias)
  endif()

  # GCC-10 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 10)
    set(XRLUA_FLAGS ${XRLUA_FLAGS} -Warith-conversion -Wcomma-subscript
                    -Wmismatched-tags -Wredundant-tags -Wvolatile)
    set(XRLUA_OPT_FLAGS ${XRLUA_OPT_FLAGS} -ffinite-loops
                        -fallow-store-data-races)
  endif()

  # GCC-11 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 11)
    set(XRLUA_FLAGS
        ${XRLUA_FLAGS} -Wenum-conversion -Wstringop-overread
        -Wdeprecated-enum-enum-conversion -Wdeprecated-enum-float-conversion
        -Winvalid-imported-macros)
  endif()

  # GCC-12 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12)
    set(XRLUA_FLAGS ${XRLUA_FLAGS} -Wbidi-chars=any -Wuse-after-free=3
                    -Winterference-size)
    set(XRLUA_OPT_FLAGS ${XRLUA_OPT_FLAGS} -fimplicit-constexpr)
    set(XRLUA_DEBUG_FLAGS
        ${XRLUA_DEBUG_FLAGS} -fharden-compares -fharden-conditional-branches
        -ftrivial-auto-var-init=pattern)
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(XRLUA_FLAGS
      -fno-exceptions
      -fno-rtti
      # Warnings
      -Weverything
      -Wformat=2
      -Wstrict-aliasing=2
      -Werror
      -Wno-constexpr-not-const
      -Wno-c++-compat
      -Wno-c++0x-compat
      -Wno-c++0x-extensions
      -Wno-c++0x-narrowing
      -Wno-c++1y-extensions
      -Wno-c++1z-compat
      -Wno-c++1z-extensions
      -Wno-c++2a-compat
      -Wno-c++2a-extensions
      -Wno-c++11-compat
      -Wno-c++11-extensions
      -Wno-c++11-narrowing
      -Wno-c++14-compat
      -Wno-c++14-extensions
      -Wno-c++17-compat
      -Wno-c++17-extensions
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-c++98-c++11-compat
      -Wno-c++98-c++11-compat-pedantic
      -Wno-c++98-c++11-c++14-compat
      -Wno-c++98-c++11-c++14-compat-pedantic
      -Wno-c++98-c++11-c++14-c++17-compat
      -Wno-c++98-c++11-c++14-c++17-compat-pedantic
      -Wno-documentation-unknown-command
      -Wno-gnu-zero-variadic-macro-arguments
      -Wno-language-extension-token
      -Wno-missing-prototypes
      -Wno-missing-variable-declarations
      -Wno-padded
      -Wno-switch-enum
      -Wno-unused-macros
      -Wno-unused-template
      -Wno-variadic-macros
      -Wno-weak-vtables
      -pedantic
      -pedantic-errors)
  set(XRLUA_OPT_FLAGS
      -felide-constructors
      -fforce-emit-vtables
      -fmerge-all-constants
      -fstrict-aliasing
      -fstrict-enums
      -fstrict-return
      -fstrict-vtable-pointers)
  set(XRLUA_DEBUG_FLAGS -ftrivial-auto-var-init=pattern -grecord-command-line)
  set(XRLUA_COVERAGE_FLAGS
      -fcoverage-mapping
      -fno-common
      -fno-inline
      -fno-inline-functions
      -fno-omit-frame-pointer
      -fprofile-arcs
      -fprofile-instr-generate
      -ftest-coverage)
  if(XRLUA_LTO_SUPPORTED)
    set(XRLUA_OPT_FLAGS -flto=full -fwhole-program-vtables
                        -fvirtual-function-elimination)
  endif()

  # Clang-10 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 10)
    set(XRLUA_FLAGS ${XRLUA_FLAGS} -Wno-c++20-compat -Wno-c++20-extensions)
  endif()

  # Clang-12 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12)
    set(XRLUA_OPT_FLAGS ${XRLUA_OPT_FLAGS} -ffinite-loops)
  endif()

  # Clang-13 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 13
     AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17)
    set(XRLUA_FLAGS ${XRLUA_FLAGS} -Wno-c++2b-extensions)
  endif()

  # Clang-16 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 16)
    set(XRLUA_FLAGS ${XRLUA_FLAGS} -Wno-unsafe-buffer-usage)
  endif()

  # Clang-17 flags
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 17)
    set(XRLUA_FLAGS ${XRLUA_FLAGS} -Wno-c++23-extensions)
  endif()
endif()

# Normalize flags
string(REPLACE ";" " " XRLUA_FLAGS "${XRLUA_FLAGS}")
string(REPLACE ";" " " XRLUA_DEBUG_FLAGS "${XRLUA_DEBUG_FLAGS}")
string(REPLACE ";" " " XRLUA_OPT_FLAGS "${XRLUA_OPT_FLAGS}")
string(REPLACE ";" " " XRLUA_COVERAGE_FLAGS "${XRLUA_COVERAGE_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XRLUA_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${XRLUA_DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${XRLUA_OPT_FLAGS}")

if (XRLUA_COVERAGE_BUILD)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${XRLUA_COVERAGE_FLAGS}")
endif()

# subdirectories
add_subdirectory(src)
