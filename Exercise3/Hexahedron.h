//
//  A simple class for hexahedral objects
//
// (c) Georg Umlauf, 2021
//
#pragma once

#include "SceneObject.h"
#include "Axes.h"
#include <iostream>

class Hexahedron :
    public SceneObject,                         // scene object properties
    public std::vector<QVector3D>               // list of corners, in affine coordinates
{
protected:
    QVector4D origin;                           // origin, controls the distance to the cameras, i.e. typically it's the bottom-left-front corner
    float dx, dy, dz;                           // dy = width, dy = height, dz = thickness/depth

public:
    Hexahedron(QVector4D _ori = E0+E1,          // origin in homogeneous coordinates, i.e. typically it's the bottom-left-front corner
               float     _dx  = 1.0,            // width
               float     _dy  = 1.0,            // height
               float     _dz  = 1.0);           // depth/thickness
    Hexahedron(const Hexahedron&  hex);         // copy constructor
    Hexahedron(const Hexahedron&& hex);         // move constructor
    virtual ~Hexahedron() override {}           // destructor has nothing to do

    // apply affine map to the corners of the hexahedron
    virtual void affineMap (const QMatrix4x4  & matrix) override;
    // draws the wireframe of the hexahedron
    virtual void draw      (const RenderCamera& renderer,
                            const QColor      & color     = COLOR_SCENE,
                            float               lineWidth = 3.0f       ) const override;
    // draws the corners of the hexahedron
            void drawPoints(const RenderCamera& renderer,
                            const QColor      & color     = COLOR_SCENE,
                            float               pointSize = 1);

protected:
    // Some convenience members to iterate a hexahedron's vertices and edges
    constexpr static unsigned edgeCount = 12;
    constexpr static unsigned faceCount = 6;
    constexpr static unsigned edgeList[2*edgeCount] = {0,1,0,3, 1,2,2,3, 4,5,4,7, 5,6,6,7, 0,4,1,5, 2,6,3,7};
    constexpr static unsigned faceList[4*faceCount] = {0,1,2,3, 0,3,7,4, 0,4,5,1, 6,5,4,7, 6,7,3,2, 6,2,1,5};
};

QDebug& operator << (QDebug& dbg, const Hexahedron &hex);
