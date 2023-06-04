#ifndef _WGEO_CORE_CURVE3D_
#define _WGEO_CORE_CURVE3D_

#include "var_interval.h"
#include "vector3.h"
#include "interval3.h"

class Curve3d {
public:
    Curve3d(VarInterval* t_interval);
    virtual ~Curve3d();
    const VarInterval* TInterval() const;
    virtual void Calculate(double t, bool prev, Vector3* d0, Vector3* dt1, Vector3* dt2) const = 0;
    virtual Vector3 CalculateTangent(double t, bool prev) const;
    virtual void CalculateInterval(Interval t_interval, Interval3* d0, Interval3* dt1, Interval3* dt2) const = 0;
    virtual Interval3 CalculateTangentInterval(Interval t_interval) const;
    virtual void SubCurves(VarInterval** t_intervals, Curve3d** sub_curves, int count) = 0;
protected:
    VarInterval* m_t_interval;    
};

inline Curve3d::Curve3d(VarInterval* t_interval) {
    m_t_interval = t_interval;
}

inline Curve3d::~Curve3d() {
    delete m_t_interval;
}

inline const VarInterval* Curve3d::TInterval() const {
    return m_t_interval;
}
    

#endif