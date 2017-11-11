#pragma once

#include <cmath>
#include <iostream>

#include "Matrix.h"
#include "Vector.h"
#include "Point.h"
#include "Normal.h"
#include "Box.h"

namespace veteris
{
    class Transform3
    {
    public:
        Matrix4x4 matrix, inverse;
        Transform3() : matrix(), inverse() {}
        Transform3(const Matrix4x4 &m, const Matrix4x4 &i) :
                matrix(m), inverse(i) {}
        Transform3 operator * (const Transform3 &t) const
        {
            return Transform3(matrix*t.matrix, t.inverse*inverse);
        }
        Point3 transform(const Point3 &p) const
        {
            float tx = matrix[0][0]*p.X + matrix[0][1]*p.Y + matrix[0][2]*p.Z + matrix[0][3];
            float ty = matrix[1][0]*p.X + matrix[1][1]*p.Y + matrix[1][2]*p.Z + matrix[1][3];
            float tz = matrix[2][0]*p.X + matrix[2][1]*p.Y + matrix[2][2]*p.Z + matrix[2][3];
            float w = matrix[3][0]*p.X + matrix[3][1]*p.Y + matrix[3][2]*p.Z + matrix[3][3];
            if (w != 1.F)
            {
                float inv_w = 1.F/w;
                return Point3(tx*inv_w, ty*inv_w, tz*inv_w);
            }
            return Point3(tx, ty, tz);
        }
        Point3 invert(const Point3 &p) const
        {
            float tx = inverse[0][0]*p.X + inverse[0][1]*p.Y + inverse[0][2]*p.Z + inverse[0][3];
            float ty = inverse[1][0]*p.X + inverse[1][1]*p.Y + inverse[1][2]*p.Z + inverse[1][3];
            float tz = inverse[2][0]*p.X + inverse[2][1]*p.Y + inverse[2][2]*p.Z + inverse[2][3];
            float w = inverse[3][0]*p.X + inverse[3][1]*p.Y + inverse[3][2]*p.Z + inverse[3][3];
            if (w != 1.F)
            {
                float inv_w = 1.F/w;
                return Point3(tx*inv_w, ty*inv_w, tz*inv_w);
            }
            return Point3(tx, ty, tz);
        }
        Vector3 transform(const Vector3 &v) const
        {
            return Vector3(matrix[0][0]*v.X + matrix[0][1]*v.Y + matrix[0][2]*v.Z,
                            matrix[1][0]*v.X + matrix[1][1]*v.Y + matrix[1][2]*v.Z,
                            matrix[2][0]*v.X + matrix[2][1]*v.Y + matrix[2][2]*v.Z);
        }
        Vector3 invert(const Vector3 &v) const
        {
            return Vector3(inverse[0][0]*v.X + inverse[0][1]*v.Y + inverse[0][2]*v.Z,
                            inverse[1][0]*v.X + inverse[1][1]*v.Y + inverse[1][2]*v.Z,
                            inverse[2][0]*v.X + inverse[2][1]*v.Y + inverse[2][2]*v.Z);
        }
        Normal3 transform(const Normal3 &n) const
        {
            return Normal3(inverse[0][0]*n.X + inverse[1][0]*n.Y + inverse[2][0]*n.Z,
                            inverse[0][1]*n.X + inverse[1][1]*n.Y + inverse[2][1]*n.Z,
                            inverse[0][2]*n.X + inverse[1][2]*n.Y + inverse[2][2]*n.Z);
        }
        Normal3 invert(const Normal3 &n) const
        {
            return Normal3(matrix[0][0]*n.X + matrix[1][0]*n.Y + matrix[2][0]*n.Z,
                            matrix[0][1]*n.X + matrix[1][1]*n.Y + matrix[2][1]*n.Z,
                            matrix[0][2]*n.X + matrix[1][2]*n.Y + matrix[2][2]*n.Z);
        }
        Box3 transform(const Box3 &b) const
        {
            Box3 r(transform(b.min));
            r.unionWith(transform(Point3(b.min.X, b.min.Y, b.max.Z)));
            r.unionWith(transform(Point3(b.min.X, b.max.Y, b.min.Z)));
            r.unionWith(transform(Point3(b.min.X, b.max.Y, b.max.Z)));
            r.unionWith(transform(Point3(b.max.X, b.min.Y, b.min.Z)));
            r.unionWith(transform(Point3(b.max.X, b.min.Y, b.max.Z)));
            r.unionWith(transform(Point3(b.max.X, b.max.Y, b.min.Z)));
            r.unionWith(transform(b.max));
            return r;
        }
        Box3 invert(const Box3 &b) const
        {
            Box3 r(invert(b.min));
            r.unionWith(invert(Point3(b.min.X, b.min.Y, b.max.Z)));
            r.unionWith(invert(Point3(b.min.X, b.max.Y, b.min.Z)));
            r.unionWith(invert(Point3(b.min.X, b.max.Y, b.max.Z)));
            r.unionWith(invert(Point3(b.max.X, b.min.Y, b.min.Z)));
            r.unionWith(invert(Point3(b.max.X, b.min.Y, b.max.Z)));
            r.unionWith(invert(Point3(b.max.X, b.max.Y, b.min.Z)));
            r.unionWith(invert(b.max));
            return r;
        }
        static Transform3 translate(float x, float y, float z)
        {
            Matrix4x4 mat(1.F, 0.F, 0.F, x,
                          0.F, 1.F, 0.F, y,
                          0.F, 0.F, 1.F, z,
                          0.F, 0.F, 0.F, 1.F);
            Matrix4x4 inv(1.F, 0.F, 0.F, -x,
                          0.F, 1.F, 0.F, -y,
                          0.F, 0.F, 1.F, -z,
                          0.F, 0.F, 0.F, 1.F);
            return Transform3(mat, inv);
        }
        static Transform3 scale(float x, float y, float z)
        {
            Matrix4x4 mat(  x, 0.F, 0.F, 0.F,
                            0.F,   y, 0.F, 0.F,
                            0.F, 0.F,   z, 0.F,
                            0.F, 0.F, 0.F, 1.F);
            Matrix4x4 inv(1.F/x,   0.F,   0.F, 0.F,
                          0.F, 1.F/y,   0.F, 0.F,
                          0.F,   0.F, 1.F/z, 0.F,
                          0.F,   0.F,   0.F, 1.F);
            return Transform3(mat, inv);
        }
        static Transform3 rotateZ(float t)
        {
            float cost = cosf(t);
            float sint = sinf(t);
            Matrix4x4 mat(cost, -sint, 0.F, 0.F,
                          sint,  cost, 0.F, 0.F,
                          0.F,   0.F, 1.F, 0.F,
                          0.F,   0.F, 0.F, 1.F);
            Matrix4x4 inv( cost, sint, 0.F, 0.F,
                           -sint, cost, 0.F, 0.F,
                           0.F,  0.F, 1.F, 0.F,
                           0.F,  0.F, 0.F, 1.F);
            return Transform3(mat, inv);
        }
        static Transform3 rotateY(float t)
        {
            float cost = cosf(t);
            float sint = sinf(t);
            Matrix4x4 mat( cost, 0.F, sint, 0.F,
                           0.F, 1.F,  0.F, 0.F,
                           -sint, 0.F, cost, 0.F,
                           0.F, 0.F,  0.F, 1.F);
            Matrix4x4 inv(cost, 0.F, -sint, 0.F,
                          0.F, 1.F,   0.F, 0.F,
                          sint, 0.F,  cost, 0.F,
                          0.F, 0.F,   0.F, 1.F);
            return Transform3(mat, inv);
        }
        static Transform3 rotateX(float t)
        {
            float cost = cosf(t);
            float sint = sinf(t);
            Matrix4x4 mat(1.F,  0.F,   0.F, 0.F,
                          0.F, cost, -sint, 0.F,
                          0.F, sint,  cost, 0.F,
                          0.F,  0.F,   0.F, 1.F);
            Matrix4x4 inv(1.F,   0.F,  0.F, 0.F,
                          0.F,  cost, sint, 0.F,
                          0.F, -sint, cost, 0.F,
                          0.F,   0.F,  0.F, 1.F);
            return Transform3(mat, inv);
        }
        static Transform3 rotate(float rx, float ry, float rz)
        {
            float cx = cosf(rx);
            float sx = sinf(rx);
            float cy = cosf(ry);
            float sy = sinf(ry);
            float cz = cosf(rz);
            float sz = sinf(rz);
            Matrix4x4 mat(         cy*cz,         -cy*sz,              sy, 0,
                                   sx*sy*cz+cx*sz, cx*cz-sx*sy*sz, -sx*cy, 0,
                                   sx*sz-cx*sy*cz, cx*sy*sz+sx*cz,  cx*cy, 0,
                                   0,              0,     0, 1);
            Matrix4x4 inv = mat.transpose();
            return Transform3(mat, inv);
        }
        static Transform3 perspective(float fov, float n, float f)
        {
            float p = 1.F/(1.F - n/f);
            float inv_tan = 1.F/tanf(fov*0.5F);
            Transform3 r;
            r.matrix[0][0] = inv_tan;
            r.matrix[1][1] = inv_tan;
            r.matrix[2][2] = p;
            r.matrix[2][2] = -n*p;
            r.matrix[3][2] = 1.F;
            r.matrix[3][3] = 0.F;
            return r;
        }
    };
    inline std::ostream &operator << (std::ostream &os, const Transform3 &t)
    {
        os << "matrix:\n" << t.matrix;
        os << "inverse:\n" << t.inverse;
        return os;
    }
}