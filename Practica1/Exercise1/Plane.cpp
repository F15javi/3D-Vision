//
// (c) Georg Umlauf, 2021
//
#include "Plane.h"

Plane::Plane(const QVector4D& _origin, const QVector4D& _normal): origin(_origin), normal(_normal)
{
    type = SceneObjectType::ST_PLANE;
    normal.normalize();
}


void Plane::affineMap(const QMatrix4x4& M)
{
    origin = M*origin;
    normal = M*normal;
    normal.normalize();
}

Plane& Plane::operator=(const Plane& p) {
    if (this!=&p) {
        origin = p.origin;
        normal = p.normal;
    }
    return *this;
}

void Plane::draw(const RenderCamera& renderer,const QColor& color,float transparency ) const
{
    QVector3D n(normal);
    QVector3D o(origin);
    QVector3D y = QVector3D::crossProduct(e1,n);
    if (y.length()< 0.001f) y = QVector3D::crossProduct(e2,n);
    QVector3D x = QVector3D::crossProduct(-y,n);
    x.normalize();
    y.normalize();

    renderer.renderLine(o,o+0.3f*n,color);

    std::vector<QVector2D> bb;
    bb.push_back(QVector2D(-1,-1));
    bb.push_back(QVector2D( 1, 1));
    renderer.renderPlane(o+bb[0][0]*x+bb[0][1]*y,
                         o+bb[0][0]*x+bb[1][1]*y,
                         o+bb[1][0]*x+bb[1][1]*y,
                         o+bb[1][0]*x+bb[0][1]*y,
                         color,transparency);
}
