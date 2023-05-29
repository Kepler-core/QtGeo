#pragma once
#include <QString>

/*字段*/

enum GeoFieldType 
{
    kFieldInt = 0,   //字段类型枚举
    kFieldDouble,
    kFieldText,
    kFieldUnknown
};


class GeoFieldDefn    
{
public:
    //字段定义  不同参数的构造函数
    GeoFieldDefn() = default;
    GeoFieldDefn(QString nameIn, int widthIn, GeoFieldType typeIn)
        : width(widthIn), type(typeIn), name(nameIn) {}
    GeoFieldDefn(const GeoFieldDefn& rhs)
        : width(rhs.width), type(rhs.type), name(rhs.name) {}
    ~GeoFieldDefn() = default;

    bool isSame(const GeoFieldDefn& rhs)  //判断字段名是否相同
    {
        return name == rhs.name;
    }
    bool operator==(const GeoFieldDefn& rhs)
    {
        return name == rhs.name;
    }

    //获取字段相关属性
    GeoFieldType getType() const { return type; }
    QString getName() const { return name; }
    int getWidth() const { return width; }

    //字段设置
    void setType(GeoFieldType typeIn) { this->type = typeIn; }  //类型
    void setWidth(int widthIn) { this->width = widthIn; }  //长度
    void setName(QString nameIn) { name = nameIn; }  //名称

private:
    int width = 0;						// 文本字段的最大长度
    GeoFieldType type = kFieldUnknown;	// 字段类型（int,double,Text）
    QString name;   //字段名
};
