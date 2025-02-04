cmake_minimum_required(VERSION 3.5)
set(CMAKE_CODEBLOCKS_EXCLUDE_EXTERNAL_FILES ON)

set(EXE "birdcpp")
set(IMGUI_DIR "include/imgui")
set(INCLUDE_DIRECTORY "include/")
set(SOURCE_DIRECTORY "src")
# SOURCES = main.cpp
# SOURCES += ${IMGUI_DIR}/*.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/
# SOURCES += ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp

file(GLOB Source CONFIGURE_DEPENDS ${SOURCE_DIRECTORY}/*.cpp ${SOURCE_DIRECTORY}/backends/imgui/*.cpp)
file(GLOB Headers CONFIGURE_DEPENDS ${SOURCE_DIRECTORY}/*.h ${SOURCE_DIRECTORY}/backends/imgui/*.h)
file(GLOB ImGUISource CONFIGURE_DEPENDS ${IMGUI_DIR}/*.cpp)
file(GLOB ImGUIHeaders CONFIGURE_DEPENDS ${IMGUI_DIR}/*.h)

project(${EXE})

find_package(SDL2 REQUIRED)
include_directories(${EXE} ${SDL2_INCLUDE_DIRS})

add_executable(${EXE} ${Source} ${Headers} ${ImGUISource} ${ImGUIHeaders})

target_include_directories(${EXE} PRIVATE ${INCLUDE_DIRECTORY} ${IMGUI_DIR})
target_link_libraries(${EXE} GL dl ${SDL2_LIBRARIES})
