//
//  Some convenience functions for unusual Qt-object operations
//
// (c) Georg Umlauf, 2022
//
#include "QtConvenience.h"

QMatrix4x3 operator*(const QMatrix3x3& a, const QMatrix4x3& b)
{
    QMatrix4x3 t;

    for (int i=0; i<3; i++)
        for (int j=0; j<4; j++) {
            t(i,j)=0;
            for (int k=0; k<3; k++) t(i,j) += a(i,k)*b(k,j);
        }
    return t;
}

QVector3D operator*(const QMatrix4x3& a, const QVector4D& b)
{
    QVector3D t;

    for (int i=0; i<3; i++) {
        t[i]=0;
        for (int j=0; j<4; j++) t[i] += a(i,j)*b[j];
    }
    return t;
}

QVector4D operator - (const QVector3D& a, const QVector4D& b)
{
    QVector4D t;

    for (int i=0; i<3; i++) t[i] = a[i]-b[i];
    t[3]= b[3];

    return t;
}

QVector3D operator ^ (const QMatrix4x4 &a, const QVector3D& b)
{
    return a.map(b);
}

QVector3D operator ^ (const QMatrix4x4 &a, const QVector4D& b)
{
    return a^QVector3D(b);
}


QVector4D to4D(const QVector3D &a)
{
    return QVector4D(a[0],a[1],a[2],1);
}
