#ifndef _WGEO_CORE_INTERVAL3_
#define _WGEO_CORE_INTERVAL3_

#include "interval.h"

class Interval3 {
public:
    Interval X;
    Interval Y;
    Interval Z;
public:
    Interval3();
    Interval3(Interval x, Interval y, Interval z);
    Interval Length() const;
    Interval3 Normalize() const;
    Interval3 Normalize(Interval& length) const;
};

inline Interval3::Interval3() {
    X = Interval();
    Y = Interval();
    Z = Interval();
}

inline Interval3::Interval3(Interval x, Interval y, Interval z) {
    X = x;
    Y = y;
    Z = z;
}

inline Interval Interval3::Length() const {
    return sqrt(X * X + Y * Y + Z * Z);
}

inline Interval3 Interval3::Normalize() const {
    Interval length;
    return Normalize(length);
}

inline Interval3 Interval3::Normalize(Interval& length) const {
    length = Length();
    if (length.IsIntersected(0, DOUBLE_EPSILON)) {
        return Interval3(Interval(-1, 1), Interval(-1, 1), Interval(-1, 1));
    }
    return Interval3(X / length, Y / length, Z / length);
}

#endif