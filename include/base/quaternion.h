#ifndef _WGEO_CORE_QUATERNION_
#define _WGEO_CORE_QUATERNION_

#include "common.h"
#include "vector3.h"
#include "interval3.h"
#include "matrix.h"

class Quaternion {
public:
    double X;
    double Y;
    double Z;
    double W;
public:
    Quaternion();
    Quaternion(double x, double y, double z, double w);
    Quaternion Inverse() const;
    Vector3 ToEuler();
    Matrix3x3 ToMatrix3x3();
public:
    static Quaternion FromAxisAngle(const Vector3& axis, double angle);
    static Quaternion FromAxis(const Vector3& axis_x, const Vector3& axis_y);
    static Quaternion FromEuler(const Vector3& vt);
    static Quaternion FromMatrix3x3(const Matrix3x3& matrix);
};

inline Quaternion operator*(const Quaternion& q0, const Quaternion& q1) {
    return Quaternion(
		q0.X * q1.W + q0.Y * q1.Z - q0.Z * q1.Y + q0.W * q1.X,
		-q0.X * q1.Z + q0.Y * q1.W + q0.Z * q1.X + q0.W * q1.Y,
		q0.X * q1.Y - q0.Y * q1.X + q0.Z * q1.W + q0.W * q1.Z,
		-q0.X * q1.X - q0.Y * q1.Y - q0.Z * q1.Z + q0.W * q1.W
    );
}

inline Vector3 operator*(const Quaternion& q, const Vector3& vt) {
    double xx = q.X * q.X;
	double yy = q.Y * q.Y;
	double zz = q.Z * q.Z;
	double ww = q.W * q.W;
	double wx = q.W * q.X;
	double wy = q.W * q.Y;
	double wz = q.W * q.Z;
	double xy = q.X * q.Y;
	double xz = q.X * q.Z;
	double yz = q.Y * q.Z;
	return Vector3(
		(ww + xx - yy - zz) * vt.X + 2 * ((xy - wz) * vt.Y + (xz + wy) * vt.Z),
		(ww - xx + yy - zz) * vt.Y + 2 * ((xy + wz) * vt.X + (yz - wx) * vt.Z),
		(ww - xx - yy + zz) * vt.Z + 2 * ((xz - wy) * vt.X + (yz + wx) * vt.Y)
    );
}

inline Interval3 operator*(const Quaternion& q, const Interval3& vt) {
    double xx = q.X * q.X;
	double yy = q.Y * q.Y;
	double zz = q.Z * q.Z;
	double ww = q.W * q.W;
	double wx = q.W * q.X;
	double wy = q.W * q.Y;
	double wz = q.W * q.Z;
	double xy = q.X * q.Y;
	double xz = q.X * q.Z;
	double yz = q.Y * q.Z;
	return Interval3(
		(ww + xx - yy - zz) * vt.X + 2 * ((xy - wz) * vt.Y + (xz + wy) * vt.Z),
		(ww - xx + yy - zz) * vt.Y + 2 * ((xy + wz) * vt.X + (yz - wx) * vt.Z),
		(ww - xx - yy + zz) * vt.Z + 2 * ((xz - wy) * vt.X + (yz + wx) * vt.Y)
    );
}

inline Quaternion::Quaternion() {
    X = 0;
    Y = 0;
    Z = 0;
    W = 1;
}

inline Quaternion::Quaternion(double x, double y, double z, double w) {
    X = x;
    Y = y;
    Z = z;
    W = w;
}

inline Quaternion Quaternion::Inverse() const {
    return Quaternion(-X, -Y, -Z, W);
}

#endif