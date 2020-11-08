/*
 * Task #4
 *
 * Azim Muradov, group #171
 */

#ifndef TASK_4_BMPL_CONFIG_H
#define TASK_4_BMPL_CONFIG_H

// Uncomment options to use them.

/** Option 1 - Automatically print error to the <ERR_STREAM> whenever BMPL_setErr(...) is called. */
// #define BMPL_OPT_1_SET_ERR_WITH_PRINT
// #define BMPL_OPTARG_1_ERR_STREAM <ERR_STREAM>

/** Option 2 - Specify BMPL_DIFF_MAX_SIZE for BMPL_compareTwoBmp(...) function. */
// #define BMPL_OPT_2_SPECIFIC_DIFF_MAX_SIZE_FOR_COMPARER
// #define BMPL_OPTARG_2_DIFF_MAX_SIZE <DIFF_MAX_SIZE>


#define BMPL_OPT_1_SET_ERR_WITH_PRINT
#define BMPL_OPTARG_1_ERR_STREAM stderr

#endif // TASK_4_BMPL_CONFIG_H
