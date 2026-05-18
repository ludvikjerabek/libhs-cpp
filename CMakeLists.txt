cmake_minimum_required(VERSION 3.16)
project(libhs-cpp LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build both shared and static by default
option(BUILD_SHARED_LIBS "Build shared library" ON)
option(BUILD_STATIC_LIBS "Build static library" ON)

# Locate threading support
find_package(Threads REQUIRED)

# Locate a libhs-compatible backend.
# This may be Intel Hyperscan or VectorCamp VectorScan.
find_library(LIBHS_LIBRARY NAMES hs)
find_path(LIBHS_INCLUDE_DIR NAMES hs/hs.h)

if(NOT LIBHS_LIBRARY OR NOT LIBHS_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find libhs. Install Intel Hyperscan or VectorScan, or set LIBHS_LIBRARY and LIBHS_INCLUDE_DIR.")
endif()

message(STATUS "libhs Library: ${LIBHS_LIBRARY}")
message(STATUS "libhs Include: ${LIBHS_INCLUDE_DIR}")

# Source files
set(LIBHS_CPP_SOURCES
        src/PlatformInfo.cpp
        src/Pattern.cpp
        src/Literal.cpp
        src/MultiPattern.cpp
        src/MultiPatternExtended.cpp
        src/MultiLiteral.cpp
        src/ExpressionInfo.cpp
        src/Database.cpp
        src/Scratch.cpp
        src/ExtendedExpressionContext.cpp
        src/Scanner.cpp
        src/Stream.cpp
)

# Create shared library if enabled
if(BUILD_SHARED_LIBS)
    add_library(libhs-cpp SHARED ${LIBHS_CPP_SOURCES})
    set_target_properties(libhs-cpp PROPERTIES
            OUTPUT_NAME "hs-cpp"
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR}
    )
    target_include_directories(libhs-cpp PUBLIC
            ${LIBHS_INCLUDE_DIR}
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
            $<INSTALL_INTERFACE:include/libhs-cpp>
    )
    target_link_libraries(libhs-cpp
            PUBLIC
            ${LIBHS_LIBRARY}
            Threads::Threads
    )
endif()

# Create static library if enabled
if(BUILD_STATIC_LIBS)
    add_library(libhs-cpp-static STATIC ${LIBHS_CPP_SOURCES})
    set_target_properties(libhs-cpp-static PROPERTIES
            OUTPUT_NAME "hs-cpp"
            POSITION_INDEPENDENT_CODE ON
    )
    target_include_directories(libhs-cpp-static PUBLIC
            ${LIBHS_INCLUDE_DIR}
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
            $<INSTALL_INTERFACE:include/libhs-cpp>
    )
    target_link_libraries(libhs-cpp-static
            PUBLIC
            ${LIBHS_LIBRARY}
            Threads::Threads
    )
endif()

# Install headers
install(DIRECTORY includes/
        DESTINATION include/libhs-cpp
        FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY src/
        DESTINATION include/libhs-cpp
        FILES_MATCHING PATTERN "*.h"
)

# Install libraries
if(BUILD_SHARED_LIBS)
    install(TARGETS libhs-cpp
            EXPORT libhs-cppTargets
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            INCLUDES DESTINATION include/libhs-cpp
    )
endif()

if(BUILD_STATIC_LIBS)
    install(TARGETS libhs-cpp-static
            EXPORT libhs-cppTargets
            ARCHIVE DESTINATION lib
            INCLUDES DESTINATION include/libhs-cpp
    )
endif()

# Installation and versioning
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/libhs-cppConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

install(EXPORT libhs-cppTargets
        FILE libhs-cppTargets.cmake
        DESTINATION lib/cmake/libhs-cpp
)

# Build example programs
option(BUILD_EXAMPLES "Build example executables" ON)

if(BUILD_EXAMPLES)
    # Function to add example with both static and dynamic versions
    function(add_example_executable NAME SOURCE)
        if(BUILD_SHARED_LIBS)
            add_executable(${NAME} ${SOURCE})
            target_link_libraries(${NAME} PRIVATE libhs-cpp)
        endif()

        if(BUILD_STATIC_LIBS)
            add_executable(${NAME}_static ${SOURCE})
            target_link_libraries(${NAME}_static PRIVATE libhs-cpp-static)
        endif()
    endfunction()

    # Add examples with both static and dynamic versions
    add_example_executable(single_pattern_test examples/SinglePatternSearch.cpp)
    add_example_executable(multi_pattern_test examples/MultiPatternSearch.cpp)
    add_example_executable(single_pattern_stream_test examples/SinglePatternStream.cpp)

    if(BUILD_SHARED_LIBS)
        message(STATUS "Building dynamic examples")
    endif()
    if(BUILD_STATIC_LIBS)
        message(STATUS "Building static examples")
    endif()
endif()

# Create uninstall target
if(NOT TARGET uninstall)
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()