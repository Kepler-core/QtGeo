#pragma once
#include "grid.h"
#include "spatialindex.h"


class GridIndex : public SpatialIndex 
{
public:
    GridIndex();
    ~GridIndex();

    //栅格操作  统计，添加，清除
    void reserve(int numGrids) { grids.reserve(numGrids); }  //统计
    void addGrid(Grid* grid) { grids.push_back(grid); }
    int getNumGrids() const { return grids.size(); }
    void clear();

    // 按条件查询
    void queryGrids(double x, double y, Grid*& gridResult);   //查询包含点x,y的
    void queryGrids(const GeoExtent& extent, std::vector<Grid*>& gridsResult);   //查询被指定边界包含的

    //重写
    void queryFeature(double x, double y, double halfEdge, GeoFeature*& featureResult) override;
    void queryFeatures(const GeoExtent& extent, std::vector<GeoFeature*>& featuresResult) override;

private:
    std::vector<Grid*> grids;
};

