#pragma once
#include "Geometry.h"
#include "field.h"

#include <vector>
#include <QColor>

/*要素类*/

class GeoFeatureLayer;   //几何要素
class OpenglFeatureDescriptor;   //opengl要素

class GeoFeature
{
public:
    //构造几何要素
    GeoFeature() {};  // 默认构造
    GeoFeature(GeoFeatureLayer* layerParent);  //通过父图层构造
    GeoFeature(int nFID, GeoFeatureLayer* layerParent);
    GeoFeature(std::vector<GeoFieldDefn*>* fieldDefnsIn);  //通过字段
    GeoFeature(int nFID, std::vector<GeoFieldDefn*>* fieldDefnsIn);
    GeoFeature(const GeoFeature& rhs, std::vector<GeoFieldDefn*>* fieldDefnsIn);
    ~GeoFeature();

    //几何相关操作
    void setGeometry(GeoGeometry* geomIn);
    GeoGeometry* getGeometry() const { return geom; }
    GeometryType getGeometryType() const;  //获取类型(用Layer中的方法)
    void offset(double xOffset, double yOffset);
    void rotate(double angle);
    void rotate(double sinAngle, double cosAngle);
    void rotate(double centerX, double centerY, double angle);
    void rotate(double centerX, double centerY, double sinAngle, double cosAngle);

    //边界（最小外包矩形）
    void updateExtent() { extent = geom->getExtent(); }
    const GeoExtent& getExtent() const { return extent; }

    //字段操作
    void initNewFieldValue();   //初始化字段值
    template<typename T>
    bool getField(QString name, T* outValue) const   //获取字段值(通过字段名)
    {
        return getField(getFieldIndexByName(name), outValue);
    }

    template<typename T>
    bool getField(int idx, T* outValue) const  //获取字段值(通过字段id)
    {
        *outValue = *(T*)fieldValues[idx];
        return true;
    }

    template<typename T>
    void setField(int idx, T valueIn)   //设置字段值(通过字段id)
    {
        initNewFieldValue();
        *(T*)(fieldValues[idx]) = valueIn;
    }

    template<typename T>
    void setField(QString name, T valueIn) {   //设置字段值(通过字段名)
        setField(getFieldIndexByName(name), valueIn);
    }

    int getFID() const { return nFID; }  //字段ID
    void setFID(int nFIDIn) { nFID = nFIDIn; }

    int getNumFields() const { return (*fieldDefns).size(); }   //获取字段数
    QString getFieldName(int idx) const;
    GeoFieldType getFieldType(int idx) const;
    GeoFieldType getFieldType(const QString& name) const;

    bool isFieldExist(const QString& fieldName, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;  //判断字段是否存在(区分大小写)
    bool isFieldExistLike(const QString& fieldName, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;
    int getFieldIndexByName(const QString& name) const;   //获取ID

//屏幕绘制(opengl相关)
    void setOpenglFeatureDescriptor(OpenglFeatureDescriptor* desc);

    void Draw() const;
    void HighlightDraw() const;  //高亮显示(选择要素时)

    // 选择要素
    bool isDeleted() const { return deleted; }
    bool isSelected() const { return selected; }
    void setDeleted(bool b) { deleted = b; }
    void setSelected(bool b) { selected = b; }

    // 设置&获取颜色   点，线，面
    void setColor(unsigned int colorIn, bool bUpdate = false);
    void setColor(int r, int g, int b, bool bUpdate = false);
    void getColorF(float& r, float& g, float& b);

    // 边界颜色  面
    void setBorderColor(int colorIn, bool bUpdate = false);
    void setBorderColor(int r, int g, int b, bool bUpdate = false);
    //void getBorderColorF(float& r, float& g, float& b);

private:
    bool checkFieldName(const QString& name) const;
    void setColor_(float r, float g, float b);
    void setBorderColor_(float r, float g, float b);

private:
    int nFID = 0;  //字段id
    GeoExtent extent;  //边界
    GeoGeometry* geom = nullptr;   //几何类

    /* Field defination
    ** There is only one defination in one layer.
    ** And each features in the layer just holds a pointer of the defination */
    std::vector<GeoFieldDefn*>* fieldDefns;   //字段定义
    std::vector<void*> fieldValues;    //保存字段值  设置为void，根据字段获取字段类型

    OpenglFeatureDescriptor* openglFeatureDesc = nullptr;   //opengl绘制

    bool selected = false;  //标识  选择要素
    bool deleted = false;

    //颜色
    QRgb color = utils::getRandomColor();
    QRgb borderColor = Qt::black;  //面边界颜色
};