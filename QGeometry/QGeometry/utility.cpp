#include "utility.h"

#include <cstring>
#include <sstream>
#include <QRgb>

#include <QFileInfo>
#include <cmath>


namespace utils 
{

    QString getFileName(const QString& filepath)  //获取文件名
    {
        QFileInfo fileInfo(filepath);
        return fileInfo.baseName();
    }

    //QString replaceExt(const QString& filepath, const QString& newExt)  //更改文件后缀（保存时）
    //{
    //    int indexOfDot = filepath.lastIndexOf(".");  //定位后缀
    //    int indexOfSlash = 0;
    //    indexOfSlash = filepath.lastIndexOf("\\");  //定位\位置

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


    ////根据起始值与个数创建连续数列
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

    //将hex（16进制版）转换为rgb模式
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

    //比较两个数，但是double
    bool isEqual(double a, double b, double eps)
    {
        return fabs(a - b) < eps;
    }


    /*创建随机颜色*/
    //Color getRandColor()
    //{
    //	uchar r = getRand(0, 256);
    //	uchar g = getRand(0, 256);
    //	uchar b = getRand(0, 256);
    //	return { r, g, b };
    //}

    //获取随机颜色值
    QRgb getRandomColor()
    {
        return qRgb(getRand(50, 200), getRand(50, 200), getRand(50, 200));
    }

} // namespace util