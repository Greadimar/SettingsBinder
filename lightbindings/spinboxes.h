#ifndef SPINBOXES_H
#define SPINBOXES_H
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QMutex>
#include "notsupported.h"
namespace LightBinding{

//binding spinbox
template <typename TVal>
inline void updateSbToVal(TVal& val, int changedVal){
    if constexpr (std::is_integral<TVal>::value){
        val = static_cast<TVal>(changedVal);
    }
    else if constexpr (std::is_same<TVal, std::chrono::milliseconds>::value){
        val = std::chrono::milliseconds(changedVal);
    }
    else{
        NOTSUPPORTED<TVal>();
    }
}
template <typename TVal>
inline void updateSbToVal(TVal& val, int changedVal, QMutex& m){
    QMutexLocker ml(&m);
    updateSbToVal(val, changedVal);
}
template <typename TVal>
inline void updateSbFromVal(TVal& val, QSpinBox* sb){
    if constexpr (std::is_integral<TVal>::value){
        sb->setValue(val);
    }
    else if constexpr (std::is_same<TVal, std::chrono::milliseconds>::value){
        sb->setValue(val.count());
    }
    else{
        NOTSUPPORTED<TVal>();
    }
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
template <typename TVal>
inline void updateDsbToVal(TVal& val, double changedVal){
    if constexpr (std::is_floating_point<TVal>::value){
        val = static_cast<TVal>(changedVal);
    }
    else{
        NOTSUPPORTED<TVal>();
    }
}
template <typename TVal>
inline void updateDsbToVal(TVal& val, double changedVal, QMutex& m){
    QMutexLocker ml(&m);
    updateDsbToVal(val, changedVal);
}
template <typename TVal>
inline void updateDsbFromVal(TVal& val, QDoubleSpinBox* dsb){
    if constexpr (std::is_floating_point<TVal>::value){
        dsb->setValue(val);
    }
    else{
        NOTSUPPORTED<TVal>();
    }
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
    updateDsbToVal(val, dsb);
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
