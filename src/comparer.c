/*
 * Task #4
 *
 * Azim Muradov, group #171
 */

#include "bmpl.h"

#include <inttypes.h>

static const char *const TASK_4_ARGS_RF_MSG = "\"./comparer <INPUT1.BMP> <INPUT2.BMP>\"";

int runMineComparer(char *in1, char *in2) {
    #define THROWING_OP(op) if (op) return bmplLastErr.type

    Bmp *bmp1, *bmp2;
    THROWING_OP(BMPL_newBmp(&bmp1));
    THROWING_OP(bmp1->readFromFile(bmp1, in1));
    THROWING_OP(BMPL_newBmp(&bmp2));
    THROWING_OP(bmp1->readFromFile(bmp2, in2));

    DWord retVal;
    PxCoord diff[BMPL_DIFF_MAX_SIZE];
    THROWING_OP(BMPL_compareTwoBmp(bmp1, bmp2, &retVal, diff));

    for (DWord i = 0; i < retVal; ++i) {
        fprintf(stderr, "%"PRIu32", %"PRIu32"\n", diff[i].x, diff[i].y);
    }

    THROWING_OP(BMPL_freeBmp(&bmp1));
    THROWING_OP(BMPL_freeBmp(&bmp2));

    return retVal;

    #undef THROWING_OP
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Wrong arguments number, the format must be:\n%s", TASK_4_ARGS_RF_MSG);
        return BMPL_ET_G;
    }

    char *in1 = argv[1];
    char *in2 = argv[2];

    return runMineComparer(in1, in2);
}
