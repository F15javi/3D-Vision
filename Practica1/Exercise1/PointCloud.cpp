//
// (c) Georg Umlauf, 2022
//
#include "PointCloud.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>

#include "GLConvenience.h"
#include "QtConvenience.h"

using namespace std;

PointCloud::PointCloud()
{
    type      = SceneObjectType::ST_POINT_CLOUD;
    pointSize = 3.0f;
}

PointCloud::~PointCloud()
{}

bool PointCloud::loadPLY(const QString& filePath)
{
    // open stream
    fstream is;
    is.open(filePath.toStdString().c_str(), fstream::in);

    // ensure format with magic header
    string line;
    getline(is, line);
    if (line != "ply") throw runtime_error("not a ply file");

    // parse header looking only for 'element vertex' section size
    unsigned pointsCount = 0;
    while (is.good()) {
        getline(is, line);
        if (line == "end_header") {
            break;
        } else {
            stringstream ss(line);
            string tag1, tag2, tag3;
            ss >> tag1 >> tag2 >> tag3;
            if (tag1 == "element" && tag2 == "vertex") {
                pointsCount = unsigned(atoi(tag3.c_str()));
            }
        }
    }

    // read and parse 'element vertex' section
    if (pointsCount > 0) {
        this->resize(pointsCount);
        float m = float(INT_MAX);
        pointsBoundMin = QVector3D(m,m,m);
        pointsBoundMax = -pointsBoundMin;

        stringstream ss;
        string line;
        QVector4D *p = this->data();
        for (size_t i = 0; is.good() && i < pointsCount; ++i) {
            getline(is, line);
            ss.str(line);
            float x, y, z;
            ss >> x >> y >> z;

            *p++ = QVector4D(x, y, z, 1.0);

            // updates for AABB
            pointsBoundMax[0] = max(x, pointsBoundMax[0]);
            pointsBoundMax[1] = max(y, pointsBoundMax[1]);
            pointsBoundMax[2] = max(z, pointsBoundMax[2]);
            pointsBoundMin[0] = min(x, pointsBoundMin[0]);
            pointsBoundMin[1] = min(y, pointsBoundMin[1]);
            pointsBoundMin[2] = min(z, pointsBoundMin[2]);
        }

        // basic validation
        if (p - this->data() < size()) throw runtime_error("broken ply file");

        cout << "number of points: " + to_string(pointsCount) << endl;

        // rescale data
        float a,s=0;
        for (int i=0; i<3;i++) {
            a = pointsBoundMax[i]-pointsBoundMin[i];
            s+= a*a;
        }
        s = sqrt(s)/pointCloudScale;
        for (int i=0; i < size(); i++) { (*this)[i]/=s; (*this)[i][3] = 1.0; }
    }
    return true;
}

void PointCloud::setPointSize(unsigned _pointSize)
{
    pointSize = _pointSize;
}

void PointCloud::affineMap(const QMatrix4x4& M)
{
    for (unsigned i = 0; i < size(); ++i) {
        (*this)[i] = M.map((*this)[i]);
    }
}

void PointCloud::draw(const RenderCamera& camera, const QColor& color, float ) const
{
    camera.renderPCL((*this),color,pointSize);
}
