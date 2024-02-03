//
// (c) Georg Umlauf, 2022
//
#pragma once

#include "QtConvenience.h"
#include "SceneObject.h"
#include "Renderer.h"

class PointCloud: public SceneObject, public QVector<QVector4D>
{
private:
    QVector3D    pointsBoundMin;
    QVector3D    pointsBoundMax;

    unsigned     pointSize       = 3;
    const float  pointCloudScale = 1.5f;

public:
    PointCloud();
    virtual ~PointCloud();

    bool loadPLY(const QString&);

    virtual void affineMap(const QMatrix4x4&) override;
    virtual void draw     (const RenderCamera& camera,
                           const QColor      & color      = COLOR_POINT_CLOUD,
                           float               point_size = 3.0f) const override;
    QVector3D getMin() const { return pointsBoundMin; }
    QVector3D getMax() const { return pointsBoundMax; }

    // setup point size
    void     setPointSize(unsigned s);
    unsigned getPointSize(          ) const { return pointSize; }
};

