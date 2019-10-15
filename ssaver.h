#ifndef SSAVER_H
#define SSAVER_H
#include <QDir>
#include <QSettings>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QDebug>
constexpr bool debugSs{false};

namespace SSaver {
    void save(QObject *target, QString extraGroupKey = "");
    void load(QObject *target, QString extraGroupKey = "");
    void saveVec(QVector<QVariant>& vars, QString customName);
    QVector<QVariant> loadVec(QString customName);
    void saveWithPath(QObject *target, QString path, QString extraGroupKey = "");
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
