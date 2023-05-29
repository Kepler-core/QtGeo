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

// ���������ľ���
#define DIS_SQURE(x1, y1, x2, y2) ((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2))
//���ռ���ڴ�
#define PrintSize(x) std::cout << "sizeof("#x")" << ": " << sizeof(x) << std::endl


namespace utils //ʹ�õ����������ռ�
{
    //���⸺���洢
    using uchar = unsigned char;  //��ֵ��Χ��0-255
    using uint = unsigned int;
    using ushort = unsigned short;

    enum DataType   //��������ö��
    {
        kUnknown = 0,
        kByte = 1,
        kInt = 2,
        kUInt = 3,
        kFloat = 4,
        kDouble = 5
    };

    //��������
    QString getFileName(const QString& filepath);  //���ݾ���·����ȡ�ļ���
    //QString replaceExt(const QString& filepath, const QString& newExt);  // �����ļ�����׺
    unsigned int* newContinuousNumber(unsigned int start, unsigned int count);   // ����������(��ʲô��?)
    void hex2rgb(std::string hexCode, uchar& r, uchar& g, uchar& b);  // ��ɫת��
    bool isEqual(double a, double b, double eps = 1e-6);   // �Ƚ���ֵ�Ƿ���ȣ�float��
    unsigned int getRandomColor();  //��ȡ�����ɫ(���ļ�ʱ������)

    //ģ�巽��
    template<typename To, typename From>
    //down_cast������������ת��������ָ��C>����ָ�룩
    inline To down_cast(From* f)
    {
        return dynamic_cast<To>(f);
    }

    // ���������
    template<typename T>
    inline T getRand(T lower, T upper)
    {
        return rand() / (double)RAND_MAX * (upper - lower) + lower;
    }

    // ������λ��
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


