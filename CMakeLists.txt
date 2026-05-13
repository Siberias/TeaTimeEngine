cmake_minimum_required (VERSION 3.27)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project (TeaTimeEngine VERSION 1.0.0)

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
set(SOURCES 
  "Source/TeaTimeEngine/Application.cpp"
  "Source/TeaTimeEngine/Scene.cpp"
)

add_library(TeaTimeEngine ${SOURCES})
add_library(TeaTimeEngine::TeaTimeEngine ALIAS TeaTimeEngine)

include_directories("Include/TeaTimeEngine")
target_include_directories(TeaTimeEngine PUBLIC "Include")

add_subdirectory("Source/TeaTimeEngine/Entities")
add_subdirectory("Source/TeaTimeEngine/Services")

target_compile_features(TeaTimeEngine PUBLIC cxx_std_20)
target_link_libraries(TeaTimeEngine PUBLIC
  nlohmann_json::nlohmann_json
  plog::plog
  SFML::Graphics)