#include "Camera.h"

#include "QtConvenience.h"
#include "Scene.h"
#include <iostream>

Camera::Camera(const QVector4D origin, const float focalDistance)
{
    type = SceneObjectType::ST_PERSPECTIVECAMERA;
    cameraOrigin = origin;
    cameraAxes = new Axes(origin, QMatrix4x4());
    projectionPlane = new Plane(QVector4D(origin.x(), origin.y(), focalDistance, 0), origin); // AQUI ESTA EL PROBLEMA
    cameraFocalDistance = focalDistance;
    planeOrigin = QVector3D(origin.x(), origin.y(), focalDistance);
    rotationRespectWorld = QMatrix4x4();
    projectedCubes = {};

    std::cout << "Camera origin: (" << origin.x() << ", " << origin.y()<< ", " << origin.z()<< ")" << std::endl;
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
    //projectionPlane->draw(renderer, COLOR_PLANE);
    renderer.renderPoint(planeOrigin, QColor(255, 255, 0), 10.0f);
}

// division by the thrid component is not in the method
void Camera::projection(const std::vector<QVector4D> objectsToRender,
                        const RenderCamera& renderer,
                        const QColor& color,
                        float lineWidth)
{
    std::vector<QVector3D> result;
    for(unsigned int i = 0;i < objectsToRender.size(); i++) {
        QVector4D cubePoint = objectsToRender.at(i);
        float aux = (this->cameraFocalDistance / (cubePoint.z() - this->cameraOrigin.z()));
        QVector3D point = QVector3D(
                    (cubePoint.x() - this->cameraOrigin.x()) * aux,
                    (cubePoint.y() - this->cameraOrigin.y()) * aux,
                    this->planeOrigin.z()
        );
        renderer.renderPoint(point, color, lineWidth);
        result.push_back(point);
    }
    this->projectedCubes.push_back(result);
    renderer.renderCube(result, color, lineWidth);
}


