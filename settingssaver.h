#ifndef SETTINGSSAVER_H
#define SETTINGSSAVER_H
#include <QDir>
#include <QSettings>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QDebug>
constexpr bool debugSs{false};
class SettingsSaver: public QObject
{
    Q_OBJECT
public:
     SettingsSaver(QObject *parent);
        ~SettingsSaver(){
    }
    QObject* target;
    void save(QObject *target, QString extraGroupKey = "");
    void load(QObject *target, QString extraGroupKey = "");
    const QMetaObject* getMeta(QObject* obj){
        return obj->metaObject();
    }
    QStringList collectPropsNames(const QObject* obj){
        const QMetaObject* metaObject = obj->metaObject();
        QStringList properties;
        for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
            properties   << strFromChars(metaObject->property(i).name());
        return properties;
    }
    static QString strFromChars(const char* array){
        return QString::fromUtf8(array);
    }
    static char* charsFromStr(const QString& str){
        return QByteArray(str.toLocal8Bit()).data();
    }

    QStringList propertiesList;
};
#endif // SETTINGSSAVER_H
