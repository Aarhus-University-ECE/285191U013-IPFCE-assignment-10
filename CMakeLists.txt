cmake_minimum_required(VERSION 3.16)
project(assignment-10 VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG        v3.4.0 # newest version as of 2023-11-03T10:38:28 CET
)

FetchContent_MakeAvailable(Catch2)

add_library(linked_list STATIC linked_list.c)
add_library(btree STATIC btree.c)

set(libs linked_list btree)

# Force compiler to output in color when you use ninja as generator
# https://stackoverflow.com/questions/73349743/ninja-build-system-gcc-clang-doesnt-output-diagnostic-colors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")

foreach(lib ${libs})
	target_compile_options(${lib}
		PUBLIC
		$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wpedantic>
	)
endforeach()

add_executable(unit-tests tests/tests.cpp)
target_include_directories(unit-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(unit-tests ${libs})
target_link_libraries(unit-tests Catch2::Catch2WithMain)
target_compile_options(unit-tests PRIVATE -Wno-comment)
