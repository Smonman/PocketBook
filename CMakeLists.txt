# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(PocketBook C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# All source files
set(SOURCES
    src/PocketBook.c
    src/content.c
    src/statusled.c
    src/lcd.c
    src/key.c
    src/persistent.c
    src/words.c
    src/content.h
    src/statusled.h
    src/lcd.h
    src/key.h
    src/persistent.h
    src/words.h
    src/log.h
)

# Add executable. Default name is the project name, version 0.1
add_executable(PocketBook ${SOURCES})

add_definitions(-DDEBUG=5 -DLFS_YES_TRACE)

pico_set_program_name(PocketBook "PocketBook")
pico_set_program_version(PocketBook "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(PocketBook 0)
pico_enable_stdio_usb(PocketBook 1)

# Add the standard library to the build
target_link_libraries(PocketBook pico_stdlib)

# Add the standard include files to the build
target_include_directories(PocketBook PRIVATE ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(lib/Config)
add_subdirectory(lib/Fonts)
add_subdirectory(lib/GUI)
add_subdirectory(lib/Infrared)
add_subdirectory(lib/LCD)
add_subdirectory(lib/littlefs)
add_subdirectory(lib/pico-lfs)
include_directories(lib/Config)
include_directories(lib/Fonts)
include_directories(lib/GUI)
include_directories(lib/Infrared)
include_directories(lib/LCD)
include_directories(lib/littlefs)
include_directories(lib/pico-lfs)

# Add any user requested libraries
target_link_libraries(PocketBook
    pico_cyw43_arch_none
    LCD
    GUI
    Fonts
    Config
    Infrared
    littlefs
    pico-lfs
)

pico_add_extra_outputs(PocketBook)
