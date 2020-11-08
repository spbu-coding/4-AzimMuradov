/*
 * Task #4
 *
 * Azim Muradov, group #171
 */

#ifndef TASK_4_BMPL_BMP_H
#define TASK_4_BMPL_BMP_H

#include "bmpl_config.h"
#include "bmpl_def.h"
#include "bmpl_err.h"


/*------------------------------------------------- Global constants -------------------------------------------------*/

static const DWord BMPL_BMP_FILE_HEADER_SIZE = 14;

static const DWord BMPL_BMP_INFO_HEADER_V3_SIZE = 40;

static const DWord BMPL_BMP_HEADER_V3_SIZE = 54;


#if defined(BMPL_OPT_2_SPECIFIC_DIFF_MAX_SIZE_FOR_COMPARER) & !defined(BMPL_OPTARG_2_DIFF_MAX_SIZE)
#error "You must define the <DIFF_MAX_SIZE> argument for the BMPL option 2 with macro BMPL_OPTARG_2_DIFF_MAX_SIZE!"
#elif !defined(BMPL_OPT_2_SPECIFIC_DIFF_MAX_SIZE_FOR_COMPARER) & defined(BMPL_OPTARG_2_DIFF_MAX_SIZE)
#error "You must define the BMPL option 2 with macro BMPL_OPT_2_SPECIFIC_DIFF_MAX_SIZE_FOR_COMPARER!"
#elif defined(BMPL_OPT_2_SPECIFIC_DIFF_MAX_SIZE_FOR_COMPARER) & defined(BMPL_OPTARG_2_DIFF_MAX_SIZE)
static const DWord BMPL_DIFF_MAX_SIZE = BMPL_OPTARG_2_DIFF_MAX_SIZE;
#else
static const DWord BMPL_DIFF_MAX_SIZE = 100;
#endif


/*---------------------------------------------- BMP & Interface Methods ---------------------------------------------*/

typedef struct bmp_t Bmp;

struct bmp_t {
    // PRIVATE DATA - READ ONLY - ANY ATTEMPT TO MODIFY IT WILL CAUSE UNDEFINED BEHAVIOR
    BmpV3 bmpV3;


    // Interface
    BmplErrType (*readFromFile)(Bmp *this, const char *filename);

    BmplErrType (*writeToFile)(Bmp *this, const char *filename);


    BmplErrType (*invertColors)(Bmp *this);
};


/*------------------------------------------------ Interface Functions -----------------------------------------------*/

BmplErrType BMPL_compareTwoBmp(Bmp *bmp1, Bmp *bmp2, DWord *retVal, PxCoord *diff);


/*------------------------------------------------- Memory management ------------------------------------------------*/

// On the heap
BmplErrType BMPL_newBmp(Bmp **bmpPtr);

BmplErrType BMPL_freeBmp(Bmp **bmpPtr);

// On the stack and the heap
BmplErrType BMPL_initBmp(Bmp *bmp);

BmplErrType BMPL_eraseBmp(Bmp *bmp);

#endif // TASK_4_BMPL_BMP_H

