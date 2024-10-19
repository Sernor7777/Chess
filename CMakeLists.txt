cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

# Set output directory for the compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option for shared libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Include FetchContent for SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Gather all .cpp files in the src directory
file(GLOB_RECURSE SOURCES src/*.cpp)

# Include header files
include_directories(include)

# Create the executable target (Chess)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Copy assets folder to the build directory
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
add_compile_definitions(ASSETS_DIR="${ASSETS_DIR}")
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${ASSETS_DIR}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets"
)

# Copy OpenAL DLL if building on Windows
if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()
