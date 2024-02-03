
#include "projection.h"
#include "QtConvenience.h"
#include "GLConvenience.h"

using namespace std;


QMatrix4x4 ProjectMat(float fFocus) {


    QMatrix4x4 Pro;
    Pro(0, 0) = 1;
    Pro(0, 1) = 0;
    Pro(0, 2) = 0;
    Pro(0, 3) = 0;
    Pro(1, 0) = 0;
    Pro(1, 1) = 1;
    Pro(1, 2) = 0;
    Pro(1, 3) = 0;
    Pro(2, 0) = 0;
    Pro(2, 1) = 0;
    Pro(2, 2) = 0;
    Pro(2, 3) = 0;
    Pro(3, 0) = 0;
    Pro(3, 1) = 0;
    Pro(3, 2) = -(1/fFocus);
    Pro(3, 3) = 1;



    return Pro;
}
QVector4D projectZ(float fFocus, QVector4D pView) {
    QVector4D res;
    res = ProjectMat(fFocus)* pView;
    res.setX(res.x() / res.w());
    res.setY(res.y() / res.w());
    res.setZ(res.z() / res.w());
    res.setW(res.w() / res.w());

    return res;
}
Projection::Projection(std::vector<QVector4D> cube, float fFocus)
{


    for (int i = 0; i < 8; i++) {

        Points[i] = projectZ(fFocus, cube[i]);
    }


}

void Projection::draw(const RenderCamera& renderer, const QColor& color, float lineWidth) const
{
    QColor c = color;
    c.toHsv();

    renderer.renderLine(Points[0],Points[1],c,lineWidth);
    renderer.renderLine(Points[0],Points[2],c,lineWidth);
    renderer.renderLine(Points[0],Points[4],c,lineWidth);

    renderer.renderLine(Points[1],Points[3],c,lineWidth);
    renderer.renderLine(Points[1],Points[5],c,lineWidth);

    renderer.renderLine(Points[2],Points[3],c,lineWidth);
    renderer.renderLine(Points[2],Points[6],c,lineWidth);

    renderer.renderLine(Points[3],Points[7],c,lineWidth);

    renderer.renderLine(Points[4],Points[5],c,lineWidth);
    renderer.renderLine(Points[4],Points[6],c,lineWidth);

    renderer.renderLine(Points[5],Points[7],c,lineWidth);

    renderer.renderLine(Points[6],Points[7],c,lineWidth);
}
