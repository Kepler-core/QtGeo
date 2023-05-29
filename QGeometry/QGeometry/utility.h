#pragma once
#include <string>
#include <QString>

#define PI 3.1415926

#ifndef MIN
#define MIN(x, y) ((x)<(y)?(x):(y))
#endif
#ifndef MAX
#define MAX(x, y) ((x)>(y)?(x):(y))
#endif

// 定义两点间的距离
#define DIS_SQURE(x1, y1, x2, y2) ((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2))
//输出占用内存
#define PrintSize(x) std::cout << "sizeof("#x")" << ": " << sizeof(x) << std::endl


namespace utils //使用单独的命名空间
{
    //避免负数存储
    using uchar = unsigned char;  //数值范围是0-255
    using uint = unsigned int;
    using ushort = unsigned short;

    enum DataType   //数据类型枚举
    {
        kUnknown = 0,
        kByte = 1,
        kInt = 2,
        kUInt = 3,
        kFloat = 4,
        kDouble = 5
    };

    //函数声明
    QString getFileName(const QString& filepath);  //根据绝对路径获取文件名
    //QString replaceExt(const QString& filepath, const QString& newExt);  // 重置文件名后缀
    unsigned int* newContinuousNumber(unsigned int start, unsigned int count);   // 生成连续数(有什么用?)
    void hex2rgb(std::string hexCode, uchar& r, uchar& g, uchar& b);  // 颜色转换
    bool isEqual(double a, double b, double eps = 1e-6);   // 比较数值是否相等（float）
    unsigned int getRandomColor();  //获取随机颜色(打开文件时随机填充)

    //模板方法
    template<typename To, typename From>
    //down_cast用于向下类型转换（父类指针–>子类指针）
    inline To down_cast(From* f)
    {
        return dynamic_cast<To>(f);
    }

    // 生成随机数
    template<typename T>
    inline T getRand(T lower, T upper)
    {
        return rand() / (double)RAND_MAX * (upper - lower) + lower;
    }

    // 计算中位数
    template<typename T>
    inline T getMedian(T* values, int size)
    {
        std::sort(values, values + size);
        if (size % 2 == 0)
            return values[size / 2];
        else
            return (values[size / 2 - 1] + values[size / 2]) / 2.0;
    }

} // end namespace utils


