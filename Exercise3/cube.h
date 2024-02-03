#pragma once

#include "QtConvenience.h"
#include "SceneObject.h"

#include <QMatrix4x4>

class Cube: public SceneObject {
private:

public:
    std::vector<QVector4D> cube;
    Cube(const std::vector<QVector4D>  origin);
    Cube(float width, float height, float depth);
    virtual ~Cube() override {}

    virtual void affineMap(const QMatrix4x4  & matrix) override;
    virtual void draw     (const RenderCamera& renderer,
                           const QColor      & color     = COLOR_AXES,
                           float               lineWidth = 3.0f      ) const override;
};
