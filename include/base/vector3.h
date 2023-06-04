#ifndef _WGEO_CORE_VECTOR3_
#define _WGEO_CORE_VECTOR3_

#include <math.h>
#include "tolerance.h"

class Vector3 {
public:
    double X;
    double Y;
    double Z;
public:
    Vector3();
    Vector3(double x, double y, double z);
    double Dot(const Vector3& other) const;
    Vector3 Cross(const Vector3& other) const;
    double Length() const;
    Vector3 Normalize() const;
    Vector3 Normalize(double& length) const;
};

inline Vector3 operator+(const Vector3& vt0, const Vector3& vt1) {
    return Vector3(vt0.X + vt1.X, vt0.Y + vt1.Y, vt0.Z + vt1.Z);
}

inline Vector3 operator-(const Vector3& vt) {
    return Vector3(-vt.X, -vt.Y, -vt.Z);
}

inline Vector3 operator-(const Vector3& vt0, const Vector3& vt1) {
    return Vector3(vt0.X - vt1.X, vt0.Y - vt1.Y, vt0.Z - vt1.Z);
}

inline Vector3 operator*(const Vector3& vt, double d) {
    return Vector3(vt.X * d, vt.Y * d, vt.Z * d);
}

inline Vector3 operator*(double d, const Vector3& vt) {
    return Vector3(vt.X * d, vt.Y * d, vt.Z * d);
}

inline Vector3 operator/(const Vector3& vt, double d) {
    return Vector3(vt.X / d, vt.Y / d, vt.Z / d);
}

inline Vector3::Vector3() {
    X = 0;
    Y = 0;
    Z = 0;
}

inline Vector3::Vector3(double x, double y, double z) {
    X = x;
    Y = y;
    Z = z;
}

inline double Vector3::Dot(const Vector3& other) const {
    return X * other.X + Y * other.Y + Z * other.Z;
}

inline Vector3 Vector3::Cross(const Vector3& other) const {
    return Vector3(
        Y * other.Z - Z * other.Y,
        Z * other.X - X * other.Z,
        X * other.Y - Y * other.X
    );
}

inline double Vector3::Length() const {
    return sqrt(this->Dot(*this));
}

inline Vector3 Vector3::Normalize() const {
    double length;
    return Normalize(length);
}

inline Vector3 Vector3::Normalize(double& length) const {
    length = Length();
    if (length <= DOUBLE_EPSILON) {
        return Vector3(0, 0, 0);
    }
    return Vector3(X / length, Y / length, Z / length);
}

#endif