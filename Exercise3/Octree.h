
#pragma once

#include <tuple>
#include "SceneObject.h"
#include "PointCloud.h"

using namespace std;

class Octree: public SceneObject
{
public:
    struct Node {
           QVector4D value;
           Node *father;
           Node *NordWest1;
           Node *NoredEast1;
           Node *SouthWest1;
           Node *SouthEast1;
           Node *NordWest2;
           Node *NoredEast2;
           Node *SouthWest2;
           Node *SouthEast2;
        };
    Node *root;
private:
    vector<QVector4D> sortedPointsX;
    vector<QVector4D> sortedPointsY;
    vector<QVector4D> sortedPointsZ;
    QMatrix4x4 rotationRespectWorld;

    Node *createOctree(vector<QVector4D> points, array<QVector4D, 8> boundingBox);
    tuple<vector<QVector4D>, vector<QVector4D>> partitionField(
            int left,
            int right,
            int m,
            int direction,
            vector<QVector4D> pointsX,
            vector<QVector4D> pointsY,
            vector<QVector4D> pointsZ
            );

public:
    Octree(PointCloud *pc);

    virtual ~Octree() override {};

    virtual void affineMap(const QMatrix4x4  & matrix) override;
    virtual void draw     (const RenderCamera& renderer,
                           const QColor      & colorAxes     = COLOR_PLANE,
                           float               lineWidth = 3.0f      ) const override;
};
