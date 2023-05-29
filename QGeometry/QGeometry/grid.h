#pragma once
#include "geoBase.hpp"
#include "feature.h"

#include <vector>

/*栅格类    使用vector对要素进行操作*/

class Grid 
{
public:
    //构造函数
    Grid(int id) : id(id) {}
    Grid(int id, const GeoExtent& extent) : id(id), extent(extent) {}

    int getId() const { return id; }
    const GeoExtent& getExtent() const { return extent; }   //获取外包矩形
    GeoFeature* getFeature(int idx) const { return featuresList[idx]; }   //在要素列表中根据下标获取指定要素
    int getFeatureCount() const { return featuresList.size(); }   //统计要素个数

    void setExtent(const GeoExtent& extentIn) { extent = extentIn; }
    void addFeature(GeoFeature* feature) { featuresList.push_back(feature); }   //添加要素

    void adjustToFit() { featuresList.shrink_to_fit(); }   //事先根据要素大小开辟空间，存储要素

private:
    int id;
    GeoExtent extent;
    std::vector<GeoFeature*> featuresList;   //vector 存储要素对象GeoFeature
};
