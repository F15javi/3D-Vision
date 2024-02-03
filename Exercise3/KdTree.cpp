#include "KdTree.h"

void KdTree::affineMap(const QMatrix4x4& matrix) {}

void KdTree::draw(const RenderCamera& renderer,
                  const QColor & colorAxes,
                  float lineWidth) const {}

bool compareX (QVector4D point1, QVector4D point2)
{
    return point1.x() < point2.x();
}

bool compareY (QVector4D point1, QVector4D point2)
{
    return point1.y() < point2.y();
}

bool compareZ (QVector4D point1, QVector4D point2)
{
    return point1.z() < point2.z();
}

tuple<vector<QVector4D>, vector<QVector4D>, vector<QVector4D>> prepareData(PointCloud *pc)
{
    vector<QVector4D> sortX(pc->size());
    vector<QVector4D> sortY(pc->size());
    vector<QVector4D> sortZ(pc->size());
    partial_sort_copy(begin(*pc), end(*pc), begin(sortX), end(sortX), compareX);
    partial_sort_copy(begin(*pc), end(*pc), begin(sortY), end(sortY), compareY);
    partial_sort_copy(begin(*pc), end(*pc), begin(sortZ), end(sortZ), compareZ);
    return std::make_tuple(sortX, sortY, sortZ);
}



/*
DIRECTION = Y: return {vector, vector} -> newPointsX, newPointsZ
DIRECTION = X: return {vector, vector} -> newPointsZ, newPointsY
DIRECTION = Z: return {vector, vector} -> newPointsY, newPointsX
*/
tuple<vector<QVector4D>, vector<QVector4D>> KdTree::partitionField(
        int left,
        int right,
        int m,
        int direction,
        vector<QVector4D> pointsX,
        vector<QVector4D> pointsY,
        vector<QVector4D> pointsZ
        )
{
    vector<QVector4D> result1;
    vector<QVector4D> result2;
    tuple<vector<QVector4D>, vector<QVector4D>> result;
    if (direction == this->directions->at(0)) {
        vector<QVector4D> leftY(pointsY.begin() + left, pointsY.begin() + m);
        vector<QVector4D> rightY(pointsY.begin() + m + 1, pointsY.begin() + right + 1);
        QVector4D median = pointsY.at(m);
        result1.push_back(median);
        result2.push_back(median);
        int countLeft1 = 0;
        int countLeft2 = 0;
        for (int i = 0; i <= right - left; i++) {
            QVector4D pX = pointsX.at(i + left);
            QVector4D pZ = pointsZ.at(i + left);
            if (pX != median) {
                if (find(leftY.begin(), leftY.end(), pX) != leftY.end()) {
                    result1.insert(result1.begin() + countLeft1, pX);
                    countLeft1++;
                }
                else {
                    result1.push_back(pX);
                }
            }
            if (pZ != median) {
                if (find(leftY.begin(), leftY.end(), pZ) != leftY.end()) {
                    result2.insert(result2.begin() + countLeft2, pZ);
                    countLeft2++;
                } else {
                    result2.push_back(pZ);
                }
            }
        }
        int sizeX = pointsX.size() - 1;
        if (result1.size() != pointsX.size() && left != 0) {
            vector<QVector4D> fillLeft(left);
            result1.insert(result1.begin(), fillLeft.begin(), fillLeft.end());
        }
        if (result1.size() != pointsX.size() && right != sizeX) {
            vector<QVector4D> fillRight(pointsX.size() - right);
            result1.insert(result1.end(), fillRight.begin(), fillRight.end());
        }
        int sizeZ = pointsZ.size();
        if (result2.size() != pointsZ.size() && left != 0) {
            vector<QVector4D> fillLeft(left);
            result2.insert(result2.begin(), fillLeft.begin(), fillLeft.end());
        }
        if (result2.size() != pointsZ.size() && right != sizeZ) {
            vector<QVector4D> fillRight(pointsZ.size() - right);
            result2.insert(result2.end(), fillRight.begin(), fillRight.end());
        }
        result = std::make_tuple(result1, result2);
    } else if (direction == this->directions->at(1)) {
        vector<QVector4D> leftX(pointsX.begin() + left, pointsX.begin() + m);
        vector<QVector4D> rightX(pointsX.begin() + m + 1, pointsX.begin() + right + 1);
        QVector4D median = pointsX.at(m);


        result1.push_back(median);
        result2.push_back(median);
        int countLeft1 = 0;
        int countLeft2 = 0;

        for (int i = 0; i <= right - left; i++) {
            QVector4D pZ = pointsZ.at(i + left);
            QVector4D pY = pointsY.at(i + left);
            if (pZ != median) {
                if (find(leftX.begin(), leftX.end(), pZ) != leftX.end()) {
                    result1.insert(result1.begin() + countLeft1, pZ);
                    countLeft1++;
                }
                else {
                    result1.push_back(pZ);
                }
            }
            if (pY != median) {
                if (find(leftX.begin(), leftX.end(), pY) != leftX.end()) {
                    result2.insert(result2.begin() + countLeft2, pY);
                    countLeft2++;
                } else {
                    result2.push_back(pY);
                }
            }
        }
        // ALGO FALLA AQUI
        int sizeZ = pointsZ.size();
        if (result1.size() != pointsZ.size() && left != 0) {
            vector<QVector4D> fillLeft(left);
            result1.insert(result1.begin(), fillLeft.begin(), fillLeft.end());
        }
        if (result1.size() != pointsZ.size() && right != sizeZ) {
            vector<QVector4D> fillRight(pointsZ.size() - right);
            result1.insert(result1.end(), fillRight.begin(), fillRight.end());
        }
        int sizeY = pointsY.size();
        if (result2.size() != pointsY.size() && left != 0) {
            vector<QVector4D> fillLeft(left);
            result2.insert(result2.begin(), fillLeft.begin(), fillLeft.end());
        }
        if (result2.size() != pointsY.size() && right != sizeY) {
            vector<QVector4D> fillRight(pointsY.size() - right);
            result2.insert(result2.end(), fillRight.begin(), fillRight.end());
        }
        result = std::make_tuple(result1, result2);
    } else {
        vector<QVector4D> leftZ(pointsZ.begin() + left, pointsZ.begin() + m);
        vector<QVector4D> rightZ(pointsZ.begin() + m + 1, pointsZ.begin() + right + 1);
        QVector4D median = pointsZ.at(m);
        result1.push_back(median);
        result2.push_back(median);
        int countLeft1 = 0;
        int countLeft2 = 0;
        for (int i = 0; i <= right - left; i++) {
            QVector4D pY = pointsY.at(i + left);
            QVector4D pX = pointsX.at(i + left);
            if (pY != median) {
                if (find(leftZ.begin(), leftZ.end(), pY) != leftZ.end()) {
                    result1.insert(result1.begin() + countLeft1, pY);
                    countLeft1++;
                }
                else {
                    result1.push_back(pY);
                }
            }
            if (pX != median) {
                if (find(leftZ.begin(), leftZ.end(), pX) != leftZ.end()) {
                    result2.insert(result2.begin() + countLeft2, pX);
                    countLeft2++;
                } else {
                    result2.push_back(pX);
                }
            }
        }
        int sizeY = pointsY.size();
        if (result1.size() != pointsY.size() && left != 0) {
            vector<QVector4D> fillLeft(left);
            result1.insert(result1.begin(), fillLeft.begin(), fillLeft.end());
            }
        if (result1.size() != pointsY.size() && right != sizeY) {
            vector<QVector4D> fillRight(pointsY.size() - right);
            result1.insert(result1.end(), fillRight.begin(), fillRight.end());
        }
        int sizeX = pointsX.size();
        if (result2.size() != pointsX.size() && left != 0) {
            vector<QVector4D> fillLeft(left);
            result2.insert(result2.begin(), fillLeft.begin(), fillLeft.end());
            }
        if (result2.size() != pointsX.size() && right != sizeX) {
            vector<QVector4D> fillRight(pointsX.size() - right);
            result2.insert(result2.end(), fillRight.begin(), fillRight.end());
        }
        result = std::make_tuple(result1, result2);
    }
    return result;
}

KdTree::Node *KdTree::create3DTree(int left, int right, int indexAxis, int layer,
                                   vector<QVector4D> vectorX,
                                   vector<QVector4D> vectorY,
                                   vector<QVector4D> vectorZ)
{
    if (left <= right) {
        KdTree::Node *result = new KdTree::Node();
        auto direction = this->directions->at(indexAxis);
        double leftD = left;
        double rightD = right;
        int m = floor((leftD + rightD) / 2.);

        if (direction == this->directions->at(0)) {
            result->value = this->sortedPointsY.at(m);
            if (left == right) return result;
            auto newPoints = partitionField(
                        left,
                        right,
                        m,
                        direction,
                        vectorX,
                        vectorY,
                        vectorZ
                        );
            vectorX = std::get<0>(newPoints);
            vectorZ = std::get<1>(newPoints);
        } else if (direction == this->directions->at(1)) {
            result->value = this->sortedPointsX.at(m);
            if (left == right ) return result;
            auto newPoints = partitionField(
                        left,
                        right,
                        m,
                        direction,
                        vectorX,
                        vectorY,
                        vectorZ
                        );
            vectorZ = std::get<0>(newPoints);
            vectorY = std::get<1>(newPoints);
        } else {
            result->value = this->sortedPointsZ.at(m);
            if (left == right ) return result;
            auto newPoints = partitionField(
                        left,
                        right,
                        m,
                        direction,
                        vectorX,
                        vectorY,
                        vectorZ
                        );
            vectorY = std::get<0>(newPoints);
            vectorX = std::get<1>(newPoints);
        }
        if (indexAxis < 2) indexAxis++;
        else if (indexAxis == 2) indexAxis = 0;
        if (layer == KdTree::numLayers) return result;
        result->left = create3DTree(left, m - 1, indexAxis, layer++, vectorX, vectorY, vectorZ);
        result->right = create3DTree(m + 1, right, indexAxis, layer++, vectorX, vectorY, vectorZ);
        return result;
    } else return NULL;
}

KdTree::KdTree(PointCloud *pc)
{
    auto sortedPoints = prepareData(pc);
    auto pointsX = std::get<0>(sortedPoints);
    auto pointsY = std::get<1>(sortedPoints);
    auto pointsZ = std::get<2>(sortedPoints);
    this->sortedPointsX = pointsX;
    this->sortedPointsY = pointsY;
    this->sortedPointsZ = pointsZ;
    this->rotationRespectWorld = QMatrix4x4();
    this->root = create3DTree(0, pointsY.size() - 1, 0, 0,
                              pointsX,
                              pointsY,
                              pointsZ);
}


