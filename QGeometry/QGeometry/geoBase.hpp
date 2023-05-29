#pragma once
#include "utility.h"

class GeoRawPoint  //ԭʼ��
{
public:
	GeoRawPoint() : x(0.0), y(0.0) {}  //���캯��
	GeoRawPoint(double xx, double yy) : x(xx), y(yy) {}
	bool operator==(const GeoRawPoint& rawPt)  //����==
	{
		return utils::isEqual(x, rawPt.x) && utils::isEqual(y, rawPt.y);
	}
	double x;
	double y;
};


class GeoExtent //�߽�
{
public:
	//���캯��
	GeoExtent()
		: minX(0.0), maxX(0.0), minY(0.0), maxY(0.0) {}
	GeoExtent(double xx, double yy)
		: minX(xx), maxX(xx), minY(yy), maxY(yy) {}
	GeoExtent(const GeoRawPoint& rawPt)
		: minX(rawPt.x), maxX(rawPt.x), minY(rawPt.y), maxY(rawPt.y) {}
	GeoExtent(const GeoRawPoint& leftTop, const GeoRawPoint rightBottom)  //���Ͻ�+���½�
		: minX(leftTop.x), maxX(rightBottom.x), minY(rightBottom.y), maxY(leftTop.y) {}
	GeoExtent(double minXIn, double maxXIn, double minYIn, double maxYIn) :
		minX(minXIn), maxX(maxXIn), minY(minYIn), maxY(maxYIn) {}

	//����߽�
	double centerX() const { return (maxX + minX) / 2; }  //���ĵ�
	double centerY() const { return (maxY + minY) / 2; }
	double width()	 const { return maxX - minX; }    //�߽���ο���
	double height()  const { return maxY - minY; }
	double aspectRatio() const { return (maxX - minX) / (maxY - minY); }    //��߱�
	GeoRawPoint center() const { return GeoRawPoint((maxX + minX) / 2, (maxY + minY) / 2); }  //���ģ�����һ���㣩

	//��߽������صĺ���
	GeoExtent operator+(const GeoExtent& geoEx);  //�����µı߽�
	GeoExtent& operator+=(const GeoExtent& geoEx);  //���µı߽�ϲ�
	void merge(const GeoExtent& geoEx); //�ϲ�
	void merge(double xx, double yy);
	void offsetX(double offset);  //ƽ��
	void offsetY(double offset);
	void offset(double xOffset, double yOffset);
	bool isIntersect(const GeoExtent& geoEx) const;  //�ж����߽��Ƿ��ཻ
	void intersect(const GeoExtent& geoEx);  //��������߽��ཻ������ཻ�Ĳ���
	bool contain(const GeoRawPoint& pt) const;  //�жϵ��Ƿ��ڱ߽���
	bool contain(double xx, double yy) const;
	void normalize(); //ȷ���㰴��ȷ�Ĵ�С���м���

public:
	double minX;
	double maxX;
	double minY;
	double maxY;
};

GeoExtent GeoExtent::operator+(const GeoExtent& geoEx)  //�����µı߽�
{
	GeoExtent extent;
	extent.minX = MIN(minX, geoEx.minX);
	extent.maxX = MAX(maxX, geoEx.maxX);
	extent.minY = MIN(minY, geoEx.minY);
	extent.maxY = MAX(maxY, geoEx.maxY);
	return extent;
}

GeoExtent& GeoExtent::operator+=(const GeoExtent& geoEx) //����+=
{
	merge(geoEx);
	return *this;
}

void GeoExtent::merge(const GeoExtent& geoEx) //�ϲ�
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

//ƽ��
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

bool GeoExtent::isIntersect(const GeoExtent& geoEx) const  //�ж����߽��Ƿ��ཻ
{
	return minX <= geoEx.maxX && maxX >= geoEx.minX &&
		minY <= geoEx.maxY && maxY >= geoEx.minY;
}

void GeoExtent::intersect(const GeoExtent& geoEx)  //��������߽��ཻ������ཻ�Ĳ���
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

//�жϵ��Ƿ�����ڱ߽���
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

void GeoExtent::normalize() //ȷ���㰴��ȷ�Ĵ�С���м���
{

	if (minX > maxX)
		std::swap(minX, maxX);
	if (minY > maxY)
		std::swap(minY, maxY);
}