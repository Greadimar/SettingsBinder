#ifndef LINEEDITS_H
#define LINEEDITS_H
#include <QMutex>
#include <QRegExpValidator>
#include <QLineEdit>
#include "notsupported.h"
#include "lbtools.h"
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
template <typename TVal>
bool manageHexInLe(QLineEdit* le, const TVal& val, QString& txt){
    TVal proxy;
    auto cp = le->cursorPosition();
    if (cp < 2) cp = 2;         //move from "0x"
    if (le->hasSelectedText())
        cp = le->selectionEnd();
    const int fullsize = sizeof (TVal) * 2 + 2;
                              //0xffffg122 22
   // int trimSize = txt.size() - fullsize;

    bool txtIsOverflowed = txt.size() > fullsize;
    if (txtIsOverflowed){
         txt.remove(cp, 1);
         txt = txt.mid(0, fullsize);
    }
    else{
        while(txt.size() != fullsize) txt.append("0");
    }

    bool ok{false};
    proxy = txt.toUInt(&ok, 16);
    auto fixed = hexString(ok? proxy: val, "0x",  false);
    le->setText(fixed);
    txt = fixed;
    if (!ok){
        if (cp > 0) cp--;
    }
    if (cp <= 2) cp = 2;  //for reverse selection fix
    le->setCursorPosition(cp);
    return ok;
}
template <typename TVal>
inline void updateLeToHex(TVal& val, QString txt){
    bool ok{false};
    if constexpr (std::is_unsigned<TVal>::value){

        val = txt.toUInt(&ok, 16);
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
    le->setFont(QFont("courier", 11));
    le->connect(le, &QLineEdit::textEdited, [&](const QString& txt){
        QString curText = txt;
        if (manageHexInLe(le, val, curText)) updateLeToHex(val, txt);});
    updateLeToHex(val, le->text());
    return le;
};
template<typename TVal>
inline QLineEdit* bindLeToHex(TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->setFont(QFont("courier", 11));
    le->connect(le, &QLineEdit::textEdited, [&](const QString& txt){
        QString curText = txt;
        if (manageHexInLe(le, val, curText)) updateLeToHex(val, txt, m);
    });
    updateLeToHex(val, le->text(), m);
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeFromHex(TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->setFont(QFont("courier", 11));
    le->connect(le, &QLineEdit::textEdited, [&, le](const QString& txt){
        QString curText = txt;
        if (manageHexInLe(le, val, curText)) updateLeToHex(val, curText);}
    );
    updateLeFromHex(val, le);
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeFromHex(TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    le->setFont(QFont("courier", 11));
    le->connect(le, &QLineEdit::textEdited, [&, le](const QString& txt){
        QString curText = txt;
        if (manageHexInLe(le, val, curText)) updateLeToHex(val, txt, m);
    });
    updateLeFromHex(val, le, m);
    return le;
};

}



#endif // LINEEDITS_H
