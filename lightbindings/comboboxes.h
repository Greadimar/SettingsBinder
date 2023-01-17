#ifndef COMBOBOXES_H
#define COMBOBOXES_H
#include <QComboBox>
#include <QMutexLocker>
#include "notsupported.h"
namespace LightBinding {


template <typename TVal,
          typename std::enable_if<std::is_enum<TVal>::value || std::is_integral<TVal>::value, bool>::type = true>
inline void updateCbToVal(TVal& val, int changedVal){
        val = static_cast<TVal>(changedVal);
}
template <typename TVal,
          typename std::enable_if<std::is_enum<TVal>::value || std::is_integral<TVal>::value, bool>::type = true>
inline void updateCbToVal(std::atomic<TVal>& val, int changedVal){
        val = static_cast<TVal>(changedVal);
}

template <typename TVal>
inline void updateCbToVal(TVal& val, int changedVal, QMutex& m){
    static_assert (std::is_enum<TVal>::value || std::is_integral<TVal>::value, "This type is not supported");
    QMutexLocker ml(&m);
    updateCbToVal(val, changedVal);
}

template <typename TVal>
inline void updateCbFromVal(const TVal& val, QComboBox* cb){
    static_assert (std::is_enum<TVal>::value || std::is_integral<TVal>::value, "This type is not supported");
    if (cb->count() > static_cast<int>(val))
        cb->setCurrentIndex(static_cast<int>(val));
}
template <typename TVal>
inline void updateCbFromVal(const TVal& val, QComboBox* cb, QMutex& m){
    static_assert (std::is_enum<TVal>::value || std::is_integral<TVal>::value, "This type is not supported");
    QMutexLocker ml(&m);
    updateCbFromVal(val, cb);
}

template <typename TVal>
inline void updateCbFromVal(const std::atomic<TVal>& val, QComboBox* cb){
    static_assert (std::is_enum<TVal>::value || std::is_integral<TVal>::value, "This type is not supported");
    TVal&& curVal = val.load();
    if (cb->count() > static_cast<int>(curVal))
        cb->setCurrentIndex(static_cast<int>(curVal));
}
template <typename TVal>
inline QComboBox* bindCbToVal(TVal& val, QComboBox* cb = nullptr){
    static_assert (std::is_enum<TVal>::value || std::is_integral<TVal>::value, "This type is not supported");
    if (!cb) cb = new QComboBox();
    cb->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), [&](int changedVal){updateCbToVal(val, changedVal);});
    updateCbToVal(val, cb->currentIndex());
    return cb;
}
template <typename TVal>
inline QComboBox* bindCbToVal(TVal& val, QMutex& m, QComboBox* cb = nullptr){
    static_assert (std::is_enum<TVal>::value || std::is_integral<TVal>::value, "This type is not supported");
    if (!cb) cb = new QComboBox();
    cb->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), [&](int changedVal){updateCbToVal(val, changedVal, m);});
    updateCbToVal(val, cb->currentIndex(), m);
    return cb;
}
template <typename TVal>
inline QComboBox* bindCbFromVal(TVal& val, QComboBox* cb = nullptr){
    if (!cb) cb = new QComboBox();
    cb->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), [&](int changedVal){updateCbToVal(val, changedVal);});
    updateCbFromVal(val, cb);
    return cb;
}
template <typename TVal>
inline QComboBox* bindCbFromVal(TVal& val, QMutex& m, QComboBox* cb = nullptr){
    if (!cb) cb = new QComboBox();
    cb->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), [&](int changedVal){updateCbToVal(val, changedVal, m);});
    updateCbFromVal(val, cb, m);
    return cb;
}
template <typename TVal>
inline QComboBox* bindCbToVal(std::atomic<TVal>& val, QComboBox* cb = nullptr){
    static_assert (std::is_enum<TVal>::value || std::is_integral<TVal>::value, "This type is not supported");
    if (!cb) cb = new QComboBox();
    cb->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), [&](int changedVal){updateCbToVal(val, changedVal);});
    updateCbToVal(val, cb->currentIndex());
    return cb;
}
template <typename TVal>
inline QComboBox* bindCbFromVal(std::atomic<TVal>& val, QComboBox* cb = nullptr){
    static_assert (std::is_enum<TVal>::value || std::is_integral<TVal>::value, "This type is not supported");
    if (!cb) cb = new QComboBox();
    cb->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), [&](int changedVal){updateCbToVal(val, changedVal);});
    updateCbFromVal(val, cb);
    return cb;
}



}


#endif // COMBOBOXES_H
