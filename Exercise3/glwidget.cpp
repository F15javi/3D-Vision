//
// (c) Nico Brügel, 2021
// (c) Georg Umlauf, 2021+2022
//
#include "glwidget.h"
#include <QtGui>

#if defined(__APPLE__)
// we're on macOS and according to their documentation Apple hates developers
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#elseif defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
// windows, even if it's case insensitive QT-Create might generate a warning
#include <gl/GL.h>
#include <gl/GLU.h>
#else
// hopefully on linux
// If can't be found, ensure that the following is installed:
// libglu1-mesa-dev and/or mesa-common-dev
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <QApplication>
#include <QtGui>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>

#include <cmath>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <utility>

#include "StereoCube.h"
#include "PointCloud.h"
#include "KdTree.h"
#include "Plane.h"

using namespace std;

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent), pointSize(5)
{
    // enable mouse-events, even if no mouse-button is pressed -> yields smoother mouse-move reactions
    setMouseTracking(true);

    // setup render camera and connect its signals
    renderer = new RenderCamera();
    renderer->reset();
    connect(renderer, &RenderCamera::changed, this, &GLWidget::onRendererChanged);

    // setup the scene
    //scene.push_back(new Axes(E0,QMatrix4x4()));    // the global world coordinate system

}

//
//  destructor has nothing to do, since it's under Qt control
//
GLWidget::~GLWidget()
{
}

//
//  initializes the canvas and OpenGL context
//
void GLWidget::initializeGL()
{
      // ensure GL flags
      glEnable(GL_POINT_SMOOTH);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glClearColor(0.4f,0.4f,0.4f,1);                       // screen background color
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);               //required for gl_PointSize
}

//
//  redraws the canvas
//
void GLWidget::paintGL()
{
    renderer->setup();

    scene.draw(*renderer,COLOR_SCENE);

    // Assignement 1, Part 2
    // Draw here your perspective camera model

    // Assignement 1, Part 3
    // Draw here the perspective projection
}

//
//  reacts on resize events
//
void GLWidget::resizeGL(int width, int height)
{
    QMatrix4x4 projectionMatrix;
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(70.0f, GLfloat(width) / GLfloat(height), 0.01f, 100.0f);
    renderer->setProjectionMatrix(projectionMatrix);
}

//
//  reacts on mouse-wheel events
//
void GLWidget::wheelEvent(QWheelEvent* event)
{
    // read the wheel angle and rotate move renderer in/out
    if (event->angleDelta().y() > 0) renderer->forward ();
    else                             renderer->backward();
}

//
//  reacts on key-release events
//
void GLWidget::keyReleaseEvent(QKeyEvent * event)
{
    switch ( event->key() )
    {
        // release camera's axis of rotation
      case Qt::Key_X: X_Pressed=false; break;
      case Qt::Key_Y: Y_Pressed=false; break;
        // for unhandled events call, keyReleaseEvent of parent class
      default: QWidget::keyReleaseEvent(event); break;
    }
    update();
}

//
//  reacts on key-press events
//
void GLWidget::keyPressEvent(QKeyEvent * event)
{
    switch ( event->key() )
    {
        // trigger translation using keyboard
    case Qt::Key_4:
    case Qt::Key_Left:     renderer->left    (); break;
    case Qt::Key_6:
    case Qt::Key_Right:    renderer->right   (); break;
    case Qt::Key_9:
    case Qt::Key_PageUp:   renderer->forward (); break;
    case Qt::Key_3:
    case Qt::Key_PageDown: renderer->backward(); break;
    case Qt::Key_8:
    case Qt::Key_Up:       renderer->up      (); break;
    case Qt::Key_2:
    case Qt::Key_Down:     renderer->down    (); break;
        // reset camera position
    case Qt::Key_R:        renderer->reset   (); break;
        // clamp camera's axis of rotation
    case Qt::Key_X:        X_Pressed=true;       break;
    case Qt::Key_Y:        Y_Pressed=true;       break;
        // quit application
    case Qt::Key_Q:
    case Qt::Key_Escape: QApplication::instance()->quit(); break;
        // for unhandled events call, keyPressEvent of parent class
    default: QWidget::keyPressEvent(event);  break;
    }
    update();
}

//
//  reacts on mouse-move events
//
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint d = event->pos()-prevMousePosition;
    prevMousePosition = event->pos();

    // if left-mouse-button is pressed, trigger rotation of renderer
    if (event->buttons() & Qt::LeftButton)
    {
        renderer->rotate(X_Pressed?0:d.y(), Y_Pressed?0:d.x(), 0);
    }
    // if right-mouse-button is pressed, trigger translation of renderer
    else if ( event->buttons() & Qt::RightButton)
    {
        if (d.x() < 0) renderer->right();
        if (d.x() > 0) renderer->left();
        if (d.y() < 0) renderer->down();
        if (d.y() > 0) renderer->up();
    }
}

//
//  triggers re-draw after, if renderer emits changed signal
//
void GLWidget::onRendererChanged()
{
  update();
}

//
// updates the point size in each point cloud in the scene management
//
void GLWidget::setPointSize(int size)
{
  assert(size > 0);
  pointSize = size;
  for (auto s: scene) if (s->getType()==SceneObjectType::ST_POINT_CLOUD) reinterpret_cast<PointCloud*>(s)->setPointSize(unsigned(pointSize));
  update();
}

//
// 1. reacts on push button click
// 2. opens file dialog
// 3. loads ply-file data to new point cloud
// 4. attaches new point cloud to scene managment
//
void GLWidget::openFileDialog()
{
    const QString filePath   = QFileDialog::getOpenFileName(this, tr("Open PLY file"), "../data", tr("PLY Files (*.ply)"));
    PointCloud*   pointCloud = new PointCloud;

    if (!filePath.isEmpty() && pointCloud)
    {
         cout << filePath.toStdString() << endl;
         pointCloud->loadPLY(filePath);
         pointCloud->setPointSize(unsigned(pointSize));
         // LANZAR AQUI EL CODIGO PARA RENDERIZAR EL ARBOL
         //scene.push_back(new Axes(E0,QMatrix4x4()));    // the global world coordinate system
         auto tree = KdTree(pointCloud);
         auto layer1 = tree.root->value; // Y
         auto layer2Left = tree.root->left->value; // X
         auto layer2Right = tree.root->right->value; // X
         auto layer3LeftLeft = tree.root->left->left->value; // Z
         auto layer3LeftRight = tree.root->left->right->value; // Z
         auto layer3RightLeft = tree.root->right->left->value; // Z
         auto layer3RightRight = tree.root->right->right->value; // Z
         Plane *firstPlane = new Plane(layer1, E2.normalized());
         Plane *secondPlaneLeft = new Plane(layer2Left, E1.normalized());
         Plane *secondPlaneRight = new Plane(layer2Right, E1.normalized());
         Plane *thirdPlaneLeftLeft = new Plane(layer3LeftLeft, E3.normalized());
         Plane *thirdPlaneLeftRight = new Plane(layer3LeftRight, E3.normalized());
         Plane *thirdPlaneRightLeft = new Plane(layer3RightLeft, E3.normalized());
         Plane *thirdPlaneRightRight = new Plane(layer3RightRight, E3.normalized());
         scene.push_back(pointCloud);
         scene.push_back(firstPlane);
         scene.push_back(secondPlaneLeft);
         scene.push_back(secondPlaneRight);
         scene.push_back(thirdPlaneLeftLeft);
         scene.push_back(thirdPlaneLeftRight);
         scene.push_back(thirdPlaneRightLeft);
         scene.push_back(thirdPlaneRightRight);
         update();
         return;
     }
     delete pointCloud;
}

//
// controls radio button clicks
//
void GLWidget::radioButtonClicked()
{
    // TODO: toggle to
    QMessageBox::warning(this, "Feature" ,"ups hier fehlt noch was");
    if (sender()) {
       QString      name = sender()->objectName();
       if (name=="radioButton_1") {};
       if (name=="radioButton_2") {};
       update();
    }
}

//
// controls check box clicks
//
void GLWidget::checkBoxClicked()
{
    QMessageBox::warning(this, "Feature" ,"ups hier fehlt noch was");
}

//
// controls spin box changes
//
void GLWidget::spinBoxValueChanged(int)
{
    QMessageBox::warning(this, "Feature" ,"ups hier fehlt noch was");
}

