using namespace std;

#include "Cube.h"
#include "QtConvenience.h"

Cube::Cube(const std::vector<QVector4D>  origin)
{
    type = SceneObjectType::ST_CUBE;
    cube.push_back(origin[0]);
    cube.push_back(origin[1]);
    cube.push_back(origin[2]);
    cube.push_back(origin[3]);
    cube.push_back(origin[4]);
    cube.push_back(origin[5]);
    cube.push_back(origin[6]);
    cube.push_back(origin[7]);
}

//Cube::Cube(float width, float height, float depth)
//{
//    this->type = SceneObjectType::ST_CUBE;
//}

void Cube::affineMap(const QMatrix4x4& M)
{
}


void Cube::draw(const RenderCamera& renderer, const QColor& color, float lineWidth) const
{
    QColor c = color;
    c.toHsv();

    renderer.renderLine(cube[0],cube[1],c,lineWidth);
    renderer.renderLine(cube[0],cube[2],c,lineWidth);
    renderer.renderLine(cube[0],cube[4],c,lineWidth);

    renderer.renderLine(cube[1],cube[3],c,lineWidth);
    renderer.renderLine(cube[1],cube[5],c,lineWidth);

    renderer.renderLine(cube[2],cube[3],c,lineWidth);
    renderer.renderLine(cube[2],cube[6],c,lineWidth);

    renderer.renderLine(cube[3],cube[7],c,lineWidth);

    renderer.renderLine(cube[4],cube[5],c,lineWidth);
    renderer.renderLine(cube[4],cube[6],c,lineWidth);

    renderer.renderLine(cube[5],cube[7],c,lineWidth);

    renderer.renderLine(cube[6],cube[7],c,lineWidth);
}
