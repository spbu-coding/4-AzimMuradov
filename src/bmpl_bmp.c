/*
 * Task #4
 *
 * Azim Muradov, group #171
 */

#include "bmpl_bmp.h"
#include "bmpl_bmp_private_functions_impl"

#include <string.h>


/*-------------------------------------------------- Compare two BMP -------------------------------------------------*/

static bool BMPL_isByteBuffersEqual(const Byte *buf1, const Byte *buf2, size_t bufLength) {
    for (size_t i = 0; i < bufLength; ++i) if (buf1[i] != buf2[i]) return false;
    return true;
}

BmplErrType BMPL_compareTwoBmp(Bmp *bmp1, Bmp *bmp2, DWord *retVal, PxCoord *diff) {
    BMPL_dropLastErr();

    if (bmp1 == NULL or bmp2 == NULL) return BMPL_setErr(BMPL_E_G_NULL_BMP, __func__);
    if (retVal == NULL or diff == NULL) return BMPL_setErr(BMPL_E_G_NULL_ARGUMENT, __func__);


    DWord rv = 0; // Return value

    Long w1 = bmp1->bmpV3.ih.width, w2 = bmp2->bmpV3.ih.width;
    Long h1 = bmp1->bmpV3.ih.height, h2 = bmp2->bmpV3.ih.height;
    Long absH1 = llabs(h1), absH2 = llabs(h2);

    if (not(w1 == w2 and absH1 == absH2)) return BMPL_setErr(BMPL_E_G_INCOMPARABLE_BMP_FILES, __func__);


    Long w = w1, absH = absH1;

    Byte *pal1 = bmp1->bmpV3.pal, *pal2 = bmp2->bmpV3.pal;
    Byte *data1 = bmp1->bmpV3.data, *data2 = bmp2->bmpV3.data;

    // Bytes Per Pixel
    Word BPP1 = bmp1->bmpV3.ih.bitsPerPixel >> 3u;
    Word BPP2 = bmp2->bmpV3.ih.bitsPerPixel >> 3u;

    // Number of bytes in one line
    Long line1 = BPP1 * w + BPP1 * w % 4;
    Long line2 = BPP2 * w + BPP2 * w % 4;


    Long offset1, offset2;
    Byte *rgb1, *rgb2;
    for (Long y = 0; rv < BMPL_DIFF_MAX_SIZE and y < absH; ++y) {
        for (Long x = 0; rv < BMPL_DIFF_MAX_SIZE and x < w; ++x) {
            offset1 = (h1 >= 0 ? y : absH - y - 1) * line1 + BPP1 * x;
            offset2 = (h2 >= 0 ? y : absH - y - 1) * line2 + BPP2 * x;

            rgb1 = BPP1 == 3 ? data1 + offset1 : pal1 + data1[offset1] * 4;
            rgb2 = BPP2 == 3 ? data2 + offset2 : pal2 + data2[offset2] * 4;

            if (!BMPL_isByteBuffersEqual(rgb1, rgb2, 3)) {
                diff[rv++] = (PxCoord) {x, y};
            }
        }
    }

    *retVal = rv;


    return BMPL_ET_OK;
}


/*--------------------------------------- Memory management for BMP on the heap --------------------------------------*/

BmplErrType BMPL_newBmp(Bmp **bmpPtr) {
    BMPL_dropLastErr();

    if (bmpPtr == NULL) return BMPL_setErr(BMPL_E_G_NULL_BMP, __func__);

    *bmpPtr = malloc(sizeof(Bmp));
    if (*bmpPtr == NULL) return BMPL_setErr(BMPL_E_G_MEM_ALLOC, __func__);

    return BMPL_initBmp(*bmpPtr);
}

BmplErrType BMPL_freeBmp(Bmp **bmpPtr) {
    BMPL_dropLastErr();

    if (bmpPtr == NULL) return BMPL_setErr(BMPL_E_G_NULL_BMP, __func__);

    if (BMPL_eraseBmp(*bmpPtr)) return bmplLastErr.type;

    free(*bmpPtr);
    *bmpPtr = NULL;

    return BMPL_ET_OK;
}


/*-------------------------------- Memory management for BMP on the stack and the heap -------------------------------*/

BmplErrType BMPL_initBmp(Bmp *bmp) {
    BMPL_dropLastErr();

    if (bmp == NULL) return BMPL_setErr(BMPL_E_G_NULL_BMP, __func__);

    // Nullify BmpV3
    memset(&bmp->bmpV3, 0, sizeof bmp->bmpV3);

    // Assign interface functions
    bmp->readFromFile = BMPL_readFromFile;
    bmp->writeToFile = BMPL_writeToFile;

    bmp->invertColors = BMPL_invertColors;

    return BMPL_ET_OK;
}

BmplErrType BMPL_eraseBmp(Bmp *bmp) {
    BMPL_dropLastErr();

    if (bmp == NULL) return BMPL_setErr(BMPL_E_G_NULL_BMP, __func__);

    free(bmp->bmpV3.data);
    free(bmp->bmpV3.pal);

    return BMPL_initBmp(bmp);
}
