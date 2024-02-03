#pragma once

#include <tuple>
#include "SceneObject.h"
#include "PointCloud.h"

using namespace std;

class KdTree: public SceneObject
{
public:
    struct Node {
           QVector4D value;
           Node *left;
           Node *right;
        };
    Node *root;
private:
    int numLayers = 3;
    vector<QVector4D> sortedPointsX;
    vector<QVector4D> sortedPointsY;
    vector<QVector4D> sortedPointsZ;
    QMatrix4x4 rotationRespectWorld;
    string directions[3] = {"directionY", "directionX", "directionZ"};

    Node *create3DTree(int left, int right, int indexAxis, int layer,
                       vector<QVector4D> vectorX,
                       vector<QVector4D> vectorY,
                       vector<QVector4D> vectorZ);
//    vector<QVector4D> vectorX = this->sortedPointsX;
//    vector<QVector4D> vectorY = this->sortedPointsY;
//    vector<QVector4D> vectorZ = this->sortedPointsZ;
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
    KdTree(PointCloud *pc);

    virtual ~KdTree() override {};

    virtual void affineMap(const QMatrix4x4  & matrix) override;
    virtual void draw     (const RenderCamera& renderer,
                           const QColor      & colorAxes     = COLOR_PLANE,
                           float               lineWidth = 3.0f      ) const override;
};



//vector<QPointF> partitionField(int left, int right, int m, string direction, vector<QPointF> newX, vector<QPointF> newY)
//{
//    vector<QPointF> result;
//    if (direction == "vertical") {
//        vector<QPointF> leftY(newY.begin() + left, newY.begin() + m);
//        vector<QPointF> rightY(newY.begin() + m + 1, newY.begin() + right + 1);
//        QPointF median = newY.at(m);
//        result.push_back(median);
//        int countLeft = 0;
//        for (int i = 0; i <= right - left; i++) {
//            QPointF p = newX.at(i + left);
//            if (p == median) continue;
//            else if (find(leftY.begin(), leftY.end(), p) != leftY.end()) {
//                result.insert(result.begin() + countLeft, p);
//                countLeft++;
//            }
//            else result.push_back(p);
//        }
//        int sizeX = newX.size() - 1;
//        if (result.size() != newX.size() && left != 0) {
//            vector<QPointF> fillLeft(left);
//            result.insert(result.begin(), fillLeft.begin(), fillLeft.end());
//        }
//        if (result.size() != newX.size() && right != sizeX) {
//            vector<QPointF> fillRight(newX.size() - right -1);
//            result.insert(result.end(), fillRight.begin(), fillRight.end());
//        }
//    } else {
//        vector<QPointF> leftX(newX.begin() + left, newX.begin() + m);
//        vector<QPointF> rightX(newX.begin() + m + 1, newX.begin() + right + 1);
//        QPointF median = newX.at(m);
//        result.push_back(median);
//        int countLeft = 0;
//        for (int i = 0; i <= right - left; i++) {
//            QPointF p = newY.at(i + left);
//            if (p == median) continue;
//            else if (find(leftX.begin(), leftX.end(), p) != leftX.end()) {
//                result.insert(result.begin() + countLeft, p);
//                countLeft++;
//            }
//            else result.push_back(p);
//        }
//        int sizeY = newY.size() - 1;
//        if (result.size() != newY.size() && left != 0) {
//            vector<QPointF> fillLeft(left);
//            result.insert(result.begin(), fillLeft.begin(), fillLeft.end());
//        }
//        if (result.size() != newY.size() && right != sizeY) {
//            vector<QPointF> fillRight(newX.size() - right - 1);
//            result.insert(result.end(), fillRight.begin(), fillRight.end());
//        }
//    }
//    return result;
//};

//Node3 *createTree2D(int left, int right, string direction, vector<QPointF> newX, vector<QPointF> newY)
//{
//    if (left <= right) {
//        Node3 *result = new Node3();
//        double leftD = left;
//        double rightD = right;
//        int m = ceil((leftD + rightD) / 2.);
//        if (direction == "vertical") {
//            result->value = newY.at(m);
//            if (left == right) return result;
//            newX = partitionField(left, right, m, direction, newX, newY);
//        } else {
//            result->value = newX.at(m);
//            if (left == right ) return result;
//            newY = partitionField(left, right, m, direction, newX, newY);
//        }
//        string newD = direction == "vertical" ? "horizontal" : "vertical";
//        result->left = createTree2D(left, m - 1, newD, newX, newY);
//        result->right = createTree2D(m + 1, right, newD, newX, newY);
//        return result;
//    }
//    else return NULL;
//};
