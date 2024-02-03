#pragma once

#include <tuple>
#include "SceneObject.h"
#include "Plane.h"
#include "Axes.h"

class StereoCamera: public SceneObject
{
private:
    QVector4D leftCameraOrigin;
    QVector3D leftPlaneOrigin;
    QMatrix4x4 leftRotationRespectWorld; // camera orientation with respect to global coordinates
    Plane * leftProjectionPlane;
    Axes * leftCameraAxes;
    QVector4D rightCameraOrigin;
    QVector3D rightPlaneOrigin;
    QMatrix4x4 rightRotationRespectWorld; // camera orientation with respect to global coordinates
    Plane * rightProjectionPlane;
    Axes * rightCameraAxes;
    float cameraBaseLength;
    std::vector<std::tuple<std::vector<QVector3D>, std::vector<QVector3D>>> projectCubes;
public:
    float cameraFocalDistance;
    StereoCamera(const QVector4D leftOrigin,
                 const QVector4D rightOrigin,
                 const float focalDistance,
                 const float baseLength
    );
    void stereoProjection(
            const std::vector<QVector4D> cube,
            const RenderCamera& renderer,
            const QColor& color,
            float lineWidth
    );
    void stereoReconstruction(
            const RenderCamera& renderer,
            const QColor& color = QColor(255, 0, 0),
            float lineWidth = 2.0f
    );
    virtual ~StereoCamera() override {};

    virtual void affineMap(const QMatrix4x4  & matrix) override;
    virtual void draw     (const RenderCamera& renderer,
                           const QColor      & colorAxes     = COLOR_AXES,
                           float               lineWidth = 3.0f      ) const override;
};
