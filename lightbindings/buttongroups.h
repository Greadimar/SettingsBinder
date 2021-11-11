#ifndef BUTTONGROUPS_H
#define BUTTONGROUPS_H
#include <QButtonGroup>
#include <QAbstractButton>
#include <QMutex>
#include "notsupported.h"
namespace  LightBinding{
//binding groupToval
template <typename TEnumVal>
inline void updateBtnGrpToVal(TEnumVal& val, int btnId){
    val = static_cast<TEnumVal>(btnId);
}
template <typename TEnumVal>
inline void updateBtnGrpToVal(TEnumVal& val, int btnId, QMutex& m){
    QMutexLocker ml(&m);
    val = static_cast<TEnumVal>(btnId);
}
template <typename TVal>
inline void updateBtnGrpFromVal(TVal& val, QButtonGroup* bgrp){
    int idx = static_cast<int>(val);
    if (idx < bgrp->buttons().size() && idx >= 0)
        bgrp->button(idx)->setChecked(true);
}
template <typename TVal>
inline void updateBtnGrpFromVal(TVal& val, QButtonGroup* bgrp, QMutex& m){
    QMutexLocker ml(&m);
    updateBtnGrpFromVal(val, bgrp);
}

template <typename TEnumVal>
inline QButtonGroup* bindBtnGrpToVal(QObject* connector, TEnumVal& val, QButtonGroup* bgrp){
    if (!bgrp) bgrp = new QButtonGroup(connector);
    static_assert (std::is_enum<TEnumVal>::value, "please, use enum or enum class to bind this button group");
#if QT_VERSION >= 0x051500
    connector->connect(bgrp, &QButtonGroup::idToggled, [&](int btnId, bool isToggled){
        if (isToggled) updateBtnGrpToVal(val, btnId);
    });
#else
    connector->connect(bgrp, &QButtonGroup::buttonToggled, [&](int btnId, bool isToggled){
        if (isToggled) updateBtnGrpToVal(val, btnId);
    });
#endif
    if (bgrp->checkedId() >= 0)
        updateBtnGrpToVal(val, bgrp->checkedId());
    return bgrp;
}

//from val
template <typename TEnumVal>
inline QButtonGroup* bindBtnGrpFromVal(QObject* connector, TEnumVal& val, QButtonGroup* bgrp){
    if (!bgrp) bgrp = new QButtonGroup(connector);
    static_assert (std::is_enum<TEnumVal>::value, "please, use enum or enum class to bind this button group");
#if QT_VERSION >= 0x051500
    connector->connect(bgrp, &QButtonGroup::idToggled, [&](int btnId, bool isToggled){
        if (isToggled) updateBtnGrpToVal(val, btnId);
    });
#else
    connector->connect(bgrp, qOverload<int, bool>(&QButtonGroup::buttonToggled), [&](int btnId, bool isToggled){
        if (isToggled) updateBtnGrpToVal(val, btnId);
    });
#endif
    updateBtnGrpFromVal(val, bgrp);
    return bgrp;
}

template <typename TEnumVal>
inline QButtonGroup* bindBtnGrpToVal(QObject* connector, TEnumVal& val, QButtonGroup* bgrp, QMutex& m){
    if (!bgrp) bgrp = new QButtonGroup(connector);
    static_assert (std::is_enum<TEnumVal>::value, "please, use enum or enum class to bind this button group");
#if QT_VERSION >= 0x051500
    connector->connect(bgrp, &QButtonGroup::idToggled, [&](int btnId, bool isToggled){
        if (isToggled) updateBtnGrpToVal(val, btnId);
    });
#else
    connector->connect(bgrp, qOverload<int, bool>(&QButtonGroup::buttonToggled), [&](int btnId, bool isToggled){
        if (isToggled) updateBtnGrpToVal(val, btnId, m);
    });
#endif
    if (bgrp->checkedId() >= 0)
        updateBtnGrpToVal(val, bgrp->checkedId(), m);
    return bgrp;
}


template <typename TEnumVal>
inline QButtonGroup* bindBtnGrpFromVal(QObject* connector, TEnumVal& val, QButtonGroup* bgrp, QMutex& m){
    if (!bgrp) bgrp = new QButtonGroup(connector);
    static_assert (std::is_enum<TEnumVal>::value, "please, use enum or enum class to bind this button group");
#if QT_VERSION >= 0x051500
    connector->connect(bgrp, &QButtonGroup::idToggled, [&](int btnId, bool isToggled){
        if (isToggled) updateBtnGrpToVal(val, btnId, m);
    });
#else
    connector->connect(bgrp, &QButtonGroup::buttonToggled, [&](int btnId, bool isToggled){
        if (isToggled) updateBtnGrpToVal(val, btnId, m);
    });
#endif
    updateBtnGrpFromVal(val, bgrp, m);
    return bgrp;
}





}


#endif // BUTTONGROUPS_H
