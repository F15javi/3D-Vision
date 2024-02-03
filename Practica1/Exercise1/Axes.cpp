//
//  A class to render coordinate systems
//
//  ATTENTION: This class is in this form only meant for rendering purposes!
//
// (c) Georg Umlauf, 2021
//
#include "Axes.h"

#include "GLConvenience.h"
#include "QtConvenience.h"

Axes::Axes(const QVector4D&  _origin,
           const QMatrix4x4& _rotation)
    : rotation(_rotation),
      origin  (_origin)
{
    type = SceneObjectType::ST_AXES;
    axes.push_back(QVector3D(origin));
    axes.push_back(QVector3D(origin + rotation.column(0)));
    axes.push_back(QVector3D(origin));
    axes.push_back(QVector3D(origin + rotation.column(1)));
    axes.push_back(QVector3D(origin));
    axes.push_back(QVector3D(origin + rotation.column(2)));
}

void Axes::affineMap(const QMatrix4x4& M)
{
    QMatrix4x4 T = M; T.setColumn(3,E0);
    origin       = M * origin;
    rotation     = T * rotation;
    axes.clear();
    axes.push_back(QVector3D(origin));
    axes.push_back(QVector3D(origin + rotation.column(0)));
    axes.push_back(QVector3D(origin));
    axes.push_back(QVector3D(origin + rotation.column(1)));
    axes.push_back(QVector3D(origin));
    axes.push_back(QVector3D(origin + rotation.column(2)));
}

void Axes::draw(const RenderCamera& renderer, const QColor& color, float lineWidth) const
{
    QColor c = color;
    c.toHsv();
    renderer.renderLine(axes[0],axes[1],c,lineWidth);

    c.setHsv(c.hue()+120, c.saturation(), c.value());
    renderer.renderLine(axes[2],axes[3],c,lineWidth);

    c.setHsv(c.hue()+120, c.saturation(), c.value());
    renderer.renderLine(axes[4],axes[5],c,lineWidth);
}
