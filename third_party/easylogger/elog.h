#ifndef __ELOG_H__
#define __ELOG_H__

#include <stdio.h>

#define ELOG_LVL_ASSERT  0
#define ELOG_LVL_ERROR   1
#define ELOG_LVL_WARN    2
#define ELOG_LVL_INFO    3
#define ELOG_LVL_DEBUG   4
#define ELOG_LVL_VERBOSE 5

#define log_a(...) printf("[ASSERT] " __VA_ARGS__)
#define log_e(...) printf("[ERROR]  " __VA_ARGS__)
#define log_w(...) printf("[WARN]   " __VA_ARGS__)
#define log_i(...) printf("[INFO]   " __VA_ARGS__)
#define log_d(...) printf("[DEBUG]  " __VA_ARGS__)
#define log_v(...) printf("[VERB]   " __VA_ARGS__)

#endif
