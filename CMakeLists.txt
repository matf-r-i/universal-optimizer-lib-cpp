cmake_minimum_required(VERSION 3.15)
project(UniversalOptimizerLib
	VERSION 1.0.0
	DESCRIPTION "Universal Optimizer Library - C++ Implementation"
	LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

# Project directories
set(PROJECT_SOURCE_DIR_ABS "${CMAKE_CURRENT_SOURCE_DIR}")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR_ABS}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR_ABS}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR_ABS}/tests")
set(DOCS_DIR "${PROJECT_SOURCE_DIR_ABS}/docs")

# Create library
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
add_library(uo ${SOURCES})

target_include_directories(uo PUBLIC
	$<BUILD_INTERFACE:${INCLUDE_DIR}>
	$<INSTALL_INTERFACE:include>
)

# Compiler-specific settings
if(MSVC)
	target_compile_options(uo PRIVATE /W4)
else()
	target_compile_options(uo PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Testing
enable_testing()

# Find test files
file(GLOB_RECURSE TEST_SOURCES "${TEST_DIR}/*.cpp")

if(TEST_SOURCES)
	# Try to find GTest
	find_package(GTest QUIET)

	if(NOT GTEST_FOUND)
		# Try to find Catch2
		find_package(Catch2 3 QUIET)

		if(Catch2_FOUND)
			message(STATUS "Using Catch2 testing framework")

			foreach(test_source ${TEST_SOURCES})
				get_filename_component(test_name "${test_source}" NAME_WE)
				add_executable(${test_name} "${test_source}")
				target_link_libraries(${test_name} PRIVATE uo Catch2::Catch2WithMain)
				add_test(NAME ${test_name} COMMAND ${test_name})
			endforeach()
		else()
			message(STATUS "GTest and Catch2 not found. Tests will not be built.")
			message(STATUS "To enable testing, install GTest or Catch2:")
			message(STATUS "  - Ubuntu/Debian: sudo apt-get install libgtest-dev")
			message(STATUS "  - macOS: brew install catch2")
			message(STATUS "  - Or use vcpkg or conan for package management")
		endif()
	else()
		message(STATUS "Using GTest testing framework")

		foreach(test_source ${TEST_SOURCES})
			get_filename_component(test_name "${test_source}" NAME_WE)
			add_executable(${test_name} "${test_source}")
			target_link_libraries(${test_name} PRIVATE uo GTest::gtest GTest::gtest_main)
			add_test(NAME ${test_name} COMMAND ${test_name})
		endforeach()
	endif()
else()
	message(STATUS "No test files found in ${TEST_DIR}")
endif()

# Documentation target
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
	add_custom_target(docs
		COMMAND ${DOXYGEN_EXECUTABLE} "${PROJECT_SOURCE_DIR_ABS}/Doxyfile"
		WORKING_DIRECTORY "${PROJECT_SOURCE_DIR_ABS}"
		COMMENT "Building documentation with Doxygen"
	)
else()
	message(STATUS "Doxygen not found. Documentation target will not be available.")
endif()

# Code formatting target (clang-format)
find_program(CLANG_FORMAT_PROG clang-format)
if(CLANG_FORMAT_PROG)
	file(GLOB_RECURSE FORMAT_SOURCES
		"${SRC_DIR}/*.cpp" "${SRC_DIR}/*.hpp"
		"${INCLUDE_DIR}/*.cpp" "${INCLUDE_DIR}/*.hpp"
	)

	add_custom_target(format
		COMMAND ${CLANG_FORMAT_PROG} -i -style=file ${FORMAT_SOURCES}
		WORKING_DIRECTORY "${PROJECT_SOURCE_DIR_ABS}"
		COMMENT "Formatting code with clang-format"
	)
else()
	message(STATUS "clang-format not found. format target will not be available.")
endif()

# Install targets
install(TARGETS uo
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

install(DIRECTORY ${INCLUDE_DIR}/
	DESTINATION include
	FILES_MATCHING PATTERN "*.hpp"
)

# Summary
message(STATUS "")
message(STATUS "=== Build Configuration ===")
message(STATUS "Build Type:        ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard:       ${CMAKE_CXX_STANDARD}")
message(STATUS "Source Directory:  ${SRC_DIR}")
message(STATUS "Include Directory: ${INCLUDE_DIR}")
message(STATUS "Test Directory:    ${TEST_DIR}")
message(STATUS "")
message(STATUS "Available targets:")
message(STATUS "  - uo              (main library)")
if(DOXYGEN_FOUND)
	message(STATUS "  - docs            (generate documentation)")
endif()
if(TEST_SOURCES)
	message(STATUS "  - test            (run tests)")
endif()
if(CLANG_FORMAT_PROG)
	message(STATUS "  - format          (format code)")
endif()
message(STATUS "")
