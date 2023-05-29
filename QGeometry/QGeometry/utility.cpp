#include "utility.h"

#include <cstring>
#include <sstream>
#include <QRgb>

#include <QFileInfo>
#include <cmath>


namespace utils 
{

    QString getFileName(const QString& filepath)  //��ȡ�ļ���
    {
        QFileInfo fileInfo(filepath);
        return fileInfo.baseName();
    }

    //QString replaceExt(const QString& filepath, const QString& newExt)  //�����ļ���׺������ʱ��
    //{
    //    int indexOfDot = filepath.lastIndexOf(".");  //��λ��׺
    //    int indexOfSlash = 0;
    //    indexOfSlash = filepath.lastIndexOf("\\");  //��λ\λ��

    //    if (indexOfDot > indexOfSlash) 
    //    {
    //        if (newExt.indexOf(".") == -1)
    //            return filepath.left(indexOfDot + 1) + newExt;
    //        else
    //            return filepath.left(indexOfDot) + newExt;
    //    }
    //    else {
    //        if (newExt.indexOf(".") == -1)
    //            return filepath + "." + newExt;
    //        else
    //            return filepath + newExt;
    //    }
    //}


    ////������ʼֵ�����������������
    unsigned int* newContinuousNumber(unsigned int start, unsigned int count)
    {
        if (count < 1)
            return nullptr;
        else {
            unsigned int* ret = new unsigned int[count];
            for (unsigned int i = 0; i < count; ++i)
            {
                ret[i] = start + i;
            }
            return ret;
        }
    }

    //��hex��16���ư棩ת��Ϊrgbģʽ
    void hex2rgb(std::string hexCode, uchar& r, uchar& g, uchar& b)
    {
        if (hexCode[0] == '#')
            hexCode.erase(0, 1);
        if (hexCode.size() < 6)
            return;

        int iR, iG, iB;

        std::istringstream(hexCode.substr(0, 2)) >> std::hex >> iR;
        std::istringstream(hexCode.substr(2, 2)) >> std::hex >> iG;
        std::istringstream(hexCode.substr(4, 2)) >> std::hex >> iB;

        r = uchar(iR);
        g = uchar(iG);
        b = uchar(iB);
    }

    //�Ƚ�������������double
    bool isEqual(double a, double b, double eps)
    {
        return fabs(a - b) < eps;
    }


    /*���������ɫ*/
    //Color getRandColor()
    //{
    //	uchar r = getRand(0, 256);
    //	uchar g = getRand(0, 256);
    //	uchar b = getRand(0, 256);
    //	return { r, g, b };
    //}

    //��ȡ�����ɫֵ
    QRgb getRandomColor()
    {
        return qRgb(getRand(50, 200), getRand(50, 200), getRand(50, 200));
    }

} // namespace util