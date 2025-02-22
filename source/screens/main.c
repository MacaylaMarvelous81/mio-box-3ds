#include "screens/main.h"
#include <3ds.h>
#include <citro2d.h>
#include <gfx.h>

#define BETWEEN(min, x, max) (min < x && x < max)

extern C2D_SpriteSheet spriteSheet;

typedef enum {
  IMG_CARTRIDGE,
  IMG_CARTRIDGE_SEL,
  IMG_SD_CARD,
  IMG_SD_CARD_SEL,
  IMG_BUBBLE_CARTRIDGE,
  IMG_BUBBLE_CARTRIDGE_SEL,
  IMG_BUBBLE_SD_CARD,
  IMG_BUBBLE_SD_CARD_SEL,
  IMG_BUTTON_CHECK,
  IMG_MAX,
} ImageIndex;

typedef enum {
  SELECTION_CARTRIDGE,
  SELECTION_SD_CARD,
  SELECTION_DOUJINSOFT,
} Selection;

C2D_Image images[IMG_MAX];
Selection selection;

void mainOpen() {
  // TODO: Maybe use the same image file for variants like a spritesheet,
  // instead of separate files like 'default' and 'select'
  images[IMG_CARTRIDGE] =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_cartridge_idx);
  images[IMG_CARTRIDGE_SEL] =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_cartridge_sel_idx);
  images[IMG_SD_CARD] = C2D_SpriteSheetGetImage(spriteSheet, gfx_sd_card_idx);
  images[IMG_SD_CARD_SEL] =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_sd_card_sel_idx);
  images[IMG_BUBBLE_CARTRIDGE] =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_bubble_cartridge_idx);
  images[IMG_BUBBLE_CARTRIDGE_SEL] =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_bubble_cartridge_sel_idx);
  images[IMG_BUBBLE_SD_CARD] =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_bubble_sd_card_idx);
  images[IMG_BUBBLE_SD_CARD_SEL] =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_bubble_sd_card_sel_idx);
  images[IMG_BUTTON_CHECK] =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_btn_check_idx);

  selection = SELECTION_CARTRIDGE;
}

void mainUpdate() {
  touchPosition touch;
  hidTouchRead(&touch);

  if (BETWEEN(258, touch.px, 258 + images[IMG_BUTTON_CHECK].subtex->width) &&
      BETWEEN(213, touch.py, 213 + images[IMG_BUTTON_CHECK].subtex->height)) {
  }
  if (BETWEEN(80, touch.px, 80 + images[IMG_CARTRIDGE].subtex->width) &&
      BETWEEN(100, touch.py, 100 + images[IMG_CARTRIDGE].subtex->height))
    selection = SELECTION_CARTRIDGE;
  if (BETWEEN(180, touch.px, 180 + images[IMG_SD_CARD].subtex->width) &&
      BETWEEN(100, touch.py, 100 + images[IMG_SD_CARD].subtex->height))
    selection = SELECTION_SD_CARD;
}

void mainDrawTop(float iod) {}

void mainDrawBottom() {
  C2D_Prepare();

  C2D_DrawImageAt(images[IMG_BUTTON_CHECK], 258, 213, 0, NULL, 1.0f, 1.0f);
  C2D_DrawImageAt(images[selection == SELECTION_CARTRIDGE ? IMG_CARTRIDGE_SEL
                                                          : IMG_CARTRIDGE],
                  80, 100, 0, NULL, 1.0f, 1.0f);
  C2D_DrawImageAt(
      images[selection == SELECTION_CARTRIDGE ? IMG_BUBBLE_CARTRIDGE_SEL
                                              : IMG_BUBBLE_CARTRIDGE],
      30, 70, 0, NULL, 1.0f, 1.0f);
  C2D_DrawImageAt(
      images[selection == SELECTION_SD_CARD ? IMG_SD_CARD_SEL : IMG_SD_CARD],
      180, 100, 0, NULL, 1.0f, 1.0f);
  C2D_DrawImageAt(images[selection == SELECTION_SD_CARD ? IMG_BUBBLE_SD_CARD_SEL
                                                        : IMG_BUBBLE_SD_CARD],
                  120, 70, 0, NULL, 1.0f, 1.0f);

  C2D_Flush();
}
