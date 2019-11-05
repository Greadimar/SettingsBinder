#ifndef SSAVER_H
#define SSAVER_H
#include <QDir>
#include <QSettings>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QDebug>
constexpr bool debugSs{false};

namespace SSaver {
    void save(QObject *target,
                        QString fileName = QDir::currentPath() + "/settings.ini");
    void load(QObject *target,
                        QString fileName = QDir::currentPath() + "/settings.ini");
    void saveVec(const QVector<QVariant> &vars, QString groupName = "",
                 QString fileName = QDir::currentPath() + "/settings.ini");
    QVector<QVariant> loadVec(QString groupName = "", QString fileName = QDir::currentPath() + "/settings.ini");

    void loadFromPath(QObject *target, QString path, QString extraGroupKey = "");
    /*void saveChildren(QObject *target);
    void loadChildren(QObject *target);*/
    inline const QMetaObject* getMeta(QObject* obj){
        return obj->metaObject();
    }
    inline QString strFromChars(const char* array){
        return QString::fromUtf8(array);
    }
    inline QStringList collectPropsNames(const QObject* obj){
        const QMetaObject* metaObject = obj->metaObject();
        QStringList properties;
        for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
            properties   << strFromChars(metaObject->property(i).name());
        return properties;
    }

}


#endif // SSAVER_H
