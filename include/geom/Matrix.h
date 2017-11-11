#pragma once

#include <iostream>
#include <memory.h>


namespace veteris {
    class Matrix4x4 {
    private:
        float m[4][4];
    public:
        Matrix4x4() {
            for (int i=0; i<4; ++i) {
                for (int j=0; j<4; ++j) {
                    m[i][j] = (i == j)? 1.f: 0.f;
                }
            }
        }
        Matrix4x4(float mat[4][4]) {
            memcpy(m, mat, 16*sizeof(float));
        }
        Matrix4x4(float x00, float x01, float x02, float x03,
                  float x10, float x11, float x12, float x13,
                  float x20, float x21, float x22, float x23,
                  float x30, float x31, float x32, float x33) {
            m[0][0] = x00; m[0][1] = x01; m[0][2] = x02; m[0][3] = x03;
            m[1][0] = x10; m[1][1] = x11; m[1][2] = x12; m[1][3] = x13;
            m[2][0] = x20; m[2][1] = x21; m[2][2] = x22; m[2][3] = x23;
            m[3][0] = x30; m[3][1] = x31; m[3][2] = x32; m[3][3] = x33;
        }
        Matrix4x4(const Matrix4x4 &mat) {
            memcpy(m, mat.m, 16*sizeof(float));
        }
        float *operator[] (int i) {
            return m[i];
        }
        const float *operator [] (int i) const {
            return m[i];
        }
        Matrix4x4 transpose() const {
            Matrix4x4 r;
            for (int i=0; i<4; ++i) {
                for (int j=0; j<4; ++j) {
                    r.m[j][i] = m[i][j];
                }
            }
            return r;
        }
        Matrix4x4 operator * (const Matrix4x4 &n) const {
            Matrix4x4 r;
            for (int i=0; i<4; ++i) {
                for (int j=0; j<4; ++j) {
                    r.m[i][j] = m[i][0]*n.m[0][j]
                              + m[i][1]*n.m[1][j]
                              + m[i][2]*n.m[2][j]
                              + m[i][3]*n.m[3][j];
                }
            }
            return r;
        }
    };
    inline std::ostream &operator << (std::ostream &os, const Matrix4x4 &m) {
        os << "[" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << "]" << "\n";
        os << "[" << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << "]" << "\n";
        os << "[" << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << "]" << "\n";
        os << "[" << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "]" << "\n";
        return os;
    }
}