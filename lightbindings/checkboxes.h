#ifndef CHECKBOXES_H
#define CHECKBOXES_H
#include <QMutex>
#include <QCheckBox>
namespace LightBinding {
//binding checkbox
template <typename TVal>
inline void updateChbToVal(TVal& val, bool changedVal){
    static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
    val = changedVal;
}

template <typename TVal>
inline void updateChbToVal(TVal& val, bool changedVal, QMutex& m){
    static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
    QMutexLocker ml(&m);
    updateChbToVal(val, changedVal);
}
template <typename TVal>
inline void updateChbFromVal(TVal& val, QCheckBox* chb){
    static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
    chb->setChecked(val);
}
template <typename TVal>
inline void updateChbFromVal(TVal& val, QCheckBox* chb, QMutex& m){
    static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
    QMutexLocker ml(&m);
    updateChbFromVal(val, chb);
}

template <typename TVal>
inline QCheckBox* bindChbToVal(QObject* connector, TVal& val, QCheckBox* chb = nullptr){
    static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
    if (!chb) chb = new QCheckBox();
    connector->connect(chb, &QCheckBox::toggled, [&](bool checked){
        updateChbToVal(val, checked);
    });
    updateChbToVal(val, chb->isChecked());
    return chb;
}
template <typename TVal>
inline QCheckBox* bindChbToVal(QObject* connector, TVal& val, QMutex& m, QCheckBox* chb = nullptr){
    static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
    if (!chb) chb = new QCheckBox();
    connector->connect(chb, &QCheckBox::toggled, [&](bool checked){
        updateChbToVal(val, checked, m);
    });
    updateChbToVal(val, chb->isChecked(), m);
    return chb;
}
template <typename TVal>
inline QCheckBox* bindChbFromVal(QObject* connector, TVal& val, QCheckBox* chb = nullptr){
    static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
    if (!chb) chb = new QCheckBox();
    connector->connect(chb, &QCheckBox::toggled, [&](bool checked){
        updateChbToVal(val, checked);
    });
    updateChbFromVal(val, chb);
    return chb;
}
template <typename TVal>
inline QCheckBox* bindChbFromVal(QObject* connector, TVal& val, QMutex& m, QCheckBox* chb = nullptr){
    static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
    if (!chb) chb = new QCheckBox();
    connector->connect(chb, &QCheckBox::toggled, [&](bool checked){
        updateChbToVal(val, checked, m);
    });
    updateChbFromVal(val, chb, m);
    return chb;
}



}


#endif // CHECKBOXES_H
