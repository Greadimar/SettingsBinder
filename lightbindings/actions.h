#ifndef ACTIONS_H
#define ACTIONS_H

#include <QAction>
#include <QMutex>

namespace LightBinding {
template<typename TVal>
    inline void updateActToVal(TVal& val, bool changedVal) {
        static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
        val = changedVal;
    }

template<typename TVal>
    inline void updateActToVal(TVal& val, bool changedVal, QMutex& m) {
        static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
        QMutexLocker ml(&m);
        updateActToVal(val, changedVal);
    }

template<typename TVal>
    inline void updateActFromVal(TVal& val, QAction* act) {
        static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
        act->setChecked(val);
    }

template<typename TVal>
    inline void updateActFromVal(TVal& val, QAction* act, QMutex& m) {
        static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
        QMutexLocker ml(&m);
        updateActFromVal(val, act);
    }

template<typename TVal>
    inline QAction* bindActToVal(QObject* connector, TVal& val, QAction* act = nullptr) {
        static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
        if (!act)
            act = new QAction();

        act->setCheckable(true);

        connector->connect(act, &QAction::triggered, [&](bool checked){
            updateActToVal(val, checked);
        });
        updateActToVal(val, act->isChecked());
        return act;
    }

template<typename TVal>
    inline QAction* bindActToVal(QObject* connector, TVal& val, QMutex& m, QAction* act = nullptr) {
        static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
        if (!act)
            act = new QAction();

        act->setCheckable(true);

        connector->connect(act, &QAction::triggered, [&](bool checked){
            updateActToVal(val, checked, m);
        });
        updateActToVal(val, act->isChecked(), m);
        return act;
    }

template<typename TVal>
    inline QAction* bindActFromVal(QObject* connector, TVal& val, QAction* act = nullptr) {
        static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
        if (!act)
            act = new QAction();

        act->setCheckable(true);

        connector->connect(act, &QAction::triggered, [&](bool checked){
            updateActToVal(val, checked);
        });
        updateActFromVal(val, act);
        return act;
    }

template<typename TVal>
    inline QAction* bindActFromVal(QObject* connector, TVal& val, QMutex& m, QAction* act = nullptr) {
        static_assert (std::is_convertible<TVal, bool>::value, "This type is not supported");
        if (!act)
            act = new QAction();

        act->setCheckable(true);

        connector->connect(act, &QAction::triggered, [&](bool checked){
            updateActToVal(val, checked, m);
        });
        updateActFromVal(val, act, m);
        return act;
    }
}

#endif // ACTIONS_H
