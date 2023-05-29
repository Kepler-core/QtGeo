#pragma once
#include "geoBase.hpp"
#include "feature.h"

#include <vector>

/*դ����    ʹ��vector��Ҫ�ؽ��в���*/

class Grid 
{
public:
    //���캯��
    Grid(int id) : id(id) {}
    Grid(int id, const GeoExtent& extent) : id(id), extent(extent) {}

    int getId() const { return id; }
    const GeoExtent& getExtent() const { return extent; }   //��ȡ�������
    GeoFeature* getFeature(int idx) const { return featuresList[idx]; }   //��Ҫ���б��и����±��ȡָ��Ҫ��
    int getFeatureCount() const { return featuresList.size(); }   //ͳ��Ҫ�ظ���

    void setExtent(const GeoExtent& extentIn) { extent = extentIn; }
    void addFeature(GeoFeature* feature) { featuresList.push_back(feature); }   //���Ҫ��

    void adjustToFit() { featuresList.shrink_to_fit(); }   //���ȸ���Ҫ�ش�С���ٿռ䣬�洢Ҫ��

private:
    int id;
    GeoExtent extent;
    std::vector<GeoFeature*> featuresList;   //vector �洢Ҫ�ض���GeoFeature
};
