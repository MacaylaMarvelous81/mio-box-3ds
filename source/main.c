#include "screens/main.h"
#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISPLAY_TRANSFER_FLAGS                                                 \
  (GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) |                       \
   GX_TRANSFER_RAW_COPY(0) | GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) |    \
   GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) |                              \
   GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

C2D_TextBuf textBuf;

int main(int argc, char *argv[]) {
  gfxInitDefault();
  gfxSet3D(true);
  C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
  C2D_Init(C2D_DEFAULT_MAX_OBJECTS);

  C3D_RenderTarget *topL =
      C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH16);
  C3D_RenderTarget *topR =
      C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH16);
  C3D_RenderTarget *bottom =
      C3D_RenderTargetCreate(240, 320, GPU_RB_RGBA8, GPU_RB_DEPTH16);
  C3D_RenderTargetSetOutput(topL, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);
  C3D_RenderTargetSetOutput(topR, GFX_TOP, GFX_RIGHT, DISPLAY_TRANSFER_FLAGS);
  C3D_RenderTargetSetOutput(bottom, GFX_BOTTOM, GFX_LEFT,
                            DISPLAY_TRANSFER_FLAGS);

  textBuf = C2D_TextBufNew(4096);

  // Main loop
  while (aptMainLoop()) {
    /* gspWaitForVBlank(); */
    /* gfxSwapBuffers(); */
    hidScanInput();

    // Your code goes here
    u32 kDown = hidKeysDown();
    if (kDown & KEY_START)
      break; // break in order to return to hbmenu

    mainUpdate();

    float slider = osGet3DSliderState();
    float iod = slider / 3;

    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

    C3D_RenderTargetClear(topL, C3D_CLEAR_ALL, 0x68b0d8ff, 0);
    C3D_FrameDrawOn(topL);
    C2D_SceneTarget(topL);
    mainDrawTop(-iod);

    if (iod > 0.0f) {
      C3D_RenderTargetClear(topR, C3D_CLEAR_ALL, 0x68b0d8ff, 0);
      C3D_FrameDrawOn(topR);
      C2D_SceneTarget(topR);
      mainDrawTop(iod);
    }

    C3D_RenderTargetClear(bottom, C3D_CLEAR_ALL, 0x68b0d8ff, 0);
    C3D_FrameDrawOn(bottom);
    C2D_SceneTarget(bottom);
    mainDrawBottom();

    C2D_TextBufClear(textBuf);

    C3D_FrameEnd(0);
  }

  C2D_TextBufDelete(textBuf);

  C2D_Fini();
  C3D_Fini();
  gfxExit();
  return 0;
}
