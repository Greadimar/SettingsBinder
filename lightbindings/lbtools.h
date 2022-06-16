#ifndef LBTOOLS_H
#define LBTOOLS_H
#include <QString>
namespace LightBinding{

template <typename Tuns = uint>
inline QString hexString(Tuns hex, QString suffix = "0x", bool appendZeroes = false)
{
    QString tempStr = QString::number(hex, 16);
    if (!appendZeroes){
        while (tempStr.length() < (sizeof (Tuns) * 2)){
            tempStr.prepend("0");
        }
    }
    else{
        while (tempStr.length() <  (sizeof (Tuns) * 2)){
            tempStr.append("0");
        }
    }
    tempStr.prepend(suffix);
    return tempStr;
}
}
#endif // LBTOOLS_H
