/*
 * Task #4
 *
 * Azim Muradov, group #171
 */

#ifndef TASK_4_BMPL_ERR_H
#define TASK_4_BMPL_ERR_H

#include <stdbool.h>
#include <stdio.h>


/*------------------------------------------ BMPL error type and error code ------------------------------------------*/

typedef enum {
    BMPL_ET_OK = 0,
    BMPL_ET_NS = -1,
    BMPL_ET_WF = -2,
    BMPL_ET_G = -3,
    BMPL_ET_OTHER = -4,
} BmplErrType;

typedef enum {
    BMPL_E_OK,

    BMPL_E_NS_IH_S,
    BMPL_E_NS_IH_BPP,
    BMPL_E_NS_IH_C,
    BMPL_E_NS_OTHER,

    BMPL_E_WF_FH_FT,
    BMPL_E_WF_FH_FS,
    BMPL_E_WF_FH_R1,
    BMPL_E_WF_FH_R2,
    BMPL_E_WF_FH_BO,
    BMPL_E_WF_IH_S,
    BMPL_E_WF_IH_W,
    BMPL_E_WF_IH_P,
    BMPL_E_WF_IH_BPP,
    BMPL_E_WF_IH_C,
    BMPL_E_WF_IH_SOB_W_H_BPP,
    BMPL_E_WF_IH_SOB_BO_FS,
    BMPL_E_WF_IH_CU,
    BMPL_E_WF_IH_CI,
    BMPL_E_WF_PAL_RES,
    BMPL_E_WF_DATA_PAL_IND,
    BMPL_E_WF_OTHER,

    BMPL_E_G_MEM_ALLOC,
    BMPL_E_G_FOPEN,
    BMPL_E_G_FREAD_EOF,
    BMPL_E_G_FREAD_FERROR,
    BMPL_E_G_FWRITE,
    BMPL_E_G_NULL_BMP,
    BMPL_E_G_NULL_FILENAME,
    BMPL_E_G_NULL_ARGUMENT,
    BMPL_E_G_INCOMPARABLE_BMP_FILES,
    BMPL_E_G_OTHER,

    BMPL_E_OTHER,
} BmplErrCode;

BmplErrType BMPL_getErrType(BmplErrCode errCode);

static const char *bmplErrMessages[] = {
    "everything is ok",

    "unsupported BMP version, only BMP Version 3 is supported",
    "unsupported BMP depth, only 8 and 24 depths are supported",
    "compression is not supported",
    "not supported",

    "in file header - file type field must be equal to \"BM\"",
    "in file header - file size field must be equal to the true file size",
    "in file header - reserved 1 field must be equal to 0",
    "in file header - reserved 2 field must be equal to 0",
    "in file header - bitmap offset field must be more than or equal to BMPL_BMP_HEADER_V3_SIZE",
    "in info header - size field must be equal to BMPL_BMP_INFO_HEADER_V3_SIZE",
    "in info header - bitmap width field must be non-negative",
    "in info header - planes field must be equal to 1",
    "in info header - bits per pixel (depth) field must be equal to 8 or 24",
    "in info header - compression field must be equal to 0",
    "in info header - size of bitmap field must be equal to the size of bitmap calculated using the width and height of the bmp",
    "bitmap offset field from the file header + size of bitmap field from the info header must be equal to file size field from the file header",
    "in info header - colors used field must be less than or equal to 256 for 8 bit BMP and equal to 0 for 24 bit BMP",
    "in info header - colors important field must be less than or equal to colors used field",
    "in palette - every reserved value must be equal to 0",
    "in BMP data - wrong palette index, it must be less than the colors used in the palette",
    "wrong format",

    "memory allocation exception",
    "can't open the file",
    "can't read from the file, EOF occurred",
    "can't read from the file, error occurred",
    "can't write to the file, error occurred",
    "pointer to the BMP is equal to NULL, null pointer exception",
    "pointer to the filename is equal to NULL, null pointer exception",
    "function argument points to NULL, null pointer exception",
    "incomparable BMP files, they must be of the same dimensions",
    "some general error occurred",

    "something went wrong",
};


/*-------------------------------------------------- BMPL Last Error -------------------------------------------------*/


typedef struct {
    BmplErrCode code;
    BmplErrType type;
    const char *funcName;
} BmplErr;

extern BmplErr bmplLastErr;


/*------------------------------------------ Drop, set, and print Last Error -----------------------------------------*/

void BMPL_dropLastErr(void);

BmplErrType BMPL_setErr(BmplErrCode errCode, const char *funcName);

BmplErrType BMPL_setErrIfOrDrop(bool isErr, BmplErrCode errCode, const char *funcName);

void BMPL_printLastErr(FILE *errStream);

#endif // TASK_4_BMPL_ERR_H
