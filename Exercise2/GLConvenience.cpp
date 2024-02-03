//
//  Some convenience functions for OpenGL-/Qt-conversions
//
// (c) Georg Umlauf, 2021
//
#include "GLConvenience.h"

void glVertex3f(const QVector3D& a)
{
    glVertex3f(a.x(),a.y(),a.z());
}

void glVertex3f(const QVector4D& a)
{
    glVertex3f(a.x(),a.y(),a.z());
}

void glColor3f (const QColor& c)
{
    glColor3f (float(c.red())/255.0f,float(c.green())/255.0f,float(c.blue())/255.0f  );
}

void glColor4f (const QColor& c)
{
    glColor4f (float(c.red())/255.0f,float(c.green())/255.0f,float(c.blue())/255.0f,float(c.alpha())/255.0f);
}

void glColor4f (const QColor& c, float a)
{
    glColor4f (float(c.red())/255.0f,float(c.green())/255.0f,float(c.blue())/255.0f,a);
}
