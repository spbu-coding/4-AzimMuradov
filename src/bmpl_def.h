/*
 * Task #4
 *
 * Azim Muradov, group #171
 */

#ifndef TASK_4_BMPL_DEF_H
#define TASK_4_BMPL_DEF_H

#include <stdint.h>

/*----------------------------------------------------- TypeDefs -----------------------------------------------------*/

typedef uint8_t Byte;

typedef uint16_t Word;

typedef uint32_t DWord;

typedef int32_t Long;


/*---------------------------------------------------- File Header ---------------------------------------------------*/

/**
 * BMP File Header
 *
 * @param fileType     File type, always 4D42h ("BM").
 * @param fileSize     Size of the file in bytes.
 * @param reserved1    Always 0.
 * @param reserved2    Always 0.
 * @param bitmapOffset Starting position of image data in bytes.
 */
typedef struct {
    Word fileType;
    DWord fileSize;
    Word reserved1;
    Word reserved2;
    DWord bitmapOffset;
} BmpFileHeader;


/*---------------------------------------------------- Info Header ---------------------------------------------------*/

/**
 * BMP Info Header
 *
 * @param size            Size of this header in bytes.
 * @param width           Image width in pixels.
 * @param height          Image height in pixels.
 * @param planes          Number of color planes.
 * @param bitsPerPixel    Number of bits per pixel.
 * @param compression     Compression methods used.
 * @param sizeOfBitmap    Size of bitmap in bytes.
 * @param horzResolution  Horizontal resolution in pixels per meter.
 * @param vertResolution  Vertical resolution in pixels per meter.
 * @param colorsUsed      Number of colors in the image.
 * @param colorsImportant Minimum number of important colors.
 */
typedef struct {
    DWord size;
    Long width;
    Long height;
    Word planes;
    Word bitsPerPixel;
    DWord compression;
    DWord sizeOfBitmap;
    Long horzResolution;
    Long vertResolution;
    DWord colorsUsed;
    DWord colorsImportant;
} BmpInfoHeader;


/*------------------------------------------------------- Pixel ------------------------------------------------------*/

/**
 * Pixel Coordinate
 *
 * @param x X coordinate.
 * @param y Y coordinate.
 */
typedef struct {
    DWord x;
    DWord y;
} PxCoord;


/*--------------------------------------------------- Bmp Version 3 --------------------------------------------------*/

/**
 * BMP Version 3
 *
 * @param fh   File Header.
 * @param ih   Info Header.
 * @param pal  Color Palette.
 * @param data Bitmap Data.
 */
typedef struct {
    BmpFileHeader fh;
    BmpInfoHeader ih;
    Byte *pal;
    Byte *data;
} BmpV3;

#endif // TASK_4_BMPL_DEF_H
