#pragma once
#include "Geometry.h"
#include "field.h"

#include <vector>
#include <QColor>

/*Ҫ����*/

class GeoFeatureLayer;   //����Ҫ��
class OpenglFeatureDescriptor;   //openglҪ��

class GeoFeature
{
public:
    //���켸��Ҫ��
    GeoFeature() {};  // Ĭ�Ϲ���
    GeoFeature(GeoFeatureLayer* layerParent);  //ͨ����ͼ�㹹��
    GeoFeature(int nFID, GeoFeatureLayer* layerParent);
    GeoFeature(std::vector<GeoFieldDefn*>* fieldDefnsIn);  //ͨ���ֶ�
    GeoFeature(int nFID, std::vector<GeoFieldDefn*>* fieldDefnsIn);
    GeoFeature(const GeoFeature& rhs, std::vector<GeoFieldDefn*>* fieldDefnsIn);
    ~GeoFeature();

    //������ز���
    void setGeometry(GeoGeometry* geomIn);
    GeoGeometry* getGeometry() const { return geom; }
    GeometryType getGeometryType() const;  //��ȡ����(��Layer�еķ���)
    void offset(double xOffset, double yOffset);
    void rotate(double angle);
    void rotate(double sinAngle, double cosAngle);
    void rotate(double centerX, double centerY, double angle);
    void rotate(double centerX, double centerY, double sinAngle, double cosAngle);

    //�߽磨��С������Σ�
    void updateExtent() { extent = geom->getExtent(); }
    const GeoExtent& getExtent() const { return extent; }

    //�ֶβ���
    void initNewFieldValue();   //��ʼ���ֶ�ֵ
    template<typename T>
    bool getField(QString name, T* outValue) const   //��ȡ�ֶ�ֵ(ͨ���ֶ���)
    {
        return getField(getFieldIndexByName(name), outValue);
    }

    template<typename T>
    bool getField(int idx, T* outValue) const  //��ȡ�ֶ�ֵ(ͨ���ֶ�id)
    {
        *outValue = *(T*)fieldValues[idx];
        return true;
    }

    template<typename T>
    void setField(int idx, T valueIn)   //�����ֶ�ֵ(ͨ���ֶ�id)
    {
        initNewFieldValue();
        *(T*)(fieldValues[idx]) = valueIn;
    }

    template<typename T>
    void setField(QString name, T valueIn) {   //�����ֶ�ֵ(ͨ���ֶ���)
        setField(getFieldIndexByName(name), valueIn);
    }

    int getFID() const { return nFID; }  //�ֶ�ID
    void setFID(int nFIDIn) { nFID = nFIDIn; }

    int getNumFields() const { return (*fieldDefns).size(); }   //��ȡ�ֶ���
    QString getFieldName(int idx) const;
    GeoFieldType getFieldType(int idx) const;
    GeoFieldType getFieldType(const QString& name) const;

    bool isFieldExist(const QString& fieldName, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;  //�ж��ֶ��Ƿ����(���ִ�Сд)
    bool isFieldExistLike(const QString& fieldName, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;
    int getFieldIndexByName(const QString& name) const;   //��ȡID

//��Ļ����(opengl���)
    void setOpenglFeatureDescriptor(OpenglFeatureDescriptor* desc);

    void Draw() const;
    void HighlightDraw() const;  //������ʾ(ѡ��Ҫ��ʱ)

    // ѡ��Ҫ��
    bool isDeleted() const { return deleted; }
    bool isSelected() const { return selected; }
    void setDeleted(bool b) { deleted = b; }
    void setSelected(bool b) { selected = b; }

    // ����&��ȡ��ɫ   �㣬�ߣ���
    void setColor(unsigned int colorIn, bool bUpdate = false);
    void setColor(int r, int g, int b, bool bUpdate = false);
    void getColorF(float& r, float& g, float& b);

    // �߽���ɫ  ��
    void setBorderColor(int colorIn, bool bUpdate = false);
    void setBorderColor(int r, int g, int b, bool bUpdate = false);
    //void getBorderColorF(float& r, float& g, float& b);

private:
    bool checkFieldName(const QString& name) const;
    void setColor_(float r, float g, float b);
    void setBorderColor_(float r, float g, float b);

private:
    int nFID = 0;  //�ֶ�id
    GeoExtent extent;  //�߽�
    GeoGeometry* geom = nullptr;   //������

    /* Field defination
    ** There is only one defination in one layer.
    ** And each features in the layer just holds a pointer of the defination */
    std::vector<GeoFieldDefn*>* fieldDefns;   //�ֶζ���
    std::vector<void*> fieldValues;    //�����ֶ�ֵ  ����Ϊvoid�������ֶλ�ȡ�ֶ�����

    OpenglFeatureDescriptor* openglFeatureDesc = nullptr;   //opengl����

    bool selected = false;  //��ʶ  ѡ��Ҫ��
    bool deleted = false;

    //��ɫ
    QRgb color = utils::getRandomColor();
    QRgb borderColor = Qt::black;  //��߽���ɫ
};