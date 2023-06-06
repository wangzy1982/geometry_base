#ifndef _WGEO_CORE_VAR_INTERVAL_
#define _WGEO_CORE_VAR_INTERVAL_

#include <memory>
#include "interval.h"

class VarInterval {
public:
    VarInterval(int knot_count);
    VarInterval(const Interval& interval);
    VarInterval(VarInterval* interval);
    virtual ~VarInterval();
    int KnotCount() const;
    double GetKnot(int i) const;
    void SetKnot(int i, double d);
    double Min() const;
    double Max() const;
    Interval ToInterval() const;
    VarInterval* SubInterval(int start, int count) const;
private:
    double* m_knots;
    int m_knot_count;
};

inline VarInterval::VarInterval(int knot_count) {
    m_knot_count = knot_count;
    m_knots = new double[m_knot_count];
}

inline VarInterval::VarInterval(const Interval& interval) {
    m_knot_count = 2;
    m_knots = new double[2];
    m_knots[0] = interval.Min;
    m_knots[1] = interval.Max;
}

inline VarInterval::VarInterval(VarInterval* interval) {
    m_knot_count = interval->m_knot_count;
    m_knots = new double[m_knot_count];
    memcpy(m_knots, interval->m_knots, m_knot_count * sizeof(double));
}    

inline VarInterval::~VarInterval() {
    delete [] m_knots;
}

inline int VarInterval::KnotCount() const {
    return m_knot_count;
}

inline double VarInterval::GetKnot(int i) const {
    return m_knots[i];
}

inline void VarInterval::SetKnot(int i, double d) {
    m_knots[i] = d;
}

inline double VarInterval::Min() const {
    return m_knots[0];
}

inline double VarInterval::Max() const {
    return m_knots[m_knot_count - 1];
}

inline Interval VarInterval::ToInterval() const {
    return Interval(Min(), Max());
}

inline VarInterval* VarInterval::SubInterval(int start, int count) const {
    VarInterval* interval = new VarInterval(count);
    memcpy(interval->m_knots, m_knots + start, count * sizeof(double));
    return interval; 
}

#endif