//
//  A class to render coordinate systems
//
//  ATTENTION: This class is in this form only meant for rendering purposes!
//
// (c) Georg Umlauf, 2021
//
#pragma once

#include "QtConvenience.h"
#include "SceneObject.h"

#include <QMatrix4x4>

[[maybe_unused]] const QVector4D E0 = QVector4D(0,0,0,1);    // world origin    in homogeneous coordinates
[[maybe_unused]] const QVector4D E1 = QVector4D(1,0,0,0);    // 1st unit vector in homogeneous coordinates
[[maybe_unused]] const QVector4D E2 = QVector4D(0,1,0,0);    // 2nd unit vector in homogeneous coordinates
[[maybe_unused]] const QVector4D E3 = QVector4D(0,0,1,0);    // 3rd unit vector in homogeneous coordinates
[[maybe_unused]] const QVector3D e1 = QVector3D(1,0,0);      // 1st unit vector in affine      coordinates
[[maybe_unused]] const QVector3D e2 = QVector3D(0,1,0);      // 2nd unit vector in affine      coordinates
[[maybe_unused]] const QVector3D e3 = QVector3D(0,0,1);      // 3rd unit vector in affine      coordinates

class Axes: public SceneObject
{
private:
    std::vector<QVector3D> axes;
    QMatrix4x4             rotation;
    QVector4D              origin;

public:
    Axes(const QVector4D&  origin   = E0,
         const QMatrix4x4& rotation = QMatrix4x4());
    virtual ~Axes() override {}

    virtual void affineMap(const QMatrix4x4  & matrix) override;
    virtual void draw     (const RenderCamera& renderer,
                           const QColor      & color     = COLOR_AXES,
                           float               lineWidth = 3.0f      ) const override;
};

