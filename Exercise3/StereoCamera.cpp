#include "StereoCamera.h"
#include "cube.h"
#include "QtConvenience.h"
#include <iostream>
#include <tuple>

StereoCamera::StereoCamera(
        const QVector4D leftOrigin,
        const QVector4D rightOrigin,
        const float focalDistance,
        const float baseLength)
{
    type = SceneObjectType::ST_STEREOCAMERA;
    leftCameraOrigin = leftOrigin;
    rightCameraOrigin = rightOrigin;
    leftCameraAxes = new Axes(leftOrigin, QMatrix4x4());
    rightCameraAxes = new Axes(rightOrigin, QMatrix4x4());
    // AQUI ESTA EL PROBLEMA
    leftProjectionPlane = new Plane(QVector4D(leftOrigin.x(), leftOrigin.y(), focalDistance, 0), leftOrigin.normalized());
    rightProjectionPlane = new Plane(QVector4D(rightOrigin.x(), rightOrigin.y(), focalDistance, 0), rightOrigin.normalized());
    cameraFocalDistance = focalDistance;
    cameraBaseLength = baseLength;
    leftPlaneOrigin = QVector3D(leftOrigin.x(), leftOrigin.y(), focalDistance);
    rightPlaneOrigin = QVector3D(rightOrigin.x(), rightOrigin.y(), focalDistance);
    leftRotationRespectWorld = QMatrix4x4();
    rightRotationRespectWorld = QMatrix4x4();
    projectCubes = {};
}

void StereoCamera::affineMap(const QMatrix4x4& M)
{
}

void StereoCamera::draw(const RenderCamera& renderer, const QColor& color, float lineWidth) const
{
    QColor c;
    c.green();
    c.toHsv();

    leftCameraAxes->draw(renderer, color, lineWidth);
    rightCameraAxes->draw(renderer, color, lineWidth);
    //leftProjectionPlane->draw(renderer, COLOR_PLANE);
    //rightProjectionPlane->draw(renderer, COLOR_PLANE);
    renderer.renderPoint(leftPlaneOrigin, QColor(255,255,0), 10.0f);
    renderer.renderPoint(rightPlaneOrigin, QColor(0,255,0), 10.0f);
}

// division by the thrid component is not in the method
void StereoCamera::stereoProjection(
                        const std::vector<QVector4D> cube,
                        const RenderCamera& renderer,
                        const QColor& color,
                        float lineWidth)
{
    std::vector<QVector3D> resultLeft;
    std::vector<QVector3D> resultRight;
    for(unsigned int i = 0;i < cube.size(); i++) {
        QVector4D cubePoint = cube.at(i);
        QVector3D points3DLeft = QVector3D(
                    cubePoint.x() - this->leftCameraOrigin.x(),
                    cubePoint.y() - this->leftCameraOrigin.y(),
                    cubePoint.z() - this->leftCameraOrigin.z()
        );
        QVector3D points3DRight = QVector3D(
                    cubePoint.x() - this->rightCameraOrigin.x(),
                    cubePoint.y() - this->rightCameraOrigin.y(),
                    cubePoint.z() - this->rightCameraOrigin.z()
        );
        float auxLeft = (this->cameraFocalDistance / points3DLeft.z());
        float auxRight = (this->cameraFocalDistance / points3DRight.z());
        QVector3D leftPoint = QVector3D(
                    (auxLeft * points3DLeft.x()) + this->leftPlaneOrigin.x(),
                    (auxLeft * points3DLeft.y()) + this->leftPlaneOrigin.y(),
                    this->leftPlaneOrigin.z()
        );
        QVector3D rightPoint = QVector3D(
                    (auxRight * points3DRight.x()) + this->rightPlaneOrigin.x(),
                    (auxRight * points3DRight.y()) + this->rightPlaneOrigin.y(),
                    this->rightPlaneOrigin.z()
        );
        renderer.renderPoint(leftPoint, QColor(255,255,0), 10.0f);
        renderer.renderPoint(rightPoint, color, 10.0f);
        resultLeft.push_back(leftPoint);
        resultRight.push_back(rightPoint);
    }
    auto projectResult = std::make_tuple(resultLeft, resultRight);
    this->projectCubes.push_back(projectResult);
    renderer.renderCube(resultLeft, QColor(255, 255, 0), lineWidth);
    renderer.renderCube(resultRight, color, lineWidth);
}

void StereoCamera::stereoReconstruction(
        const RenderCamera& renderer,
        const QColor& color,
        float lineWidth)
{
    float focalDistance = this->cameraFocalDistance;
    for (auto tuple : this->projectCubes) {
        std::vector<QVector4D> result;
        auto leftProjection = std::get<0>(tuple);
        auto rightProjection = std::get<1>(tuple);
        for (unsigned int i = 0; i < leftProjection.size(); i++) {
            QVector3D leftPoint = leftProjection.at(i);
            QVector3D rightPoint = rightProjection.at(i);
            float z = - focalDistance * ( cameraBaseLength / (rightPoint.x() - leftPoint.x()) );
            float y = - z * ( rightPoint.y() / focalDistance );
            float x = - z * ( rightPoint.x() / focalDistance );
            QVector4D pointCreated = QVector4D(x, y, z, 1);
            result.push_back(pointCreated);
        }
        Cube * cube3D = new Cube(result);
        cube3D->draw(renderer, color, lineWidth);
    };
}
