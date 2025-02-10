#include <citro2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

void drawButton(float x, float y, float z, float w, float h, C2D_Text text, u32 clr)
{
	u32 clrButton = C2D_Color32(0x26, 0xa6, 0x9a, 0xff);
	C2D_DrawRectangle(x, y, z, w, h, clrButton, clrButton, clrButton, clrButton);
	C2D_DrawText(&text, C2D_WithColor | C2D_AlignCenter, x + w / 2, y, z, 0.5f, 0.5, clr);
}

int main(int argc, char* argv[])
{
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	C2D_TextBuf textBuf = C2D_TextBufNew(4096);

	// Main loop
	while (aptMainLoop())
	{
		/* gspWaitForVBlank(); */
		/* gfxSwapBuffers(); */
		hidScanInput();

		// Your code goes here
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(bottom, C2D_Color32(0xc6, 0x28, 0x28, 0xff));
		C2D_SceneBegin(bottom);

		/* C2D_DrawRectangle(30, 0, 0, 50, 50, C2D_Color32(0x9a, 0x6c, 0xb9, 0xff), C2D_Color32(0xff, 0xff, 0x2c, 0xff), C2D_Color32(0xd8, 0xf6, 0x0f, 0xff), C2D_Color32(0x40, 0xea, 0x87, 0xff)); */
		/* C2D_DrawRectangle(320 / 2 - 80, 60, 0, 160, 30, clrButton, clrButton, clrButton, clrButton); */

		C2D_Text text;
		C2D_TextParse(&text, textBuf, "Open Save File");
		C2D_TextOptimize(&text);
		/* C2D_DrawText(&text, C2D_WithColor | C2D_AlignCenter, 320 / 2, 60, 0, 0.5f, 0.5f, C2D_Color32(0xff, 0xff, 0xff, 0xff)); */

		drawButton(320 / 2 - 80, 60, 0, 160, 30, text, C2D_Color32(0xff, 0xff, 0xff, 0xff));

		C2D_TextParse(&text, textBuf, "DoujinSoft");
		C2D_TextOptimize(&text);
		drawButton(320 / 2 - 80, 120, 0, 160, 30, text, C2D_Color32(0xff, 0xff, 0xff, 0xff));

		C2D_TextBufClear(textBuf);
		C3D_FrameEnd(0);
	}

	C2D_TextBufDelete(textBuf);
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}
