cmake_minimum_required (VERSION 3.28)

project(BMtoBMPCpp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(WIN32_CC i686-w64-mingw32-g++)
set(WIN64_CC x86_64-w64-mingw32-g++)

add_compile_options(
    -std=c++20
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wuninitialized
    -Wmissing-include-dirs
    -Wshadow
    -Wundef
    -Winvalid-pch
    -Wzero-as-null-pointer-constant
    -Wctor-dtor-privacy
    -Wold-style-cast
    -Woverloaded-virtual
)

set(AUTO_FMT clang-format)
set(CODE_STYLE GNU)

set(INCL_DIR "${PROJECT_SOURCE_DIR}/include")
set(INCL_FILES
    "${INCL_DIR}/bitmap_image.hpp"
    "${INCL_DIR}/converter.hpp"
    "${INCL_DIR}/utils.hpp"
)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(SRC_FILES
    "${SRC_DIR}/bitmap_image.cpp"
    "${SRC_DIR}/converter.cpp"
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/utils.cpp"
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

# Format target
add_custom_target(format
    COMMAND ${AUTO_FMT} -style=${CODE_STYLE} -i ${SRC_FILES} ${INCL_FILES}
    COMMENT "Auto-formatting code."
)

# Test target
add_custom_target(test
    COMMAND valgrind --leak-check=yes ./${PROJECT_NAME} AUTOGRPH.BM AUTOGRPH.PAL
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Testing for memory leaks with Valgrind."
)

# `full` target
add_custom_target(full
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test
    COMMENT "Running full build (clean, format, build, and test)."
)

# Default/All target
add_executable(${PROJECT_NAME} ${SRC_FILES})
add_dependencies(${PROJECT_NAME} format)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCL_DIR})

if (DEFINED ARCH_SUFFIX)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}${ARCH_SUFFIX}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()
