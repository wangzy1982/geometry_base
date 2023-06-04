#include "base/quaternion.h"

//yaw(Z), pitch(Y), roll(X)
Vector3 Quaternion::ToEuler() {
    double sinr_cosp = 2 * (W * X + Y * Z);
    double cosr_cosp = 1 - 2 * (X * X + Y * Y);
    double roll = atan2(sinr_cosp, cosr_cosp);

    double sinp = 2 * (W * Y - Z * X);
    double pitch;
    if (sinp >= 1) {
        pitch = PI * 0.5;
    } else if (sinp <= -1) {
        pitch = -PI * 0.5;
    } else {
        pitch = asin(sinp);
    }

    double siny_cosp = 2 * (W * Z + X * Y);
    double cosy_cosp = 1 - 2 * (Y * Y + Z * Z);
    double yaw = atan2(siny_cosp, cosy_cosp);

    return Vector3(roll, pitch, yaw);
}

Matrix3x3 Quaternion::ToMatrix3x3() {
    return Matrix3x3(
        1 - 2 * Y * Y - 2 * Z * Z,
        2 * X * Y - 2 * W * Z,
        2 * X * Z + 2 * W * Y,
        2 * X * Y + 2 * W * Z,
        1 - 2 * X * X - 2 * Z * Z,
        2 * Y * Z - 2 * W * X,
        2 * X * Z - 2 * W * Y,
        2 * Y * Z + 2 * W * X,
        1 - 2 * X * X - 2 * Y * Y
    );
}

Quaternion Quaternion::FromAxisAngle(const Vector3& axis, double angle) {
    double a2 = angle * 0.5;
    double sin, cos;
    sincos(a2, &sin, &cos);
    return Quaternion(axis.X * sin, axis.Y * sin, axis.Z * sin, cos);
}

Quaternion Quaternion::FromAxis(const Vector3& axis_x, const Vector3& axis_y)  {
    Vector3 axis_x_2 = Vector3(1, 0, 0);
    Vector3 vt = axis_x_2.Cross(axis_x);
    double len;
    Vector3 axis = vt.Normalize(len);
    if (len < DOUBLE_EPSILON) {
        if (axis_x_2.Dot(axis_x) > 0) {
            Vector3 axis_y_2 = Vector3(0, 1, 0);
            double s = axis_y_2.Cross(axis_y).Dot(axis_x_2);
            double c = axis_y_2.Dot(axis_y);
            double angle = acos_safe(c);
            if (s < 0) {
                angle = -angle;
            }
            return FromAxisAngle(axis_x_2, angle);
        } else {
            Quaternion q = FromAxisAngle(axis_y, PI);
            Vector3 axis_y_2 = q * Vector3(0, 1, 0);
            double s = axis_y_2.Cross(axis_y).Dot(axis_x_2);
            double c = axis_y_2.Dot(axis_y);
            double angle = acos_safe(c);
            if (s < 0) {
                angle = -angle;
            }
            return FromAxisAngle(axis_x_2, angle) * q;
        }
    } else {
        double c = axis_x_2.Dot(axis_x);
        double angle = acos_safe(c);
        Quaternion q = FromAxisAngle(axis, angle);
        Vector3 axis_y_2 = q * Vector3(0, 1, 0);
        double s = axis_y_2.Cross(axis_y).Dot(axis_x_2);
        c = axis_y_2.Dot(axis_y);
        angle = acos_safe(c);
        if (s < 0) {
            angle = -angle;
        }
        return FromAxisAngle(axis_x_2, angle) * q;
    }
}

//yaw(Z), pitch(Y), roll(X)，旋转顺序X->Y->Z
Quaternion Quaternion::FromEuler(const Vector3& vt)  {
    double sy, cy, sp, cp, sr, cr;
    sincos(vt.Z * 0.5, &sy, &cy);
    sincos(vt.Y * 0.5, &sp, &cp);
    sincos(vt.X * 0.5, &sr, &cr);
    return Quaternion(
        cy * sr * cp - sy * cr * sp,
        cy * cr * sp + sy * sr * cp,
        sy * cr * cp - cy * sr * sp,
        cy * cr * cp + sy * sr * sp
    );
}

Quaternion Quaternion::FromMatrix3x3(const Matrix3x3& matrix)  {
    int i = 0;
    double d = matrix.M[0][0] - matrix.M[1][1] - matrix.M[2][2];
    double t = matrix.M[1][1] - matrix.M[0][0] - matrix.M[2][2];
    if (t > d) {
        i = 1;
        d = t;
    }
    t = matrix.M[2][2] - matrix.M[0][0] - matrix.M[1][1];
    if (t > d) {
        i = 2;
        d = t;
    }
    t = matrix.M[0][0] + matrix.M[1][1] + matrix.M[2][2];
    if (t > d) {
        i = 3;
        d = t;
    }
    switch (i) {
    case 0: 
        {
            double x = sqrt(d + 1) * 0.5;
            t = 0.25 / x;
            return Quaternion(
                x,
                (matrix.M[1][0] + matrix.M[0][1]) * t,
                (matrix.M[0][2] + matrix.M[2][0]) * t,
                (matrix.M[2][1] - matrix.M[1][2]) * t
            );
        }
    case 1:
        {
            double y = sqrt(d + 1) * 0.5;
            t = 0.25 / y;
            return Quaternion(
                (matrix.M[1][0] + matrix.M[0][1]) * t,
                y,
                (matrix.M[2][1] + matrix.M[1][2]) * t,
                (matrix.M[0][2] - matrix.M[2][0]) * t
            );
        }
    case 2:
        {
            double z = sqrt(d + 1) * 0.5;
            t = 0.25 / z;
            return Quaternion(
                (matrix.M[0][2] + matrix.M[2][0]) * t,
                (matrix.M[2][1] + matrix.M[1][2]) * t,
                z,
                (matrix.M[1][0] - matrix.M[0][1]) * t
            );
        }
    default:
        {
            double w = sqrt(d + 1) * 0.5;
            t = 0.25 / w;
            return Quaternion(
                (matrix.M[2][1] - matrix.M[1][2]) * t,
                (matrix.M[0][2] - matrix.M[2][0]) * t,
                (matrix.M[1][0] - matrix.M[0][1]) * t,
                w
            );
        }
    }
}
