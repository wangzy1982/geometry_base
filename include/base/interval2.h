#ifndef _WGEO_CORE_INTERVAL2_
#define _WGEO_CORE_INTERVAL2_

#include "interval.h"

class Interval2 {
public:
    Interval X;
    Interval Y;
public:
    Interval2();
    Interval2(Interval x, Interval y);
};

inline Interval2::Interval2() {
    X = Interval();
    Y = Interval();
}

inline Interval2::Interval2(Interval x, Interval y) {
    X = x;
    Y = y;
}

#endif