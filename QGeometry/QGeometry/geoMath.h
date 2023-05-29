#pragma once
#include "Geometry.h"
//#include "geo_base.hpp"

/*几何位置关系计算*/

namespace gm
{

	using Rect = GeoExtent;  //边界矩形

	int compare(double x, double y, double precision = 1e-6);  //比较，但是float

	//两线
	double cross(const GeoRawPoint& vec1Start, const GeoRawPoint& vec1End, const GeoRawPoint& vec2Start, const GeoRawPoint& vec2End);

	//旋转
	void rotate(double centerX, double centerY, double& x, double& y, double sinAngle, double cosAngle);
	void rotate(double centerX, double centerY, double& x, double& y, double angle);

	double distancePointToPoint(const GeoRawPoint& ptA, const GeoRawPoint& ptB);  //点到点的距离
	bool isPointEqPoint(const GeoRawPoint& ptA, const GeoRawPoint& ptB, double precision = 2);  //判断两点是否相等

	//点在线上
	bool isPointOnLine(const GeoRawPoint& pt, const GeoRawPoint& lineStartPt, const GeoRawPoint& lineEndPt, double precision = 0.001);
	bool isPointOnLineString(const GeoRawPoint& pt, double halfEdge, GeoLineString* lineString);
	//bool isPointOnLineString(const GeoRawPoint& pt, double halfEdge, const GeoRawPoint& lineStartPt, const GeoRawPoint& lineEndPt);
	bool isPointOnLineString(const GeoRawPoint& pt, GeoLineString* lineString, double precision = 0.001);

	//判断是否包含
	bool isPointInLinearRing(const GeoRawPoint& pt, GeoLinearRing* ring, double precision = 0.001);  //点-线
	bool isPointInRect(const GeoRawPoint& point, const Rect& rect);  //点-矩形
	bool isPointInPolygon(const GeoRawPoint& pt, GeoPolygon* polygon, double precision = 0.001);  //面-面

	//判断是否相交
	//线-线
	bool isLineIntersect(const GeoRawPoint& line1Start, const GeoRawPoint& line1End, const GeoRawPoint& line2Start, const GeoRawPoint& line2End, double precision = 1e-6);
	bool isRectIntersect(const Rect& rect1, const Rect& rect2);  //矩形
	bool isLineStringRectIntersect(GeoLineString* lineString, const Rect& rect);  //线-面
	bool isPolygonRectIntersect(GeoPolygon* polygon, const Rect& rect);  //面-面

} // namespace gm
