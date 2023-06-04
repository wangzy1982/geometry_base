#ifndef _WGEO_CORE_MATRIX_
#define _WGEO_CORE_MATRIX_

class Matrix3x3 {
public:
    double M[3][3];
public:
    Matrix3x3();
    Matrix3x3(double m00, double m01, double m02, 
        double m10, double m11, double m12,
        double m20, double m21, double m22);
    static Matrix3x3 Identity();
};

inline Matrix3x3::Matrix3x3() {
    M[0][0] = 0; M[0][1] = 0; M[0][2] = 0;
    M[1][0] = 0; M[1][1] = 0; M[1][2] = 0;
    M[2][0] = 0; M[2][1] = 0; M[2][2] = 0;
}

inline Matrix3x3::Matrix3x3(double m00, double m01, double m02, 
    double m10, double m11, double m12,
    double m20, double m21, double m22) {
    M[0][0] = m00; M[0][1] = m01; M[0][2] = m02;
    M[1][0] = m10; M[1][1] = m11; M[1][2] = m12;
    M[2][0] = m20; M[2][1] = m21; M[2][2] = m22;
}

inline Matrix3x3 Matrix3x3::Identity() {
    return Matrix3x3(
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    );
}

#endif