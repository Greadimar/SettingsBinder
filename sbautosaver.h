#ifndef AUTOSAVER_H
#define AUTOSAVER_H
#include <QSettings>
#include <QDir>
#if (defined __cplusplus) && (__cplusplus >= 201401L)
#include "simplereflex.h"

namespace SbAutoSaver{
template <class T>
void saveEveryField(T& t, const QString groupName = typeid (T()).name(), const QString filename = QDir::currentPath()+"/autosettings.ini")
{
    QSettings sets(filename, QSettings::IniFormat);
    sets.beginGroup(groupName);
    int i = 0;
    SimpleReflex::for_each_member(t, [&i, &sets](auto& member){
        using Type = typename std::remove_reference<decltype (member)>::type;
        if constexpr(std::is_enum<Type>::value){
            sets.setValue(QString("field_%1_%2").arg(typeid(member).name()).arg(i++), (static_cast<uint>(member)));
        }
        else{
            sets.setValue(QString("field_%1_%2").arg(typeid(member).name()).arg(i++), QVariant::fromValue<Type>(member));
        }
    });
    sets.endGroup();
}
template <class T>
void loadEveryField(T &t, const QString groupName = typeid (T()).name(), const QString filename = QDir::currentPath()+"/autosettings.ini")
{
    QSettings sets(filename, QSettings::IniFormat);
    sets.beginGroup(groupName);
    int i = 0;
    SimpleReflex::for_each_member(t, [&i, &sets](auto& member) mutable{
        //add check for enum class
        using Type = typename std::remove_reference<decltype (member)>::type;
        if constexpr(std::is_enum<Type>::value){
            member = static_cast<Type>(sets.value(QString("field_%1_%2").arg(typeid(member).name())
                                .arg(i++),
                                QVariant::fromValue(static_cast<int>(member))).toInt());
        }
        else{
            member = sets.value(QString("field_%1_%2").arg(typeid(member).name())
                                .arg(i++),
                                QVariant::fromValue(member))
                    .template value<Type>();
        }
    });
    sets.endGroup();
}
}

#endif

#endif // AUTOSAVER_H
