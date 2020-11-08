/*
 * Task #4
 *
 * Azim Muradov, group #171
 */

#include "bmpl.h"  // Mine
#include "qdbmp.h" // Theirs

#include <iso646.h>

static const char *const TASK_4_ARGS_RF_MSG = "\"./converter --mine <INPUT.BMP> <OUTPUT.BMP>\" or\n"
                                              "\"./converter --theirs <INPUT.BMP> <OUTPUT.BMP>\"";

BmplErrType runMineConverter(char *in, char *out) {
    #define THROWING_OP(op) if (op) return bmplLastErr.type

    Bmp *bmp;
    THROWING_OP(BMPL_newBmp(&bmp));
    THROWING_OP(bmp->readFromFile(bmp, in));

    THROWING_OP(bmp->invertColors(bmp));
    THROWING_OP(bmp->writeToFile(bmp, out));

    THROWING_OP(BMPL_freeBmp(&bmp));

    return BMPL_ET_OK;

    #undef THROWING_OP
}

BmplErrType covertQdbmpErrCode(BMP_STATUS errCode) {
    switch (errCode) {
        case BMP_OK:
            return BMPL_ET_OK;
        case BMP_FILE_NOT_SUPPORTED:
            return BMPL_ET_NS;
        case BMP_FILE_INVALID:
        case BMP_TYPE_MISMATCH:
            return BMPL_ET_WF;
        case BMP_ERROR:
        case BMP_OUT_OF_MEMORY:
        case BMP_IO_ERROR:
        case BMP_FILE_NOT_FOUND:
        case BMP_INVALID_ARGUMENT:
        default:
            return BMPL_ET_G;
    };
}

BmplErrType runTheirsConverter(char *in, char *out) {
    BMP *bmp = BMP_ReadFile(in);
    BMP_CHECK_ERROR(stderr, covertQdbmpErrCode(BMP_LAST_ERROR_CODE))

    INT w = BMP_GetWidth(bmp), h = BMP_GetHeight(bmp);
    USHORT depth = BMP_GetDepth(bmp);

    if (depth == 24) {
        UCHAR r, g, b;
        for (UINT x = 0; x < w; ++x) {
            for (UINT y = 0; y < h; ++y) {
                BMP_GetPixelRGB(bmp, x, y, &r, &g, &b);
                BMP_SetPixelRGB(bmp, x, y, compl r, compl g, compl b);
            }
        }
    } else if (depth == 8) {
        UCHAR r, g, b;
        UINT cu = bmp->Header.ColorsUsed;
        cu = cu == 0 ? 256 : cu;
        for (UINT i = 0; i < cu; ++i) {
            BMP_GetPaletteColor(bmp, i, &r, &g, &b);
            BMP_SetPaletteColor(bmp, i, compl r, compl g, compl b);
        }
    } else {
        return BMPL_ET_NS;
    }

    BMP_WriteFile(bmp, out);
    BMP_CHECK_ERROR(stderr, covertQdbmpErrCode(BMP_LAST_ERROR_CODE))

    BMP_Free(bmp);

    return BMPL_ET_OK;
}


int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Wrong arguments number, the format must be:\n%s", TASK_4_ARGS_RF_MSG);
        return BMPL_ET_G;
    }

    bool isMine = strcmp(argv[1], "--mine") == 0;
    bool isTheirs = strcmp(argv[1], "--theirs") == 0;
    if (not isMine and not isTheirs) {
        fprintf(stderr, "Wrong option, the format must be:\n%s", TASK_4_ARGS_RF_MSG);
        return BMPL_ET_G;
    }

    char *in = argv[2];
    char *out = argv[3];

    return (int) (isMine ? runMineConverter(in, out) : runTheirsConverter(in, out));
}
