#ifndef _WGEO_CORE_TOLERANCE_
#define _WGEO_CORE_TOLERANCE_

#include "common.h"
#include <math.h>

#define DOUBLE_EPSILON 1E-12
extern double DISTANCE_EPSILON;

inline double acos_safe(double c) {
    if (c >= 1) {
        return 0;
    }
    if (c <= -1) {
        return PI;
    }
    return acos(c);
}

#endif
