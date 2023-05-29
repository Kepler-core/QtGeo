#pragma once
#include "geoBase.hpp"
#include "feature.h"

#include <vector>

/*�ռ�����   ͨ�����ĵ�/�߽��ѯҪ�� */

class SpatialIndex
{
public:
    SpatialIndex() {}
    virtual ~SpatialIndex() {};

    //halfEdge:�߽��е�   x,y:���ĵ�
    virtual void queryFeature(double x, double y, double halfEdge, GeoFeature*& featureResult) = 0;
    virtual void queryFeatures(const GeoExtent& extent, std::vector<GeoFeature*>& featuresResult) = 0;
};
