/*
 * gfx_demo.c -- PicoC Real RGB565 Pixel Graphics & Hardware Key Demo
 * Run inside Utilities.g3a -> File Manager -> select gfx_demo.c -> EXE
 *
 * Controls:
 *   Arrows (including diagonals!) : Move cursor smoothly
 *   EXE (hold)                    : Paint glowing circles on canvas
 *   F1..F5                        : Change brush color
 *   F6                            : Redraw gradient background
 *   EXIT                          : Quit back to Utilities
 */
#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/system.h>
#include <utilities/graphicsProvider.h>

int key_down(int code) {
    unsigned short *kreg = (unsigned short *)0xA44B0000;
    int row = code % 10;
    int col = code / 10 - 1;
    int word = row >> 1;
    int bit = col + ((row & 1) << 3);
    return (kreg[word] & (1 << bit)) != 0;
}

void draw_backdrop(unsigned short *vram) {
    int x;
    int y;
    for (y = 0; y < 198; y++) {
        int r = (y * 12) / 198;
        for (x = 0; x < 384; x++) {
            int g = (x * 20) / 384;
            int b = 8 + ((x + y) * 20) / 582;
            vram[y * 384 + x] = (r << 11) | (g << 5) | b;
        }
    }
    drawRectangle(0, 198, 384, 18, 0x0000);
    multiPrintMini(6, 175, "Arrows:Move  EXE:Paint  F1-F5:Color  F6:Clear  EXIT:Quit", 0xFFFF);
}

int main() {
    unsigned short *vram = (unsigned short *)GetVRAMAddress();
    unsigned short palette[5];
    int cx = 192;
    int cy = 100;
    int cidx = 0;

    palette[0] = 0xFFE0; /* Yellow */
    palette[1] = 0x07FF; /* Cyan   */
    palette[2] = 0xF81F; /* Magenta*/
    palette[3] = 0x07E0; /* Green  */
    palette[4] = 0xFFFF; /* White  */

    Bdisp_EnableColor(1);
    EnableStatusArea(3);
    draw_backdrop(vram);

    /* Wait until launching EXE key is released */
    while (key_down(31)) {
        OS_InnerWait_ms(10);
    }

    while (!key_down(47)) { /* 47 = EXIT */
        if (key_down(38)) cx -= 3; /* LEFT  */
        if (key_down(27)) cx += 3; /* RIGHT */
        if (key_down(28)) cy -= 3; /* UP    */
        if (key_down(37)) cy += 3; /* DOWN  */

        if (cx < 6) cx = 6;
        if (cx > 377) cx = 377;
        if (cy < 6) cy = 6;
        if (cy > 190) cy = 190;

        if (key_down(79)) cidx = 0; /* F1 */
        if (key_down(69)) cidx = 1; /* F2 */
        if (key_down(59)) cidx = 2; /* F3 */
        if (key_down(49)) cidx = 3; /* F4 */
        if (key_down(39)) cidx = 4; /* F5 */
        if (key_down(29)) draw_backdrop(vram); /* F6 */

        if (key_down(31)) { /* EXE = paint */
            drawFilledCircle(cx, cy, 5, palette[cidx]);
        } else {
            vram[cy * 384 + cx] = palette[cidx];
        }

        /* Show active color swatch in bottom-right corner */
        drawRectangle(366, 200, 14, 14, palette[cidx]);

        Bdisp_PutDisp_DD();
        OS_InnerWait_ms(12);
    }

    EnableStatusArea(0);
    return 0;
}

main();
