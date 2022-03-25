#ifndef RADIOBUTTONS_H
#define RADIOBUTTONS_H
#include <QMutex>
#include <QRadioButton>
namespace LightBinding {

//binding radiobutton
template <typename TVal>
inline void updateRbToVal(TVal& val, bool changedVal){
    val = changedVal;
}

template <typename TVal>
inline void updateRbToVal(TVal& val, bool changedVal, QMutex& m){
    QMutexLocker ml(&m);
    updateRbToVal(val, changedVal);
}
template <typename TVal>
inline void updateRbFromVal(TVal& val, QRadioButton* rb){
    rb->setChecked(val);
}
template <typename TVal>
inline void updateRbFromVal(TVal& val, QRadioButton* rb, QMutex& m){
    QMutexLocker ml(&m);
    updateRbFromVal(val, rb);
}

inline QRadioButton* bindRbToVal(bool& val, QRadioButton* rb = nullptr){
    if (!rb) rb = new QRadioButton();
    rb->connect(rb, &QRadioButton::toggled, [&](bool checked){
        updateRbToVal(val, checked);
    });
    updateRbToVal(val, rb->isChecked());
    return rb;
}
inline QRadioButton* bindRbToVal(bool& val, QMutex&m, QRadioButton* rb = nullptr){
    if (!rb) rb = new QRadioButton();
    rb->connect(rb, &QRadioButton::toggled, [&](bool checked){
        updateRbToVal(val, checked, m);
    });
    updateRbToVal(val, rb->isChecked(), m);
    return rb;
}
inline QRadioButton* bindRbFromVal(bool& val, QRadioButton* rb = nullptr){
    if (!rb) rb = new QRadioButton();
    rb->connect(rb, &QRadioButton::toggled, [&](bool checked){
        updateRbToVal(val, checked);
    });
    updateRbFromVal(val, rb);
    return rb;
}
inline QRadioButton* bindRbFromVal(bool& val, QMutex& m, QRadioButton* rb = nullptr){
    if (!rb) rb = new QRadioButton();
    rb->connect(rb, &QRadioButton::toggled, [&](bool checked){
        updateRbToVal(val, checked, m);
    });
    updateRbFromVal(val, rb, m);
    return rb;
}

}
#endif // RADIOBUTTONS_H
