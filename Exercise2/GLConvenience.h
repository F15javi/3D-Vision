//
//  Some convenience functions for OpenGL-/Qt-conversions
//
// (c) Georg Umlauf, 2021
//
#pragma once

#include <QtGui>
#include <QVector3D>
#include <QVector4D>
#include <QColor>

void glVertex3f(const QVector3D& a);
void glVertex3f(const QVector4D& a);
void glColor3f (const QColor   & c);
void glColor4f (const QColor   & c);
void glColor4f (const QColor   & c, float a);

