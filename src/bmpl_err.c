/*
 * Task #4
 *
 * Azim Muradov, group #171
 */

#include "bmpl_config.h"
#include "bmpl_err.h"

#include <iso646.h>


/*------------------------------------------------ Get BMPL error type -----------------------------------------------*/

BmplErrType BMPL_getErrType(BmplErrCode errCode) {
    if (errCode == BMPL_E_OK) return BMPL_ET_OK;
    if (BMPL_E_OK < errCode and errCode <= BMPL_E_NS_OTHER) return BMPL_ET_NS;
    if (BMPL_E_NS_OTHER < errCode and errCode <= BMPL_E_WF_OTHER) return BMPL_ET_WF;
    if (BMPL_E_WF_OTHER < errCode and errCode <= BMPL_E_G_OTHER) return BMPL_ET_G;
    return BMPL_ET_OTHER;
}


/*-------------------------------------------------- BMPL Last Error -------------------------------------------------*/

#define BMPL_NO_ERR (BmplErr) {BMPL_E_OK, BMPL_ET_OK, NULL}

BmplErr bmplLastErr = BMPL_NO_ERR;


/*------------------------------------------ Drop, set, and print Last Error -----------------------------------------*/

void BMPL_dropLastErr(void) { bmplLastErr = BMPL_NO_ERR; }

BmplErrType BMPL_setErr(BmplErrCode errCode, const char *funcName) {
    bmplLastErr = (BmplErr) {errCode, BMPL_getErrType(errCode), funcName};

#if defined(BMPL_OPT_1_SET_ERR_WITH_PRINT) & !defined(BMPL_OPTARG_1_ERR_STREAM)
#error "You must define the <ERR_STREAM> argument for the BMPL option 1 with macro BMPL_OPTARG_1_ERR_STREAM!"
#elif !defined(BMPL_OPT_1_SET_ERR_WITH_PRINT) & defined(BMPL_OPTARG_1_ERR_STREAM)
#error "You must define the BMPL option 1 with macro BMPL_OPT_1_SET_ERR_WITH_PRINT!"
#elif defined(BMPL_OPT_1_SET_ERR_WITH_PRINT) & defined(BMPL_OPTARG_1_ERR_STREAM)
    BMPL_printLastErr(BMPL_OPTARG_1_ERR_STREAM);
#endif

    return bmplLastErr.type;
}

BmplErrType BMPL_setErrIfOrDrop(bool isErr, BmplErrCode errCode, const char *funcName) {
    BMPL_dropLastErr();
    return isErr ? BMPL_setErr(errCode, funcName) : BMPL_ET_OK;
}

void BMPL_printLastErr(FILE *errStream) {
    static const char *const MSG = "BMPL : error occurred : \"%s\" in function \"%s\"\n";
    fprintf(errStream, MSG, bmplErrMessages[bmplLastErr.code], bmplLastErr.funcName);
}


/*------------------------------------------------------ Undefs ------------------------------------------------------*/

#undef BMPL_NO_ERR
