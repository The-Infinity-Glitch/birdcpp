cmake_minimum_required(VERSION 3.5)

# For Code::Blocks generator
set(CMAKE_CODEBLOCKS_EXCLUDE_EXTERNAL_FILES ON)

# For other code editors
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Main application name
set(EXE "birdcpp")

# Main directories
set(INCLUDE_DIRECTORY "include")
set(SOURCE_DIRECTORY "src")

# Individual library directories
set(IMGUI_DIR "include/imgui")
set(FILE_DIALOG_DIR "include/ImGuiFileDialog")

# Main application source and hearders
file(GLOB Source CONFIGURE_DEPENDS ${SOURCE_DIRECTORY}/*.cpp ${SOURCE_DIRECTORY}/backends/imgui/*.cpp)
file(GLOB Headers CONFIGURE_DEPENDS ${SOURCE_DIRECTORY}/*.h ${SOURCE_DIRECTORY}/backends/imgui/*.h)

# ImGui source and headers to compile and link
file(GLOB ImGUISource CONFIGURE_DEPENDS ${IMGUI_DIR}/*.cpp)
file(GLOB ImGUIHeaders CONFIGURE_DEPENDS ${IMGUI_DIR}/*.h)

# ImGuiFileDialog source and headers to compile and link
file(GLOB FileDialogSource CONFIGURE_DEPENDS ${FILE_DIALOG_DIR}/*.cpp)
file(GLOB FileDialogHeaders CONFIGURE_DEPENDS ${FILE_DIALOG_DIR}/*.h ${FILE_DIALOG_DIR}/dirent/*.h ${FILE_DIALOG_DIR}/stb/*.h)

# Main application
project(${EXE})

# We uses SDL2 for windowing and input handling
find_package(SDL2 REQUIRED)
include_directories(${EXE} ${SDL2_INCLUDE_DIRS})

add_executable(${EXE} ${Source} ${Headers} ${ImGUISource} ${ImGUIHeaders} ${FileDialogSource} ${FileDialogHeaders})

target_include_directories(${EXE} PRIVATE ${INCLUDE_DIRECTORY} ${IMGUI_DIR} ${FILE_DIALOG_DIR})
target_link_libraries(${EXE} GL dl ${SDL2_LIBRARIES})
