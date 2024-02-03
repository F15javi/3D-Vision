//
//  A very simple class for rudimentary scene management
//
//  (c) Georg Umlauf, 2021+2022
//
#include <iostream>
#include "QtConvenience.h"

#include "Scene.h"
#include "Camera.h"
#include "StereoCamera.h"

//
// iterates all objects under its control and has them drawn by the renderer
//
void Scene::draw(const RenderCamera& renderer, const QColor& color) const
{
    for (auto obj : *this) if (obj)
    {
        switch (obj->getType())
        {
            case SceneObjectType::ST_AXES: {
                obj->draw(renderer,COLOR_AXES,2.0f);
                break;
            }
            case SceneObjectType::ST_PLANE: {
                obj->draw(renderer,COLOR_PLANE, 0.3f);
                break;
            }
            case SceneObjectType::ST_CUBE: {
                obj->draw(renderer, COLOR_SCENE, 2.0f);
                break;
            }
            case SceneObjectType::ST_HEXAHEDRON: {
                obj->draw(renderer,color,2.0f);
                break;
            }
            case SceneObjectType::ST_POINT_CLOUD: {
                obj->draw(renderer,COLOR_POINT_CLOUD,3.0f);     // last argument unused
                break;
            }
            case SceneObjectType::ST_PERSPECTIVECAMERA: {
                // TODO: Assignement 1, Part 3
                // This is the place to invoke the perspective camera's projection method and draw the projected objects.
                obj->draw(renderer, COLOR_CAMERA, 2.0f);
                Camera * cam = reinterpret_cast<Camera*>(obj);
                for (auto o : *this) {
                    if (o->getType() == SceneObjectType::ST_CUBE) {
                        Cube * cub = reinterpret_cast<Cube *>(o);
                        cam->projection(cub->cube, renderer, QColor(255, 255, 0), 2.0f);
                    }
                }
                break;
            }
            case SceneObjectType::ST_STEREOCAMERA: {
                // TODO: Assignement 2, Part 1 - 3
                obj->draw(renderer, COLOR_CAMERA, 2.0f);
                // Part 1: This is the place to invoke the stereo camera's projection method and draw the projected objects.
                StereoCamera * cam = reinterpret_cast<StereoCamera *>(obj);
                for (auto o : *this) {
                    if (o->getType() == SceneObjectType::ST_CUBE) {
                        Cube * cub = reinterpret_cast<Cube *>(o);
                        cam->stereoProjection(cub->cube, renderer, COLOR_SCENE, 2.0f);
                    }
                }
                // Part 2: This is the place to invoke the stereo camera's reconstruction method.
                cam->stereoReconstruction(renderer);
                // Part 3: This is the place to invoke the stereo camera's reconstruction method using misaligned stereo cameras.
               break;
            }
        }
    }
}
