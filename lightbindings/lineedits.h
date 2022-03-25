#ifndef LINEEDITS_H
#define LINEEDITS_H
#include <QMutex>
#include <QLineEdit>
#include "notsupported.h"
namespace LightBinding{

//binding LineEdit
template <typename TVal>
inline void updateLeToVal(TVal& val, QString txt){
    if constexpr (std::is_unsigned<TVal>::value){
        ulong proxy;
        txt.contains("0x")? proxy = txt.toULong(nullptr, 16): proxy = txt.toULong();
        val = static_cast<TVal>(proxy);
    }
    else if constexpr(std::is_integral<TVal>::value){
        long proxy;
        txt.contains("0x")? proxy = txt.toLong(nullptr, 16): proxy = txt.toLong();
        val = static_cast<TVal>(proxy);
    }
    else if constexpr(std::is_same<TVal, QString>::value){
        val = txt;
    }
    else if constexpr(std::is_floating_point<TVal>::value){
        double proxy;
        proxy = txt.toDouble();
        val = static_cast<TVal>(proxy);
    }
    else {
        NOTSUPPORTED<TVal>();
    }
}
template <typename TVal>
inline void updateLeToVal(TVal& val, QString txt, QMutex& m){
    QMutexLocker ml(&m);
    updateLeToVal(val, txt);
}
template <typename TVal>
inline QLineEdit* bindLeToVal(TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textChanged, [&val](const QString& txt){updateLeToVal(val, txt);});
    updateLeToVal(val, le->text());
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeToVal(TVal& val , QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textChanged, [&](const QString& txt){updateLeToVal(val,txt, m);});
    updateLeToVal(val, le->text(), m);
    return le;
};
template <typename TVal>
inline bool updateLeFromVal(TVal& val, QLineEdit* le){
    if constexpr (std::is_integral<TVal>::value || std::is_floating_point<TVal>::value){
        le->setText(QString::number(val));
        return true;
    }
    if constexpr (std::is_same<TVal, QString>::value){
        le->setText(val);
        return true;
    }
    return false;
};
template <typename TVal>
inline bool updateLeFromVal(TVal& val, QLineEdit* le, QMutex& m){
    QMutexLocker ml(&m);
    return updateLeFromVal(val, le);
};
template <typename TVal>
inline QLineEdit* bindLeFromVal(TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textChanged, [&](const QString& txt){updateLeToVal(val, txt);});
    updateLeFromVal(val, le);
    return le;
}

template <typename TVal>
inline QLineEdit* bindLeFromVal(TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textChanged, [&](const QString& txt){updateLeToVal(val, txt, m);});
    updateLeFromVal(val, le, m);
    return le;
};

//binding le to hex
template <typename TVal>
inline void updateLeToHex(TVal& val, QString txt){
    if constexpr (std::is_unsigned<TVal>::value){
        val = static_cast<TVal>(txt.toUInt(nullptr, 16));
    }
    else{
        NOTSUPPORTED<TVal>();
    }
}
template <typename TVal>
inline void updateLeToHex(TVal& val, QString txt, QMutex& m){
    QMutexLocker ml(&m);
    updateLeToHex(val, txt);
}
template <typename TVal>
inline void updateLeFromHex(TVal& val, QLineEdit* le){
    le->setText(QString::number(val, 16));
}
template <typename TVal>
inline void updateLeFromHex(TVal& val, QLineEdit* le, QMutex& m){
    QMutexLocker ml(&m);
    updateLeFromHex(val, le);
}
template<typename TVal>
inline QLineEdit* bindLeToHex(TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textChanged, [&](const QString& txt){updateLeToHex(val, txt);});
    updateLeToHex(val, le->text());
    return le;
};
template<typename TVal>
inline QLineEdit* bindLeToHex(TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textChanged, [&](const QString& txt){updateLeToHex(val, txt, m);});
    updateLeToHex(val, le->text(), m);
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeFromHex(TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();

    le->connect(le, &QLineEdit::textChanged, [&](const QString& txt){updateLeToHex(val, txt);});
    updateLeFromHex(val, le);
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeFromHex(TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->connect(le, &QLineEdit::textChanged, [&](const QString& txt){updateLeFromHex(val, txt, m);});
    updateLeFromHex(val, le, m);
    return le;
};

}



#endif // LINEEDITS_H
