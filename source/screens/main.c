#include "screens/main.h"
#include <3ds.h>
#include <citro2d.h>
#include <gfx.h>

extern C2D_TextBuf textBuf;
extern C2D_SpriteSheet spriteSheet;

C2D_Image imgCartridge;
C2D_Image imgCartridgeSel;
C2D_Image imgBubbleCartridge;
C2D_Image imgBubbleCartridgeSel;
C2D_Image imgBtnCheck;

typedef enum {
  SELECTION_CARTRIDGE,
  SELECTION_SD_CARD,
  SELECTION_DOUJINSOFT,
} Selection;

Selection selection;

void mainOpen() {
  // TODO: Maybe use the same image file for variants like a spritesheet,
  // instead of separate files like 'default' and 'select'
  imgCartridge = C2D_SpriteSheetGetImage(spriteSheet, gfx_cartridge_idx);
  imgCartridgeSel = C2D_SpriteSheetGetImage(spriteSheet, gfx_cartridge_sel_idx);
  imgBubbleCartridge =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_bubble_cartridge_idx);
  imgBubbleCartridgeSel =
      C2D_SpriteSheetGetImage(spriteSheet, gfx_bubble_cartridge_sel_idx);
  imgBtnCheck = C2D_SpriteSheetGetImage(spriteSheet, gfx_btn_check_idx);

  selection = SELECTION_CARTRIDGE;
}

void mainUpdate() {}

void mainDrawTop(float iod) {}

void mainDrawBottom() {
  C2D_Prepare();

  C2D_DrawRectangle(0, 0, 0, 320, 240, 0xc62828ff, 0xc62828ff, 0xc62828ff,
                    0xc62828ff);
  C2D_DrawImageAt(selection == SELECTION_CARTRIDGE ? imgCartridgeSel
                                                   : imgCartridge,
                  80, 100, 0, NULL, 1.0f, 1.0f);
  C2D_DrawImageAt(selection == SELECTION_CARTRIDGE ? imgBubbleCartridgeSel
                                                   : imgBubbleCartridge,
                  30, 70, 0, NULL, 1.0f, 1.0f);
  C2D_DrawImageAt(imgBtnCheck, 258, 213, 0, NULL, 1.0f, 1.0f);

  C2D_Flush();
}
