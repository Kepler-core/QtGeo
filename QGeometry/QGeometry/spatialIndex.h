#pragma once
#include "geoBase.hpp"
#include "feature.h"

#include <vector>

/*空间索引   通过中心点/边界查询要素 */

class SpatialIndex
{
public:
    SpatialIndex() {}
    virtual ~SpatialIndex() {};

    //halfEdge:边界中点   x,y:中心点
    virtual void queryFeature(double x, double y, double halfEdge, GeoFeature*& featureResult) = 0;
    virtual void queryFeatures(const GeoExtent& extent, std::vector<GeoFeature*>& featuresResult) = 0;
};
