#pragma once
#include <cassert>  //断言
#include <vector>

#include"utility.h"
#include"qsharedmemory.h"
#include "geoBase.hpp"


/*几何类型的声明(参考OGC标准)*/
class GeoPoint;								//点
class GeoPolygon;							//面
class GeoLineString;						//线串(多(顶)点构成的连续线)
class GeoLinearRing;						//线环
class GeoMultiPoint;						//多点
class GeoMultiPolygon;						//多面
class GeoMultiLineString;					//多线


enum GeometryType  //集合类型枚举 
{
    kPoint = 0,
    kPolygon = 1,
    kLineString = 2,
    kLinearRing = 3,
    kMultiPoint = 4,
    kMultiPolygon = 5,
    kMultiLineString = 6,
    kGeometryCollection = 7,
    kGeometryTypeUnknown = 8
};


/*-----------------------------------几何基类（虚基类）---------------------------------*/
class GeoGeometry
{
public:
    GeoGeometry() {}
    virtual ~GeoGeometry();  //虚析构

    virtual GeoGeometry* copy() = 0;    // 深拷贝

    virtual GeometryType getGeometryType() const = 0;  //获取集合类型
    virtual const char* getGeometryName() const = 0;  //获取几何名
    virtual int getNumPoints() const = 0;   //获取点数
    virtual GeoExtent getExtent() const = 0;   //获取边界范围
    virtual bool isEmpty() const = 0;  //判空
    virtual void swapXY() = 0;   //坐标交换
    virtual void offset(double xOffset, double yOffset) = 0;  //坐标偏移
    virtual void rotate(double centerX, double centerY, double sinAngle, double cosAngle) = 0;  //绕某一中心点旋转
    void rotate(double centerX, double centerY, double angle);
    void rotate(double sinAngle, double cosAngle);
    void rotate(double angle);

    /* 构造子类（一种类型转换  父->子） */
    inline GeoPoint* toPoint() { return utils::down_cast<GeoPoint*>(this); }
    inline GeoLineString* toLineString() { return utils::down_cast<GeoLineString*>(this); }
    inline GeoLinearRing* toLinearRing() { return utils::down_cast<GeoLinearRing*>(this); }
    inline GeoPolygon* toPolygon() { return utils::down_cast<GeoPolygon*>(this); }
    inline GeoMultiPoint* toMultiPoint() { return utils::down_cast<GeoMultiPoint*>(this); }
    inline GeoMultiLineString* toMultiLineString() { return utils::down_cast<GeoMultiLineString*>(this); }
    inline GeoMultiPolygon* toMultiPolygon() { return utils::down_cast<GeoMultiPolygon*>(this); }
};


/*------------------------------------------点---------------------------------------*/
class GeoPoint : public GeoGeometry {
public:
    GeoPoint();    //f构造
    GeoPoint(double xx, double yy);
    GeoPoint(const GeoPoint& geoPt) = default;
    GeoPoint& operator=(const GeoPoint& geoPt) = delete;  //这里避免了未实现该函数而引发的错误
    ~GeoPoint() {}

public:
    GeoRawPoint getXY() const { return { x, y }; }
    double getX() const { return x; }
    double getY() const { return y; }

    void setXY(double xx, double yy) { x = xx; y = yy; }
    void setX(double xx) { x = xx; }
    void setY(double yy) { y = yy; }

    bool operator==(const GeoPoint& geoPt)
    {
        return utils::isEqual(x, geoPt.x) && utils::isEqual(y, geoPt.y);
    }

    //父类方法重写
public:
    virtual GeoGeometry* copy() override;
    virtual GeometryType getGeometryType() const override;
    virtual const char* getGeometryName() const override;
    virtual int getNumPoints() const override;
    virtual GeoExtent getExtent() const override;
    virtual bool isEmpty() const override;
    virtual void swapXY() override;
    virtual void offset(double xOffset, double yOffset) override;
    virtual void rotate(double /*centerX*/, double /*centerY*/,
        double /*sinAngle*/, double /*cosAngle*/) override {}

private:
    double x;
    double y;
};


/*----------------------------------------------线串---------------------------------------*/
class GeoLineString : public GeoGeometry {
public:
    GeoLineString() = default;
    GeoLineString(const GeoLineString& LineS);
    GeoLineString& operator=(const GeoLineString&) = delete;
    virtual ~GeoLineString() = default;

    //迭代器
public:
    std::vector<GeoRawPoint>::iterator begin()
    {
        return points.begin();
    }
    std::vector<GeoRawPoint>::iterator end()
    {
        return points.end();
    }

public:
    GeoRawPoint& operator[](int idx) //根据下标进行修改
    {
        return points[idx];
    }
    const GeoRawPoint& operator[](int idx) const   //根据下标获取
    {
        return points[idx];
    }

    //获取点坐标
    GeoRawPoint getXY(int idx) const { return { points[idx].x, points[idx].y }; }
    double getX(int idx) const { return points[idx].x; }
    double getY(int idx) const { return points[idx].y; }
    void  getPoint(int idx, GeoPoint* point) const;
    void  getRawPoint(int idx, GeoRawPoint* rawPoint) const;
    double* getRawData();      // 获取第一个点的x坐标地址

    // 设置点坐标
    void setPoint(int idx, double xx, double yy);
    void setPoint(int idx, GeoPoint* point);

    void removePoint(int idx);  //移动点
    void addPoint(const GeoRawPoint& rawPoint);  //添加点
    void addPoint(double xx, double yy);

    void reserveNumPoints(int count);   //开辟内存，存储点
    void adjustToFit() { points.shrink_to_fit(); }  //判断适合的内存(使容器达到相应的大小)

//重写父类方法
public:
    virtual GeoGeometry* copy() override;
    virtual GeometryType getGeometryType() const override;
    virtual const char* getGeometryName() const override;
    virtual GeoExtent getExtent() const override;
    virtual int getNumPoints() const override;
    virtual bool isEmpty() const override;
    virtual void swapXY() override;
    virtual void offset(double xOffset, double yOffset) override;
    virtual void rotate(double centerX, double centerY, double sinAngle, double cosAngle) override;

protected:
    std::vector<GeoRawPoint> points;
};


/*---------------------------------------线环------------------------------------*/
class GeoLinearRing : public GeoLineString
{
public:
    GeoLinearRing() = default;
    GeoLinearRing(const GeoLinearRing&);
    GeoLinearRing& operator=(const GeoLinearRing&) = delete;
    virtual ~GeoLinearRing() = default;

public:
    bool isClockwise() const;  //判断是否为顺时针方向
    void closeRings();
    inline GeoLineString* toLineString() { return this; }

    //重写
public:
    virtual GeoGeometry* copy() override;
    virtual GeometryType getGeometryType() const override;
    virtual const char* getGeometryName() const override;
};


/*-----------------------面(由线环组成  外环+内环)----------------------*/
class GeoPolygon : public GeoGeometry {
public:
    GeoPolygon() = default;
    GeoPolygon(const GeoPolygon& rhs);
    GeoPolygon& operator=(const GeoPolygon& rhs) = delete;
    virtual ~GeoPolygon();

public:
    void reserveInteriorRingsCount(int size);  //按内环数量开辟空间，进行存储
    int getInteriorRingsCount() const { return rings.size() - 1; }  //对内环计数
    GeoLinearRing* getExteriorRing() const;   //获取外环
    GeoLinearRing* getInteriorRing(int idx) const;   //根据下标获取内环

    void getRawData(double** rawData) const;   // 获取第一个点的x坐标地址

    void setExteriorRing(GeoLinearRing* ring);
    void addInteriorRing(GeoLinearRing* ring);  //增加内环
    void removeInteriorRing(int idx);   //删除内环

    void adjustToFit() { rings.shrink_to_fit(); }

    //重写
public:
    virtual GeoGeometry* copy() override;
    virtual GeometryType getGeometryType() const override;
    virtual const char* getGeometryName() const override;
    virtual GeoExtent getExtent() const override;
    virtual int getNumPoints() const override;
    virtual bool isEmpty() const override;
    virtual void swapXY() override;
    virtual void offset(double xOffset, double yOffset) override;
    virtual void rotate(double centerX, double centerY, double sinAngle, double cosAngle) override;

private:
    // rings[0]: exterior ring
    // rings[n]: interior ring(n >= 0)
    std::vector<GeoLinearRing*> rings;
};


/**************************************************/
/*                                                */
/*            GeoGeometryCollection               */
/*                                                */
/**************************************************/
class GeoGeometryCollection : public GeoGeometry
{
public:
    GeoGeometryCollection() = default;
    GeoGeometryCollection(const GeoGeometryCollection& rhs);
    GeoGeometryCollection& operator=(const GeoGeometryCollection&) = delete;
    virtual ~GeoGeometryCollection();

public:
    std::vector<GeoGeometry*>::iterator begin()
    {
        return geoms.begin();
    }
    std::vector<GeoGeometry*>::iterator end()
    {
        return geoms.end();
    }

    GeoGeometry* getGeometry(int idx) const { return geoms[idx]; }
    int getNumGeometries() const { return geoms.size(); }

    void addGeometry(GeoGeometry* geom);
    void removeGeometry(int idx);

    void reserveNumGeoms(int idx) { geoms.reserve(idx); }
    void adjustToFit() { geoms.shrink_to_fit(); }

    /* override */
public:
    virtual GeoGeometry* copy() override = 0;
    virtual GeometryType getGeometryType() const override = 0;
    virtual const char* getGeometryName() const override = 0;
    virtual GeoExtent getExtent() const override;
    virtual int getNumPoints() const override;
    virtual bool isEmpty() const override;
    virtual void swapXY() override;
    virtual void offset(double xOffset, double yOffset) override;
    virtual void rotate(double centerX, double centerY, double sinAngle, double cosAngle) override;

protected:
    std::vector<GeoGeometry*> geoms;
};


/*------------------------------------------------多点----------------------------------------------------*/
class GeoMultiPoint : public GeoGeometryCollection
{
public:
    GeoMultiPoint() = default;
    GeoMultiPoint(const GeoMultiPoint&);
    GeoMultiPoint& operator=(const GeoMultiPoint&) = delete;
    ~GeoMultiPoint() = default;

    GeoPoint* getPoint(int idx) const { return geoms[idx]->toPoint(); }
    void addPoint(GeoPoint* point) { addGeometry(point); }

    /* override */
public:
    virtual GeoGeometry* copy() override;
    virtual GeometryType getGeometryType() const override;
    virtual const char* getGeometryName() const override;
};


/*------------------------------------------多线-------------------------------------*/
class GeoMultiLineString : public GeoGeometryCollection
{
public:
    GeoMultiLineString() = default;
    GeoMultiLineString(const GeoMultiLineString& rhs);
    GeoMultiLineString& operator=(const GeoMultiLineString&) = delete;
    virtual ~GeoMultiLineString() = default;

public:
    GeoLineString* getLineString(int idx) const
    {
        return geoms[idx]->toLineString();
    }
    void addLineString(GeoLineString* lineString)
    {
        addGeometry(lineString);
    }

    //重写
public:
    virtual GeoGeometry* copy() override;
    virtual GeometryType getGeometryType() const override;
    virtual const char* getGeometryName() const override;
};


/*-------------------------------------多面---------------------------------------------*/
class GeoMultiPolygon : public GeoGeometryCollection
{
public:
    GeoMultiPolygon() = default;
    GeoMultiPolygon(const GeoMultiPolygon& rhs);
    GeoMultiPolygon& operator=(const GeoMultiPolygon&) = delete;
    ~GeoMultiPolygon() = default;

public:
    GeoPolygon* getPolygon(int idx) const { return geoms[idx]->toPolygon(); }
    int getNumLinearRings() const;
    void addPolygon(GeoPolygon* polygon) { addGeometry(polygon); }

    //重写
public:
    virtual GeoGeometry* copy() override;
    virtual GeometryType getGeometryType() const override;
    virtual const char* getGeometryName() const override;
};

