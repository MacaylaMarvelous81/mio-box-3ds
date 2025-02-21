cmake_minimum_required(VERSION 3.13)

project(mio-box-3ds LANGUAGES C VERSION 1.0.0)

add_executable(${PROJECT_NAME}
  source/main.c

  source/screens/main.c
)

target_compile_options(${PROJECT_NAME} PRIVATE
  -g -O2 -Wall
)

target_include_directories(${PROJECT_NAME} PRIVATE
  include
  ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME} citro2d citro3d)

ctr_add_graphics_target(gfx ATLAS
  OPTIONS
    -f rgba -z auto -H gfx.h
  INPUTS
    gfx/cartridge.png
    gfx/bubble-left.png
)

add_dependencies(${PROJECT_NAME} gfx)

dkp_add_asset_target(romfs ${CMAKE_CURRENT_BINARY_DIR}/romfs)
dkp_install_assets(romfs TARGETS gfx)

ctr_generate_smdh(${PROJECT_NAME}.smdh
  NAME "${PROJECT_NAME}"
  DESCRIPTION "v${PROJECT_VERSION}"
  AUTHOR "Jomar Milan"
)

ctr_create_3dsx(${PROJECT_NAME}
  SMDH ${PROJECT_NAME}.smdh
  ROMFS romfs
)
