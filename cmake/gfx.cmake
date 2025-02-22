ctr_add_graphics_target(gfx ATLAS
  OPTIONS
    -f rgba -z auto -H gfx.h
  INPUTS
    gfx/cartridge.png
    gfx/cartridge-sel.png
    gfx/sd-card.png
    gfx/sd-card-sel.png
    gfx/bubble-cartridge.png
    gfx/bubble-cartridge-sel.png
    gfx/bubble-sd-card.png
    gfx/bubble-sd-card-sel.png
    gfx/btn-check.png
)

add_dependencies(${PROJECT_NAME} gfx)

dkp_install_assets(romfs TARGETS gfx)
