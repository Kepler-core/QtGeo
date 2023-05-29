#include "Geometry.h"
#include"geoMath.h"

GeoLineString::GeoLineString(const GeoLineString& geoLS) :points(geoLS.points) {}  //���캯������ʼ��

GeoGeometry* GeoLineString::copy()
{
    return (new GeoLineString(*this));
}

void GeoLineString::getPoint(int idx, GeoPoint* point) const  //ȡ��
{
    point->setX(points[idx].x);
    point->setY(points[idx].y);
}

void GeoLineString::getRawPoint(int idx, GeoRawPoint* rawPoint) const
{
    rawPoint->x = points[idx].x;
    rawPoint->y = points[idx].y;
}

double* GeoLineString::getRawData()
{
    if (points.empty())
        return nullptr;
    else
        return &(points[0].x);  //��һ�����x��ַ
}

void GeoLineString::removePoint(int idx)
{
    points.erase(points.begin() + idx);  //ɾ����
}

void GeoLineString::setPoint(int idx, double xx, double yy)  //���õ�
{
    this->points[idx].x = xx;
    this->points[idx].y = yy;
}

void GeoLineString::setPoint(int idx, GeoPoint* point)
{
    setPoint(idx, point->getX(), point->getY());
}

void GeoLineString::addPoint(double xx, double yy)  //����
{
    this->points.emplace_back(xx, yy);
}

void GeoLineString::addPoint(const GeoRawPoint& rawPoint)
{
    this->points.emplace_back(rawPoint);
}

void GeoLineString::reserveNumPoints(int count)  //�洢
{
    this->points.reserve(count);
}


//��д����
GeometryType GeoLineString::getGeometryType() const
{
    return kLineString;
}

const char* GeoLineString::getGeometryName() const
{
    return "LINESTRING";
}

int GeoLineString::getNumPoints() const
{
    return points.size();
}

GeoExtent GeoLineString::getExtent() const  //�߽��ȡ
{
    if (isEmpty())
        return GeoExtent();

    GeoExtent extentOut(points[0]);

    int count = points.size();
    for (int i = 1; i < count; ++i) {
        extentOut.merge(points[i]);
    }

    return extentOut;
}

bool GeoLineString::isEmpty() const
{
    return points.empty();
}

void GeoLineString::swapXY()
{
    for (auto& point : points) {
        std::swap(point.x, point.y);
    }
}

void GeoLineString::offset(double xOffset, double yOffset) {
    for (auto& point : points) {
        point.x += xOffset;
        point.y += yOffset;
    }
}

void GeoLineString::rotate(double centerX, double centerY, double sinAngle, double cosAngle) {
    for (auto& point : points)
    {
        gm::rotate(centerX, centerY, point.x, point.y, sinAngle, cosAngle);
    }
}