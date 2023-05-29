#pragma once
#include "grid.h"
#include "spatialindex.h"


class GridIndex : public SpatialIndex 
{
public:
    GridIndex();
    ~GridIndex();

    //դ�����  ͳ�ƣ���ӣ����
    void reserve(int numGrids) { grids.reserve(numGrids); }  //ͳ��
    void addGrid(Grid* grid) { grids.push_back(grid); }
    int getNumGrids() const { return grids.size(); }
    void clear();

    // ��������ѯ
    void queryGrids(double x, double y, Grid*& gridResult);   //��ѯ������x,y��
    void queryGrids(const GeoExtent& extent, std::vector<Grid*>& gridsResult);   //��ѯ��ָ���߽������

    //��д
    void queryFeature(double x, double y, double halfEdge, GeoFeature*& featureResult) override;
    void queryFeatures(const GeoExtent& extent, std::vector<GeoFeature*>& featuresResult) override;

private:
    std::vector<Grid*> grids;
};

