#pragma once
#include "utility.h"

class GeoRawPoint  //原始点
{
public:
	GeoRawPoint() : x(0.0), y(0.0) {}  //构造函数
	GeoRawPoint(double xx, double yy) : x(xx), y(yy) {}
	bool operator==(const GeoRawPoint& rawPt)  //重载==
	{
		return utils::isEqual(x, rawPt.x) && utils::isEqual(y, rawPt.y);
	}
	double x;
	double y;
};


class GeoExtent //边界
{
public:
	//构造函数
	GeoExtent()
		: minX(0.0), maxX(0.0), minY(0.0), maxY(0.0) {}
	GeoExtent(double xx, double yy)
		: minX(xx), maxX(xx), minY(yy), maxY(yy) {}
	GeoExtent(const GeoRawPoint& rawPt)
		: minX(rawPt.x), maxX(rawPt.x), minY(rawPt.y), maxY(rawPt.y) {}
	GeoExtent(const GeoRawPoint& leftTop, const GeoRawPoint rightBottom)  //左上角+右下角
		: minX(leftTop.x), maxX(rightBottom.x), minY(rightBottom.y), maxY(leftTop.y) {}
	GeoExtent(double minXIn, double maxXIn, double minYIn, double maxYIn) :
		minX(minXIn), maxX(maxXIn), minY(minYIn), maxY(maxYIn) {}

	//计算边界
	double centerX() const { return (maxX + minX) / 2; }  //中心点
	double centerY() const { return (maxY + minY) / 2; }
	double width()	 const { return maxX - minX; }    //边界矩形宽，高
	double height()  const { return maxY - minY; }
	double aspectRatio() const { return (maxX - minX) / (maxY - minY); }    //宽高比
	GeoRawPoint center() const { return GeoRawPoint((maxX + minX) / 2, (maxY + minY) / 2); }  //中心（返回一个点）

	//与边界操作相关的函数
	GeoExtent operator+(const GeoExtent& geoEx);  //加入新的边界
	GeoExtent& operator+=(const GeoExtent& geoEx);  //与新的边界合并
	void merge(const GeoExtent& geoEx); //合并
	void merge(double xx, double yy);
	void offsetX(double offset);  //平移
	void offsetY(double offset);
	void offset(double xOffset, double yOffset);
	bool isIntersect(const GeoExtent& geoEx) const;  //判断两边界是否相交
	void intersect(const GeoExtent& geoEx);  //如果两个边界相交，求出相交的部分
	bool contain(const GeoRawPoint& pt) const;  //判断点是否在边界内
	bool contain(double xx, double yy) const;
	void normalize(); //确保点按正确的大小进行计算

public:
	double minX;
	double maxX;
	double minY;
	double maxY;
};

GeoExtent GeoExtent::operator+(const GeoExtent& geoEx)  //加入新的边界
{
	GeoExtent extent;
	extent.minX = MIN(minX, geoEx.minX);
	extent.maxX = MAX(maxX, geoEx.maxX);
	extent.minY = MIN(minY, geoEx.minY);
	extent.maxY = MAX(maxY, geoEx.maxY);
	return extent;
}

GeoExtent& GeoExtent::operator+=(const GeoExtent& geoEx) //重载+=
{
	merge(geoEx);
	return *this;
}

void GeoExtent::merge(const GeoExtent& geoEx) //合并
{
	minX = MIN(minX, geoEx.minX);
	minY = MIN(minY, geoEx.minY);
	maxX = MAX(maxX, geoEx.maxX);
	maxY = MAX(maxY, geoEx.maxY);
}
void GeoExtent::merge(double xx, double yy)
{
	minX = MIN(minX, xx);
	minY = MIN(minY, yy);
	maxX = MAX(maxX, xx);
	maxY = MAX(maxY, yy);
}

//平移
void GeoExtent::offsetX(double offset)
{
	minX += offset;
	maxX += offset;
}
void GeoExtent::offsetY(double offset)
{
	minY += offset;
	maxY += offset;
}
void GeoExtent::offset(double xOffset, double yOffset)
{
	minX += xOffset;
	maxX += xOffset;
	minY += yOffset;
	maxY += yOffset;
}

bool GeoExtent::isIntersect(const GeoExtent& geoEx) const  //判断两边界是否相交
{
	return minX <= geoEx.maxX && maxX >= geoEx.minX &&
		minY <= geoEx.maxY && maxY >= geoEx.minY;
}

void GeoExtent::intersect(const GeoExtent& geoEx)  //如果两个边界相交，求出相交的部分
{
	if (isIntersect(geoEx))
	{
		minX = MAX(minX, geoEx.minX);
		minY = MAX(minY, geoEx.minY);
		maxX = MIN(maxX, geoEx.maxX);
		maxY = MIN(maxY, geoEx.maxY);
	}
	else
		*this = GeoExtent();
}

//判断点是否包含在边界内
bool GeoExtent::contain(const GeoRawPoint& pt) const
{
	return pt.x >= minX && pt.x <= maxX
		&& pt.y >= minY && pt.y <= maxY;
}
bool GeoExtent::contain(double xx, double yy) const
{
	return xx >= minX && xx <= maxX
		&& yy >= minY && yy <= maxY;
}

void GeoExtent::normalize() //确保点按正确的大小进行计算
{

	if (minX > maxX)
		std::swap(minX, maxX);
	if (minY > maxY)
		std::swap(minY, maxY);
}