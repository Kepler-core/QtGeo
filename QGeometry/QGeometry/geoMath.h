#pragma once
#include "Geometry.h"
//#include "geo_base.hpp"

/*����λ�ù�ϵ����*/

namespace gm
{

	using Rect = GeoExtent;  //�߽����

	int compare(double x, double y, double precision = 1e-6);  //�Ƚϣ�����float

	//����
	double cross(const GeoRawPoint& vec1Start, const GeoRawPoint& vec1End, const GeoRawPoint& vec2Start, const GeoRawPoint& vec2End);

	//��ת
	void rotate(double centerX, double centerY, double& x, double& y, double sinAngle, double cosAngle);
	void rotate(double centerX, double centerY, double& x, double& y, double angle);

	double distancePointToPoint(const GeoRawPoint& ptA, const GeoRawPoint& ptB);  //�㵽��ľ���
	bool isPointEqPoint(const GeoRawPoint& ptA, const GeoRawPoint& ptB, double precision = 2);  //�ж������Ƿ����

	//��������
	bool isPointOnLine(const GeoRawPoint& pt, const GeoRawPoint& lineStartPt, const GeoRawPoint& lineEndPt, double precision = 0.001);
	bool isPointOnLineString(const GeoRawPoint& pt, double halfEdge, GeoLineString* lineString);
	//bool isPointOnLineString(const GeoRawPoint& pt, double halfEdge, const GeoRawPoint& lineStartPt, const GeoRawPoint& lineEndPt);
	bool isPointOnLineString(const GeoRawPoint& pt, GeoLineString* lineString, double precision = 0.001);

	//�ж��Ƿ����
	bool isPointInLinearRing(const GeoRawPoint& pt, GeoLinearRing* ring, double precision = 0.001);  //��-��
	bool isPointInRect(const GeoRawPoint& point, const Rect& rect);  //��-����
	bool isPointInPolygon(const GeoRawPoint& pt, GeoPolygon* polygon, double precision = 0.001);  //��-��

	//�ж��Ƿ��ཻ
	//��-��
	bool isLineIntersect(const GeoRawPoint& line1Start, const GeoRawPoint& line1End, const GeoRawPoint& line2Start, const GeoRawPoint& line2End, double precision = 1e-6);
	bool isRectIntersect(const Rect& rect1, const Rect& rect2);  //����
	bool isLineStringRectIntersect(GeoLineString* lineString, const Rect& rect);  //��-��
	bool isPolygonRectIntersect(GeoPolygon* polygon, const Rect& rect);  //��-��

} // namespace gm
