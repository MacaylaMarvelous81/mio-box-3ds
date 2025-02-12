#include "screens/main.h"
#include <citro2d.h>

extern C2D_TextBuf textBuf;

void drawButton(float x, float y, float z, float w, float h, C2D_Text text,
                u32 clr) {
  u32 clrButton = C2D_Color32(0x26, 0xa6, 0x9a, 0xff);
  C2D_DrawRectangle(x, y, z, w, h, clrButton, clrButton, clrButton, clrButton);
  C2D_DrawText(&text, C2D_WithColor | C2D_AlignCenter, x + w / 2, y, z, 0.5f,
               0.5, clr);
}

void mainUpdate() {}

void mainDrawTop(float iod) {}

void mainDrawBottom() {
  C2D_Prepare();

  C2D_DrawRectangle(0, 0, 0, 320, 240, 0xc62828ff, 0xc62828ff, 0xc62828ff,
                    0xc62828ff);
  C2D_Text text;
  C2D_TextParse(&text, textBuf, "Open Save File");
  C2D_TextOptimize(&text);
  drawButton(80, 60, 0, 160, 30, text, 0xffffffff);

  C2D_TextParse(&text, textBuf, "DoujinSoft");
  C2D_TextOptimize(&text);
  drawButton(80, 120, 0, 160, 30, text, 0xffffffff);

  C2D_Flush();
}
