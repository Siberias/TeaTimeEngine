cmake_minimum_required (VERSION 3.27)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SFML3Template")

# Libraries
include(FetchContent)

FetchContent_Declare(json 
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    plog
    GIT_REPOSITORY https://github.com/SergiusTheBest/plog
    GIT_TAG        1.1.10
    GIT_SHALLOW    true
)
FetchContent_MakeAvailable(plog)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Setup project files
include_directories("Include")

set(SOURCES "Source/Application.cpp" "Source/Main.cpp" "Source/Scene.cpp" 
    "Source/SceneLoader.cpp")
add_executable(SFML3Template ${SOURCES})
add_subdirectory("Source/Services")

target_compile_features(SFML3Template PRIVATE cxx_std_20)
target_link_libraries(SFML3Template PRIVATE nlohmann_json::nlohmann_json plog::plog 
    SFML::Graphics)

set_property(TARGET SFML3Template PROPERTY DEBUGGER_WORKING_DIRECTORY 
    "${CMAKE_SOURCE_DIR}")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 
    SFML3Template)
