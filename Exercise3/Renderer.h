//
//  This is the camera for the rendering (aka painting objects on the canvas) of the scene ONLY.
//
//  It provides methods to render primitives like points, lines, planes, and point clouds.
//
//  Note: If you need other primitives, you have to add your own render-method here.
//
// (c) Georg Umlauf, 2021 + 2022
//
#pragma once

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>

class RenderCamera : public QObject
{
  Q_OBJECT

public:
  RenderCamera(QObject* parent=nullptr);

  // methods to render primitive geometric obejcts, e.g. points, lines, planes, point clouds, etc.
  void renderPoint(const QVector3D& p,
                   const QColor& color, float pointSize=3.0f) const;
  void renderPoint(const QVector4D& p,
                   const QColor& color, float pointSize=3.0f) const;
  void renderLine (const QVector3D& a, const QVector3D& b,
                   const QColor& color, float lineWidth=1.0f) const;
  void renderLine (const QVector4D& a, const QVector4D& b,
                   const QColor& color, float lineWidth=1.0f) const;
  void renderPlane(const QVector3D& a, const QVector3D& b, const QVector3D& c, const QVector3D& d,
                   const QColor& color, float transparency=0.2f) const;
  void renderPCL  (const QVector<QVector4D>& pcl,
                   const QColor& color, float pointSize=3.0f) const;
  void renderCube(const std::vector<QVector3D> cube,
                                const QColor& color, float alpha) const;

  // methods for camera navigation
  void setup   ();
  void reset   ();
  void forward ();
  void backward();
  void left    ();
  void right   ();
  void up      ();
  void down    ();
  void rotate  (int dx, int dy, int dz);

  // setter-methods for render camera parameters
  void setFrontCPDistance (double            d);
  void setRearCPDistance  (double            d);
  void setPosition        (const QVector3D&  p);
  void setProjectionMatrix(const QMatrix4x4& P);
  void setCameraMatrix    (const QMatrix4x4& C);
  void setWorldMatrix     (const QMatrix4x4& W);

  // getter-methods for render camera mappings
  QMatrix4x4 getRenderMatrix() const;
  QMatrix4x4 getViewMatrix  () const;

signals:
  void changed();

public slots:
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);

private:
  double frontClippingPlaneDistance;
  double rearClippingPlaneDistance;
  int xRotation;
  int yRotation;
  int zRotation;

  QVector3D  position;
  QMatrix4x4 projectionMatrix;
  QMatrix4x4 cameraMatrix;
  QMatrix4x4 worldMatrix;
  QMatrix4x4 renderMatrix;

  const int   RotationSTEP    = 1;
  const float TranslationSTEP = 0.005f;
};


