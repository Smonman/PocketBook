project(pico-lfs
  VERSION 1.0.0
  LANGUAGES C CXX
)

add_library(pico-lfs INTERFACE)

target_include_directories(pico-lfs INTERFACE
  .
  ../littlefs/
)

target_sources(pico-lfs INTERFACE
  pico_lfs.c
  ../littlefs/lfs.c
  ../littlefs/lfs_util.c
)

target_link_libraries(pico-lfs INTERFACE hardware_flash)
