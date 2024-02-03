//
//  Some convenience functions for unusual Qt-object operations
//
// (c) Georg Umlauf, 2022
//
#pragma once

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QColor>

QMatrix4x3 operator * (const QMatrix3x3& a, const QMatrix4x3& b);   // (3x3)-(4x3)-matrix multiplication
QVector3D  operator * (const QMatrix4x3& a, const QVector4D & b);
QVector4D  operator - (const QVector3D & a, const QVector4D & b);
QVector3D  operator ^ (const QMatrix4x4& a, const QVector3D & b);
QVector3D  operator ^ (const QMatrix4x4& a, const QVector4D & b);
QVector4D  to4D       (const QVector3D & a);
