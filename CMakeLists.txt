cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

# Set policy for INTERPROCEDURAL_OPTIMIZATION
cmake_policy(SET CMP0069 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

# Set output directory for the compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Handle assert behavior based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)  # Disables asserts in Release
else()
    remove_definitions(-DNDEBUG)  # Ensures asserts are enabled in Debug
endif()

# Set compiler flags for all configurations
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Base flags for all configurations
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -mpopcnt -mbmi")
    
    # Release-specific flags
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto -ffast-math -funroll-loops -fomit-frame-pointer")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
    
    # Debug-specific flags
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -march=native")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Base flags for all configurations
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")
    
    # Release-specific flags
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Ob3 /Oi /Ot /GL /fp:fast /GS- /MD")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
endif()

# Option for shared libraries
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Include FetchContent for SFML
include(FetchContent)

# Configure SFML options
set(SFML_BUILD_NETWORK FALSE)
set(SFML_BUILD_EXAMPLES FALSE)
set(SFML_BUILD_DOC FALSE)
set(SFML_BUILD_TEST FALSE)
set(SFML_ENABLE_IPO FALSE)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Gather source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Create executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link libraries and set compile features
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Set target-specific compile options for all configurations
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -mpopcnt
        -mbmi
        -msse4.2
        -march=native
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /arch:AVX2
    )
endif()

# Enable IPO/LTO if available
include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
if(supported)
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Copy assets folder to the build directory
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
add_compile_definitions(ASSETS_DIR="${ASSETS_DIR}")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${ASSETS_DIR}" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

# Copy OpenAL DLL if building on Windows
if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        VERBATIM)
endif()
