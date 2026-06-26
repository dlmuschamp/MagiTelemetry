/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --stride 1 --align 1 --font
 * 7segment.ttf --symbols
 * 0123456789:abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ<>?,./:";'{}|[]\`~!@#$%^&*()_=1234567890-=
 * --format lvgl -o seven_segment_font.c
 ******************************************************************************/
#include "lvgl/lvgl.h"

#ifndef SEVEN_SEGMENT_FONT
#define SEVEN_SEGMENT_FONT 1
#endif

#if SEVEN_SEGMENT_FONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0022 "\"" */
    0x6, 0x18, 0x61, 0x84, 0x10,

    /* U+0027 "'" */
    0x78,

    /* U+0028 "(" */
    0x79, 0x4, 0x10, 0x40, 0x8, 0x20, 0x82, 0x8, 0x3e,

    /* U+0029 ")" */
    0x7c, 0x10, 0x41, 0x4, 0x10, 0x2, 0x8, 0x20, 0xbc,

    /* U+002C "," */
    0xfc,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0x80,

    /* U+0030 "0" */
    0x7d, 0x14, 0x51, 0x44, 0x18, 0x61, 0x86, 0x18, 0x7f,

    /* U+0031 "1" */
    0x55, 0x52, 0xa8,

    /* U+0032 "2" */
    0x7c, 0x10, 0x41, 0x7, 0xe8, 0x20, 0x82, 0x8, 0x1c,

    /* U+0033 "3" */
    0x7c, 0x10, 0x41, 0x7, 0xe0, 0x82, 0x8, 0x20, 0xbc,

    /* U+0034 "4" */
    0x6, 0x18, 0x61, 0x87, 0xf0, 0x41, 0x4, 0x10, 0x40,

    /* U+0035 "5" */
    0x7a, 0x8, 0x20, 0x83, 0xf0, 0x41, 0x4, 0x10, 0x7f,

    /* U+0036 "6" */
    0x79, 0x4, 0x10, 0x41, 0xf8, 0x61, 0x86, 0x18, 0x7f,

    /* U+0037 "7" */
    0x7c, 0x10, 0x41, 0x4, 0x0, 0x82, 0x8, 0x20, 0x80,

    /* U+0038 "8" */
    0x7d, 0x14, 0x51, 0x45, 0xf8, 0x61, 0x86, 0x18, 0x7f,

    /* U+0039 "9" */
    0x7e, 0x18, 0x61, 0x87, 0xf0, 0x41, 0x4, 0x10, 0x7f,

    /* U+003A ":" */
    0x40, 0x8,

    /* U+003D "=" */
    0x78, 0x0, 0x0, 0x1, 0xc0,

    /* U+003F "?" */
    0x7c, 0x10, 0x41, 0x7, 0xe8, 0x20, 0x82, 0x0, 0x0,

    /* U+0041 "A" */
    0x7d, 0x14, 0x51, 0x45, 0xf8, 0x61, 0x86, 0x18, 0x40,

    /* U+0042 "B" */
    0x7d, 0x14, 0x51, 0x45, 0xf8, 0x61, 0x86, 0x18, 0x7f,

    /* U+0043 "C" */
    0x79, 0x4, 0x10, 0x40, 0x8, 0x20, 0x82, 0x8, 0x3e,

    /* U+0044 "D" */
    0x7d, 0x14, 0x51, 0x44, 0x18, 0x61, 0x86, 0x18, 0x7f,

    /* U+0045 "E" */
    0x79, 0x4, 0x10, 0x41, 0xf8, 0x20, 0x82, 0x8, 0x3e,

    /* U+0046 "F" */
    0x79, 0x4, 0x10, 0x41, 0xf8, 0x20, 0x82, 0x8, 0x0,

    /* U+0047 "G" */
    0x79, 0x4, 0x10, 0x40, 0x8, 0x21, 0x86, 0x18, 0x7f,

    /* U+0048 "H" */
    0x5, 0x14, 0x51, 0x45, 0xf8, 0x61, 0x86, 0x18, 0x40,

    /* U+0049 "I" */
    0x55, 0x52, 0xa8,

    /* U+004A "J" */
    0x4, 0x10, 0x41, 0x4, 0x8, 0x61, 0x86, 0x17, 0xc0,

    /* U+004B "K" */
    0x5, 0x14, 0x51, 0x45, 0xe8, 0x20, 0x82, 0x8, 0x3e,

    /* U+004C "L" */
    0x2, 0x10, 0x84, 0x2, 0x10, 0x84, 0x3e,

    /* U+004D "M" */
    0x78, 0x0, 0x0, 0x3, 0xf8, 0x61, 0x86, 0x10, 0x40,

    /* U+004E "N" */
    0x7d, 0x14, 0x51, 0x44, 0x8, 0x61, 0x86, 0x18, 0x40,

    /* U+004F "O" */
    0x7d, 0x14, 0x51, 0x44, 0x18, 0x61, 0x86, 0x18, 0x7f,

    /* U+0050 "P" */
    0x7d, 0x14, 0x51, 0x45, 0xe8, 0x20, 0x82, 0x8, 0x0,

    /* U+0051 "Q" */
    0x7e, 0x18, 0x61, 0x87, 0xe0, 0x0, 0x0, 0x0, 0x3c,

    /* U+0052 "R" */
    0x79, 0x4, 0x10, 0x40, 0x8, 0x20, 0x82, 0x8, 0x0,

    /* U+0053 "S" */
    0x7a, 0x8, 0x20, 0x83, 0xf0, 0x41, 0x4, 0x10, 0x7f,

    /* U+0054 "T" */
    0x7c, 0x10, 0x41, 0x4, 0x0, 0x82, 0x8, 0x20, 0x80,

    /* U+0055 "U" */
    0x5, 0x14, 0x51, 0x44, 0x8, 0x61, 0x86, 0x1f, 0xc0,

    /* U+0056 "V" */
    0x86, 0x18, 0x61, 0x84, 0x0, 0x0, 0x0, 0xf, 0x0,

    /* U+0057 "W" */
    0x5, 0x14, 0x51, 0x45, 0xf8, 0x61, 0x86, 0x18, 0x7f,

    /* U+0058 "X" */
    0x78, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0xe0,

    /* U+0059 "Y" */
    0x6, 0x18, 0x61, 0x87, 0xf0, 0x41, 0x4, 0x10, 0x7f,

    /* U+005A "Z" */
    0x7c, 0x10, 0x41, 0x7, 0xe8, 0x20, 0x82, 0x8, 0x1c,

    /* U+005B "[" */
    0x79, 0x4, 0x10, 0x40, 0x8, 0x20, 0x82, 0x8, 0x3e,

    /* U+005D "]" */
    0x7c, 0x10, 0x41, 0x4, 0x10, 0x2, 0x8, 0x20, 0xbc,

    /* U+005F "_" */
    0x70,

    /* U+0060 "`" */
    0x78,

    /* U+0061 "a" */
    0x7c, 0x10, 0x41, 0x7, 0xf8, 0x61, 0x86, 0x18, 0x5f,

    /* U+0062 "b" */
    0x1, 0x4, 0x10, 0x41, 0xf8, 0x61, 0x86, 0x18, 0x7f,

    /* U+0063 "c" */
    0xfc, 0x21, 0x8, 0x41, 0xc0,

    /* U+0064 "d" */
    0x4, 0x10, 0x41, 0x7, 0xf8, 0x61, 0x86, 0x18, 0x5f,

    /* U+0065 "e" */
    0x7d, 0x14, 0x51, 0x45, 0xe8, 0x20, 0x82, 0x8, 0x3e,

    /* U+0066 "f" */
    0x79, 0x4, 0x10, 0x41, 0xf8, 0x20, 0x82, 0x8, 0x0,

    /* U+0067 "g" */
    0x7e, 0x18, 0x61, 0x87, 0xf0, 0x41, 0x4, 0x10, 0x7f,

    /* U+0068 "h" */
    0x1, 0x4, 0x10, 0x41, 0xf8, 0x61, 0x86, 0x18, 0x40,

    /* U+0069 "i" */
    0xfc,

    /* U+006A "j" */
    0x4, 0x10, 0x41, 0x4, 0x0, 0x82, 0x8, 0x2f, 0x0,

    /* U+006B "k" */
    0x79, 0x4, 0x10, 0x41, 0xf8, 0x61, 0x86, 0x18, 0x40,

    /* U+006C "l" */
    0x2, 0x10, 0x84, 0x2, 0x10, 0x84, 0x3e,

    /* U+006D "m" */
    0x78, 0x0, 0x0, 0x3, 0xf8, 0x61, 0x86, 0x10, 0x40,

    /* U+006E "n" */
    0xfe, 0x18, 0x61, 0x84, 0x10,

    /* U+006F "o" */
    0xfe, 0x18, 0x61, 0x86, 0x17, 0xc0,

    /* U+0070 "p" */
    0x7d, 0x14, 0x51, 0x45, 0xe8, 0x20, 0x82, 0x8, 0x0,

    /* U+0071 "q" */
    0x7e, 0x18, 0x61, 0x87, 0xf0, 0x41, 0x4, 0x10, 0x40,

    /* U+0072 "r" */
    0xfc, 0x21, 0x8, 0x0,

    /* U+0073 "s" */
    0x2, 0x8, 0x20, 0x83, 0xf0, 0x41, 0x4, 0x10, 0x40,

    /* U+0074 "t" */
    0x1, 0x4, 0x10, 0x41, 0xf8, 0x20, 0x82, 0x8, 0x3e,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x7c,

    /* U+0076 "v" */
    0x86, 0x18, 0x61, 0x84, 0x0, 0x0, 0x0, 0xf, 0x0,

    /* U+0077 "w" */
    0x5, 0x14, 0x51, 0x45, 0xf8, 0x61, 0x86, 0x18, 0x7f,

    /* U+0078 "x" */
    0x78, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0xe0,

    /* U+0079 "y" */
    0x6, 0x18, 0x61, 0x87, 0xf0, 0x41, 0x4, 0x10, 0x7f,

    /* U+007A "z" */
    0x7c, 0x10, 0x41, 0x7, 0xe8, 0x20, 0x82, 0x8, 0x1c,

    /* U+007C "|" */
    0x15, 0x4a, 0xa8};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0,
     .adv_w = 0,
     .box_w = 0,
     .box_h = 0,
     .ofs_x = 0,
     .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 6,
     .ofs_x = 1,
     .ofs_y = 6},
    {.bitmap_index = 5,
     .adv_w = 120,
     .box_w = 1,
     .box_h = 6,
     .ofs_x = 1,
     .ofs_y = 6},
    {.bitmap_index = 6,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 15,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 24,
     .adv_w = 120,
     .box_w = 1,
     .box_h = 6,
     .ofs_x = 6,
     .ofs_y = 0},
    {.bitmap_index = 25,
     .adv_w = 120,
     .box_w = 4,
     .box_h = 1,
     .ofs_x = 2,
     .ofs_y = 6},
    {.bitmap_index = 26,
     .adv_w = 0,
     .box_w = 1,
     .box_h = 1,
     .ofs_x = 0,
     .ofs_y = 0},
    {.bitmap_index = 27,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 36,
     .adv_w = 120,
     .box_w = 2,
     .box_h = 12,
     .ofs_x = 6,
     .ofs_y = 0},
    {.bitmap_index = 39,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 48,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 57,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 66,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 75,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 84,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 93,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 102,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 111,
     .adv_w = 45,
     .box_w = 2,
     .box_h = 7,
     .ofs_x = 1,
     .ofs_y = 3},
    {.bitmap_index = 113,
     .adv_w = 120,
     .box_w = 5,
     .box_h = 7,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 118,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 127,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 136,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 145,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 154,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 163,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 172,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 181,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 190,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 199,
     .adv_w = 120,
     .box_w = 2,
     .box_h = 12,
     .ofs_x = 6,
     .ofs_y = 0},
    {.bitmap_index = 202,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 211,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 220,
     .adv_w = 120,
     .box_w = 5,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 227,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 236,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 245,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 254,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 263,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 272,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 281,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 290,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 299,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 308,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 317,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 326,
     .adv_w = 120,
     .box_w = 5,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 334,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 343,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 352,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 361,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 370,
     .adv_w = 120,
     .box_w = 5,
     .box_h = 1,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 371,
     .adv_w = 120,
     .box_w = 1,
     .box_h = 6,
     .ofs_x = 1,
     .ofs_y = 6},
    {.bitmap_index = 372,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 381,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 390,
     .adv_w = 120,
     .box_w = 5,
     .box_h = 7,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 395,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 404,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 413,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 422,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 431,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 440,
     .adv_w = 120,
     .box_w = 1,
     .box_h = 6,
     .ofs_x = 6,
     .ofs_y = 0},
    {.bitmap_index = 441,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 2,
     .ofs_y = 0},
    {.bitmap_index = 450,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 459,
     .adv_w = 120,
     .box_w = 5,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 466,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 475,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 6,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 480,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 7,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 486,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 495,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 504,
     .adv_w = 120,
     .box_w = 5,
     .box_h = 6,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 508,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1},
    {.bitmap_index = 517,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 526,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 5,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 530,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 539,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 548,
     .adv_w = 120,
     .box_w = 5,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 556,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 565,
     .adv_w = 120,
     .box_w = 6,
     .box_h = 12,
     .ofs_x = 1,
     .ofs_y = 0},
    {.bitmap_index = 574,
     .adv_w = 120,
     .box_w = 2,
     .box_h = 11,
     .ofs_x = 1,
     .ofs_y = 1}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0,  0,  0,  0,  0,  1,  2,  3,  0,  0,  4,  5,  6,  0,  7,  8,  9,  10, 11,
    12, 13, 14, 15, 16, 17, 0,  0,  18, 0,  19, 0,  20, 21, 22, 23, 24, 25, 26,
    27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
    46, 0,  47, 0,  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
    63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 0,  76};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {.range_start = 34,
     .range_length = 91,
     .glyph_id_start = 1,
     .unicode_list = NULL,
     .glyph_id_ofs_list = glyph_id_ofs_list_0,
     .list_length = 91,
     .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL}};

/*-----------------
 *    KERNING
 *----------------*/

/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] = {7, 7};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] = {30};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 1,
    .glyph_ids_size = 0};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t seven_segment_font = {
#else
lv_font_t seven_segment_font = {
#endif
    .get_glyph_dsc =
        lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap =
        lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 12, /*The maximum line height required by the font*/
    .base_line = 0,    /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc, /*The custom font data. Will be accessed by
                         `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL, // normally montserrat but removing it
#endif
    .user_data = NULL,
};

#endif /*#if SEVEN_SEGMENT_FONT*/
