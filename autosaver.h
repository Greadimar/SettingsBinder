#ifndef AUTOSAVER_H
#define AUTOSAVER_H
#include <QSettings>
#include <QDir>
#include "simplereflex.h"
namespace AutoSaver{
template <class T>
void saveEveryField(T& t)
{
    QSettings sets(QDir::currentPath()+"/autosettings.ini", QSettings::IniFormat);
    sets.beginGroup("auto_saving");
    int i = 0;
    SimpleReflex::for_each_member(t, [&i, &sets](auto& member){
        sets.setValue(QString("field_%1_%2").arg(typeid(member).name()).arg(i), member);
    });
    sets.endGroup();
}
template <class T>
void loadEveryField(T &t)
{
    QSettings sets(QDir::currentPath()+"/autosettings.ini", QSettings::IniFormat);
    sets.beginGroup("auto_saving");
    int i = 0;
    SimpleReflex::for_each_member(t, [&i, &sets](auto& member) mutable{
        member = sets.value(QString("field_%1_%2").arg(typeid(member).name()).arg(i++)).value<typename std::remove_reference<decltype (member)>::type>();
    });
    sets.endGroup();
}
}



#endif // AUTOSAVER_H
