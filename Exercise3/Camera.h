#pragma once

#include "SceneObject.h"
#include "Plane.h"
#include "Axes.h"
#include "Cube.h"


class Camera: public SceneObject
{
private:
    QVector4D cameraOrigin;
    QVector3D planeOrigin;
    QMatrix4x4 rotationRespectWorld; // camera orientation with respect to global coordinates
    Plane * projectionPlane;
    Axes * cameraAxes;
public:
    float cameraFocalDistance;
    std::vector<std::vector<QVector3D>> projectedCubes;
    Camera(const QVector4D origin, const float focalDistance);
    void projection(
            const std::vector<QVector4D> cube,
            const RenderCamera& renderer,
            const QColor& color,
            float lineWidth
    );
    //std::vector<QVector3D> projectedCube();
    virtual ~Camera() override {};

    virtual void affineMap(const QMatrix4x4  & matrix) override;
    virtual void draw     (const RenderCamera& renderer,
                           const QColor      & colorAxes     = COLOR_AXES,
                           float               lineWidth = 3.0f      ) const override;
};
