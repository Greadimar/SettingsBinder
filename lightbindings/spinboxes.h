#ifndef SPINBOXES_H
#define SPINBOXES_H
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QMutex>
#include <QDebug>
#include "notsupported.h"
namespace LightBinding{

//binding spinbox
template <typename TVal, typename std::enable_if<std::is_integral<TVal>::value, bool>::type = true>
inline void updateSbToVal(TVal& val, int changedVal){
   val = static_cast<TVal>(changedVal);
}
template <typename TVal,
          typename std::enable_if<
              !std::is_integral<TVal>::value &&
              std::is_constructible<TVal, int>::value, bool>
          ::type = true>
inline void updateSbToVal(TVal& val, int changedVal){
   val = TVal(changedVal);
}

template <typename TVal>
inline void updateSbToVal(TVal& val, int changedVal, QMutex& m){
    QMutexLocker ml(&m);
    updateSbToVal(val, changedVal);
}


template <typename TVal>
inline void updateSbFromVal(TVal& val, QSpinBox* sb){
    sb->setValue(val);
}

template <typename TRepType, typename TRatioType>
inline void updateSbFromVal(std::chrono::duration<TRepType, TRatioType> & val, QSpinBox* sb){

    //static_assert ratiotype is std::ratio
    //static_assert TDur is std::chrono::duration
    sb->setValue(val.count());
}
template <typename TVal>
inline void updateSbFromVal(TVal& val, QSpinBox* sb, QMutex& m){
    QMutexLocker ml(&m);
    updateSbFromVal(val, sb);
}

template <typename TVal>
inline QSpinBox* bindSbToVal(TVal& val , QSpinBox* sb = nullptr){
    if (!sb) sb = new QSpinBox();
    sb->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
        updateSbToVal(val, changedVal);
    });
    updateSbToVal(val, sb->value());
    return sb;
}
template <typename TVal>
inline QSpinBox* bindSbToVal(TVal& val, QMutex& m, QSpinBox* sb = nullptr){
    if (!sb) sb = new QSpinBox();
    sb->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
        updateSbToVal(val, changedVal, m);
    });
    updateSbToVal(val, sb->value(), m);
    return sb;
}

template <typename TVal>
inline QSpinBox* bindSbFromVal(TVal& val , QSpinBox* sb = nullptr){
    if (!sb) sb = new QSpinBox();
    sb->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
        updateSbToVal(val, changedVal);
    });
    updateSbFromVal(val, sb);
    return sb;
}

template <typename TVal>
inline QSpinBox* bindSbFromVal(TVal& val , QMutex& m, QSpinBox* sb = nullptr){
    if (!sb) sb = new QSpinBox();
    sb->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
        updateSbToVal(val, changedVal, m);
    });
    updateSbFromVal(val, sb, m);
    return sb;
}

//binding double spin box

template <typename TVal,
          typename std::enable_if<std::is_floating_point<TVal>::value, bool>::type = true>
inline void updateDsbToVal(TVal& val, double changedVal){
        val = static_cast<TVal>(changedVal);
}
template <typename TVal>
inline void updateDsbToVal(TVal& val, double changedVal, QMutex& m){
    QMutexLocker ml(&m);
    updateDsbToVal(val, changedVal);
}

template <typename TVal, typename std::enable_if<std::is_floating_point<TVal>::value, bool>::type = true>
inline void updateDsbFromVal(TVal& val, QDoubleSpinBox* dsb){
        dsb->setValue(val);
}
template <typename TVal>
inline void updateDsbFromVal(TVal& val, QDoubleSpinBox* dsb, QMutex& m){
    QMutexLocker ml(&m);
    updateDsbFromVal(val, dsb);
}
template <typename TVal>
inline QDoubleSpinBox* bindDsbToVal(TVal& val, QDoubleSpinBox* dsb = nullptr){
    if (!dsb) dsb = new QDoubleSpinBox();
    dsb->connect(dsb, qOverload<double>(&QDoubleSpinBox::valueChanged), [&](double changedVal){
        updateDsbToVal(val, changedVal);
    });
    updateDsbToVal(val, dsb->value());
    return dsb;
}
template <typename TVal>
inline QDoubleSpinBox* bindDsbToVal(TVal& val, QMutex& m, QDoubleSpinBox* dsb = nullptr){
    if (!dsb) dsb = new QDoubleSpinBox();
    dsb->connect(dsb, qOverload<double>(&QDoubleSpinBox::valueChanged), [&](double changedVal){
        updateDsbToVal(val, changedVal, m);
    });
    updateDsbToVal(val, dsb, m);
    return dsb;
}
template <typename TVal>
inline QDoubleSpinBox* bindDsbFromVal(TVal& val, QDoubleSpinBox* dsb = nullptr){
    if (dsb == nullptr) dsb = new QDoubleSpinBox();
    dsb->connect(dsb, qOverload<double>(&QDoubleSpinBox::valueChanged), [&](double changedVal){
        updateDsbToVal(val, changedVal);
    });
    updateDsbFromVal(val, dsb);
    return dsb;
}
template <typename TVal>
inline QDoubleSpinBox* bindDsbFromVal(TVal& val, QMutex& m, QDoubleSpinBox* dsb = nullptr){
    if (!dsb) dsb = new QDoubleSpinBox();
    dsb->connect(dsb, qOverload<double>(&QDoubleSpinBox::valueChanged), [&](double changedVal){
        updateDsbToVal(val, changedVal, m);
    });
    updateDsbFromVal(val, dsb, m);
    return dsb;
}



}

#endif // SPINBOXES_H
