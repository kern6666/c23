#ifndef UTIL_H
#define UTIL_H
    #ifdef DEBUG
        #include <stdio.h>
        #define LOGD(...) fprintf(stdout, __VA_ARGS__)
        #define LOGE(...) fprintf(stderr, __VA_ARGS__)
    #else
        #define LOGD(...)
        #define LOGE(...)
    #endif
#endif // UTIL_H

