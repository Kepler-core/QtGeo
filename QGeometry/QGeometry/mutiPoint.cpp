#include "Geometry.h"

GeoMultiPoint::GeoMultiPoint(const GeoMultiPoint& rhs) : GeoGeometryCollection(rhs) {}

GeoGeometry* GeoMultiPoint::copy() //拷贝
{
    return new GeoMultiPoint(*this);
}

GeometryType GeoMultiPoint::getGeometryType() const  //获取几何类型
{
    return kMultiPoint;
}

const char* GeoMultiPoint::getGeometryName() const  //几何名
{
    return "MULTIPOINT";
}