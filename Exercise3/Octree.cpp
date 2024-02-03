#include "Octree.h"

void Octree::affineMap(const QMatrix4x4  & matrix) {}

void Octree::draw (const RenderCamera& renderer,
               const QColor & colorAxes,
              float lineWidth) const {}

//bool compareX (QVector4D point1, QVector4D point2)
//{
//    return point1.x() < point2.x();
//}

//bool compareY (QVector4D point1, QVector4D point2)
//{
//    return point1.y() < point2.y();
//}

//bool compareZ (QVector4D point1, QVector4D point2)
//{
//    return point1.z() < point2.z();
//}

//// FORMATO RESULT -> {maxX, minX, maxY, minY, maxZ, minZ}
//array<QVector4D, 8> boundingBox (vector<QVector4D> points)
//{
//    array<QVector4D, 8> result;
//    auto xExtremes = minmax_element(points.begin(), points.end(), compareX);
//    auto yExtremes = minmax_element(points.begin(), points.end(), compareY);
//    auto ZExtremes = minmax_element(points.begin(), points.end(), compareZ);
//    // first -> min element, second -> max element
//    result[0] = QVector4D(xExtremes.first->x(), yExtremes.first->y(), ZExtremes.first->z(), 1.);
//    result[1] = QVector4D(xExtremes.first->x(), yExtremes.second->y(), ZExtremes.first->z(), 1.);
//    result[2] = QVector4D(xExtremes.first->x(), yExtremes.first->y(), ZExtremes.second->z(), 1.);
//    result[3] = QVector4D(xExtremes.first->x(), yExtremes.second->y(), ZExtremes.second->z(), 1.);
//    result[4] = QVector4D(xExtremes.second->x(), yExtremes.first->y(), ZExtremes.first->z(), 1.);
//    result[5] = QVector4D(xExtremes.second->x(), yExtremes.second->y(), ZExtremes.first->z(), 1.);
//    result[6] = QVector4D(xExtremes.second->x(), yExtremes.first->y(), ZExtremes.second->z(), 1.);
//    result[7] = QVector4D(xExtremes.second->x(), yExtremes.second->y(), ZExtremes.second->z(), 1.);
//    return result;
//}

//Octree::Node *Octree::createOctree(vector<QVector4D> points, array<QVector4D, 8> boundingBox)
//{
//    Octree::Node *result = new Octree::Node();

//    return result;
//}

//Octree::Octree(PointCloud *pc)
//{
//    vector<QVector4D> * points = reinterpret_cast<vector<QVector4D> *>(pc);
//    auto initialBox = boundingBox(*points);
//    this->root = createOctree(*points, initialBox);
//}
