#ifndef AUTOSAVER_H
#define AUTOSAVER_H
#include <QSettings>
#include <QDir>
#include "simplereflex.h"
namespace SbAutoSaver{
template <class T>
void saveEveryField(T& t, const QString groupName = typeid (T()).name(), const QString filename = QDir::currentPath()+"/autosettings.ini")
{
    QSettings sets(filename, QSettings::IniFormat);
    sets.beginGroup(groupName);
    int i = 0;
    SimpleReflex::for_each_member(t, [&i, &sets](auto& member){
        sets.setValue(QString("field_%1_%2").arg(typeid(member).name()).arg(i++), member);
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
        member = sets.value(QString("field_%1_%2").arg(typeid(member).name())
                            .arg(i++), member).template value<typename std::remove_reference<decltype (member)>::type>();
    });
    sets.endGroup();
}
}



#endif // AUTOSAVER_H
