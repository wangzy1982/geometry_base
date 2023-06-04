#include "base/curve3d.h"

Vector3 Curve3d::CalculateTangent(double t, bool prev) const {
    Vector3 dt1;
    Calculate(t, prev, nullptr, &dt1, nullptr);
    return dt1.Normalize();
}

Interval3 Curve3d::CalculateTangentInterval(Interval t_interval) const {
    Interval3 dt1;
    CalculateInterval(t_interval, nullptr, &dt1, nullptr);
    return dt1.Normalize();
}