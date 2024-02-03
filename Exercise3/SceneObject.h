//
//  A very simple ABSTRACT class for objects in the scene
//
//  ATTENTION: If you inherit from this class, you MUST implement your own draw- and affineMap-method!!!!!
//
//  (c) Georg Umlauf, 2021+2022
//
#pragma once

#include <QColor>
#include <QMatrix4x4>
#include "Renderer.h"

// some predefined colors
[[maybe_unused]] const QColor COLOR_AXES           = QColor(255,  0,  0);
[[maybe_unused]] const QColor COLOR_PLANE          = QColor(255,255,  0);
[[maybe_unused]] const QColor COLOR_SCENE          = QColor(  0,255,  0);
[[maybe_unused]] const QColor COLOR_RECONSTRUCTION = QColor(255,  0,  0);
[[maybe_unused]] const QColor COLOR_CAMERA         = QColor(255,  0,  0);
[[maybe_unused]] const QColor COLOR_POINT_CLOUD    = QColor(255,255,255);

// some example object types, that you might use
enum class SceneObjectType {ST_NONE                     [[maybe_unused]],   //
                            ST_PLANE                    [[maybe_unused]],   //
                            ST_AXES                     [[maybe_unused]],   // coordinate systems
                            ST_HEXAHEDRON               [[maybe_unused]],   //
                            ST_CUBE                     [[maybe_unused]],   //
                            ST_PERSPECTIVECAMERA        [[maybe_unused]],   // perspective camera
                            ST_STEREOCAMERA             [[maybe_unused]],   // stereo cameras
                            ST_POINT_CLOUD              [[maybe_unused]],   // point cloud
                            ST_MaxSceneType             [[maybe_unused]]};

class SceneObject
{
protected:
    SceneObjectType type;

public:
    SceneObject(                      ): type(SceneObjectType::ST_NONE) {}
    SceneObject(const SceneObject&  so): type(            so.getType()) {}
    SceneObject(const SceneObject&& so): type(            so.getType()) {}
    virtual ~SceneObject()  {}

    virtual void affineMap(const QMatrix4x4&                        )       = 0;
    virtual void draw     (const RenderCamera&, const QColor&, float) const = 0;

    SceneObjectType getType() const { return type; }
};
