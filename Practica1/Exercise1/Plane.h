//
// (c) Georg Umlauf, 2021
//
#pragma once

#include "SceneObject.h"
#include "Axes.h"

class Plane : public SceneObject
{
private:
    QVector4D origin, normal;

public:
    Plane (const QVector4D& _origin=E1+E0,
           const QVector4D& _normal=E1);
    virtual ~Plane() override {}

    virtual void affineMap(const QMatrix4x4  & matrix                    ) override;
    virtual void draw     (const RenderCamera& renderer,
                           const QColor      & color        = COLOR_PLANE,
                           float               transparency = 0.2f       ) const override;

    Plane& operator=(const Plane& p);
};
