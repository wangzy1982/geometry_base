#ifndef _WGEO_CORE_VECTOR2_
#define _WGEO_CORE_VECTOR2_

#include <math.h>
#include "tolerance.h"

class Vector2 {
public:
    double X;
    double Y;
public:
    Vector2();
    Vector2(double x, double y);
    double Dot(const Vector2& other) const;
    double Cross(const Vector2& other) const;
    double Length() const;
    Vector2 Normalize() const;
    Vector2 Normalize(double& length) const;
};

inline Vector2 operator+(const Vector2& vt0, const Vector2& vt1) {
    return Vector2(vt0.X + vt1.X, vt0.Y + vt1.Y);
}

inline Vector2 operator-(const Vector2& vt) {
    return Vector2(-vt.X, -vt.Y);
}

inline Vector2 operator-(const Vector2& vt0, const Vector2& vt1) {
    return Vector2(vt0.X - vt1.X, vt0.Y - vt1.Y);
}

inline Vector2 operator*(const Vector2& vt, double d) {
    return Vector2(vt.X * d, vt.Y * d);
}

inline Vector2 operator*(double d, const Vector2& vt) {
    return Vector2(vt.X * d, vt.Y * d);
}

inline Vector2 operator/(const Vector2& vt, double d) {
    return Vector2(vt.X / d, vt.Y / d);
}

inline Vector2::Vector2() {
    X = 0;
    Y = 0;
}

inline Vector2::Vector2(double x, double y) {
    X = x;
    Y = y;
}

inline double Vector2::Dot(const Vector2& other) const {
    return X * other.X + Y * other.Y;
}

inline double Vector2::Cross(const Vector2& other) const {
    return X * other.Y - Y * other.X;
}

inline double Vector2::Length() const {
    return sqrt(this->Dot(*this));
}

inline Vector2 Vector2::Normalize() const {
    double length;
    return Normalize(length);
}

inline Vector2 Vector2::Normalize(double& length) const {
    length = Length();
    if (length <= DOUBLE_EPSILON) {
        return Vector2(0, 0);
    }
    return Vector2(X / length, Y / length);
}

#endif

