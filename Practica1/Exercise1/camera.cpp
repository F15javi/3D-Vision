#include "Camera.h"

#include "QtConvenience.h"
#include "Scene.h"
#include <iostream>

Camera::Camera(const QVector4D origin, const QVector3D planeCenter, const float focalDistance)
{
    type = SceneObjectType::ST_PERSPECTIVECAMERA;
    cameraOrigin = origin;
    cameraAxes = new Axes(origin, QMatrix4x4());
    projectionPlane = new Plane(origin * focalDistance, origin.normalized());
    cameraFocalDistance = focalDistance;
    planeOrigin = planeCenter;
    rotationRespectWorld = QMatrix4x4();
}

void Camera::affineMap(const QMatrix4x4& M)
{
}

void Camera::draw(const RenderCamera& renderer, const QColor& color, float lineWidth) const
{
    QColor c;
    c.green();
    c.toHsv();

    cameraAxes->draw(renderer, color, lineWidth);
    projectionPlane->draw(renderer, color.red());
    renderer.renderPoint(planeOrigin, COLOR_SCENE, 2.0f);
}

// division by the thrid component is not in the method
void Camera::projection(const std::vector<QVector4D> objectsToRender,
                        const RenderCamera& renderer,
                        const QColor& color,
                        float lineWidth)
{
    std::vector<QVector3D> result;
    float projectVector[] = {
        this->cameraFocalDistance, 0,                         0, 0,
        0,                         this->cameraFocalDistance, 0, 0,
        0,                         0,                        -1, 0
    };

    QMatrix4x3 projectMatrix = QMatrix4x3(projectVector);
    std::cout << "Focal distance: " << cameraFocalDistance << std::endl;
    for(unsigned int i = 0;i < objectsToRender.size(); i++) {
        QVector4D cubePoint = objectsToRender.at(i);
        QVector3D point = projectMatrix * cubePoint;
        point = QVector3D(point.x() / cubePoint.z(), point.y() / cubePoint.z(),this->planeOrigin.z());
        std::cout << "x: " << point.x() << "y : " << point.y()<< " z: " << point.z() << std::endl;
        renderer.renderPoint(point, color, 10.0f);
        result.push_back(point);
//        if (i % 2 != 0) {
//            renderer.renderLine(result.at(i-1), point2D, color, lineWidth);
//        }
    }
    renderer.renderCube(result, color, 1.0f);
}


