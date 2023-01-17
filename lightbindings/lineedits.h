#ifndef LINEEDITS_H
#define LINEEDITS_H
#include <QMutex>
#include <QRegExpValidator>
#include <QLineEdit>
#include "notsupported.h"
namespace LightBinding{
template <typename Tuns>
inline QString hexString(Tuns hex, QString suffix = "0x", bool appendZeroes = false)
{
    QString tempStr = QString::number(hex, 16);
    if (!appendZeroes){
        while (static_cast<uint>(tempStr.length()) < (sizeof (Tuns) * 2)){
            tempStr.prepend("0");
        }
    }
    else{
        while (static_cast<uint>(tempStr.length()) <  (sizeof (Tuns) * 2)){
            tempStr.append("0");
        }
    }
    tempStr.prepend(suffix);
    return tempStr;
}


//binding LineEdit
template <typename TVal, typename std::enable_if<std::is_unsigned<TVal>::value, bool>::type = true>
inline void updateLeToVal(TVal& val, QString txt){
    ulong proxy;
    txt.contains("0x")? proxy = txt.toULong(nullptr, 16): proxy = txt.toULong();
    val = static_cast<TVal>(proxy);
}
template <typename TVal, typename std::enable_if<std::is_integral<TVal>::value
                                                 && !std::is_unsigned<TVal>::value, bool>::type = true>
inline void updateLeToVal(TVal& val, QString txt){
    long proxy;
    txt.contains("0x")? proxy = txt.toLong(nullptr, 16): proxy = txt.toLong();
    val = static_cast<TVal>(proxy);
}
template <typename TVal, typename std::enable_if<std::is_same<TVal, QString>::value, bool>::type = true>
inline void updateLeToVal(TVal& val, QString txt){
    val = txt;
}
template <typename TVal, typename std::enable_if<std::is_floating_point<TVal>::value, bool>::type = true>
inline void updateLeToVal(TVal& val, QString txt){
    double proxy;
    proxy = txt.toDouble();
    val = static_cast<TVal>(proxy);
}

template <typename TVal>
inline void updateLeToVal(TVal& val, QString txt, QMutex& m){
    QMutexLocker ml(&m);
    updateLeToVal(val, txt);
}
template <typename TVal>
inline QLineEdit* bindLeToVal(TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textEdited, [&val](const QString& txt){updateLeToVal(val, txt);});
    updateLeToVal(val, le->text());
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeToVal(TVal& val , QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textEdited, [&](const QString& txt){updateLeToVal(val,txt, m);});
    updateLeToVal(val, le->text(), m);
    return le;
};

template <typename TVal,
          typename std::enable_if<std::is_integral<TVal>::value
                                  || std::is_floating_point<TVal>::value, bool>::type = true>
inline bool updateLeFromVal(TVal& val, QLineEdit* le){
    le->setText(QString::number(val));
    return true;
};
template <typename TVal,
          typename std::enable_if<std::is_same<TVal, QString>::value, bool>::type = true>
inline bool updateLeFromVal(TVal& val, QLineEdit* le){
    le->setText(val);
    return true;
};

template <typename TVal>
inline bool updateLeFromVal(TVal& val, QLineEdit* le, QMutex& m){
    QMutexLocker ml(&m);
    return updateLeFromVal(val, le);
};
template <typename TVal>
inline QLineEdit* bindLeFromVal(TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textEdited, [&](const QString& txt){updateLeToVal(val, txt);});
    updateLeFromVal(val, le);
    return le;
}

template <typename TVal>
inline QLineEdit* bindLeFromVal(TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textEdited, [&](const QString& txt){updateLeToVal(val, txt, m);});
    updateLeFromVal(val, le, m);
    return le;
};

//binding le to hex
//inline

template <typename TVal, typename std::enable_if<std::is_unsigned<TVal>::value, bool>::type = true>
inline void updateLeToHex(TVal& val, QString txt){
    bool ok{false};
        val = txt.toUInt(&ok, 16);
}
template <typename TVal>
inline void updateLeToHex(TVal& val, QString txt, QMutex& m){
    QMutexLocker ml(&m);
    updateLeToHex(val, txt);
}



template <typename TVal>
inline void updateLeFromHex(TVal& val, QLineEdit* le){
    QString msg = hexString(static_cast<TVal>(val));  //possible type narrowing!
    le->setText(msg);
}
template <typename TVal>
inline void updateLeFromHex(TVal& val, QLineEdit* le, QMutex& m){
    QMutexLocker ml(&m);
    updateLeFromHex(val, le);
}
template<typename TVal>
inline QLineEdit* bindLeToHex(TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    //le->setInputMask("0xHhhhhhhh");
    le->setFont(QFont("courier", 11));
    le->connect(le, &QLineEdit::textEdited, [&](const QString& txt){
        QString curText = txt;
        updateLeToHex(val, txt);});
    updateLeToHex(val, le->text());
    return le;
};
template<typename TVal>
inline QLineEdit* bindLeToHex(TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    //le->setInputMask("0xHhhhhhhh");
    le->setFont(QFont("courier", 11));
    le->connect(le, &QLineEdit::textEdited, [&](const QString& txt){
        QString curText = txt;
         updateLeToHex(val, txt, m);
    });
    updateLeToHex(val, le->text(), m);
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeFromHex(TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    //le->setInputMask("0xHhhhhhhh");
    le->setFont(QFont("courier", 11));
    le->connect(le, &QLineEdit::textEdited, [&, le](const QString& txt){
        QString curText = txt;
        updateLeToHex(val, curText);}
    );
    auto curTxt = le->text();

    updateLeFromHex(val, le);
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeFromHex(TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    //le->setInputMask("0xHhhhhhhhh");
    le->setFont(QFont("courier", 11));
    le->connect(le, &QLineEdit::textEdited, [&, le](const QString& txt){
        QString curText = txt;
         updateLeToHex(val, txt, m);
    });
    updateLeFromHex(val, le, m);
    return le;
};

}



#endif // LINEEDITS_H
