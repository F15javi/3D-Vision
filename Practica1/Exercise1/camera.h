#pragma once

#include "SceneObject.h"
#include "Plane.h"
#include "Axes.h"


class Camera: public SceneObject
{
private:
    QVector4D cameraOrigin;
    QVector3D planeOrigin;
    QMatrix4x4 rotationRespectWorld; // camera orientation with respect to global coordinates
    float cameraFocalDistance;
    Plane * projectionPlane;
    Axes * cameraAxes;
public:
    Camera(const QVector4D origin, const QVector3D planeCenter, const float focalDistance);
    void projection(
            const std::vector<QVector4D> cube,
            const RenderCamera& renderer,
            const QColor& color,
            float lineWidth
    );
//    void projection2(
//            Scene sceneToRender,
//            const RenderCamera& renderer,
//            const QColor& color,
//            float lineWidth
//    );
    virtual ~Camera() override {};

    virtual void affineMap(const QMatrix4x4  & matrix) override;
    virtual void draw     (const RenderCamera& renderer,
                           const QColor      & colorAxes     = COLOR_AXES,
                           float               lineWidth = 3.0f      ) const override;
};
