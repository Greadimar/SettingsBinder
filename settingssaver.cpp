#include "settingssaver.h"


SettingsSaver::SettingsSaver(QObject *parent) : QObject(parent)
{
}

void SettingsSaver::save(QObject* target, QString extraGroupKey)
{
    saveWithPath(target, QDir::currentPath(), extraGroupKey);
}

void SettingsSaver::load(QObject *target, QString extraGroupKey)
{
    loadFromPath(target, QDir::currentPath(), extraGroupKey);
}

void SettingsSaver::saveWithPath(QObject *target, QString path, QString extraGroupKey)
{
    const QMetaObject* metaTarget = getMeta(target);
    propertiesList = collectPropsNames(target);

    if (debugSs) qDebug()<< Q_FUNC_INFO << " saving properties";
    QString setsName(path + "/" +QString::fromUtf8(metaTarget->className()) + ".ini");
    QSettings qsets(setsName, QSettings::IniFormat);
    int offset = metaTarget->propertyOffset();
    int end = metaTarget->propertyCount();
    qsets.beginGroup(QString::fromLocal8Bit("Settings_") + extraGroupKey);
    for (int i = offset; i < end; i++){
       QMetaProperty metaProp = metaTarget->property(i);
       if (metaProp.isEnumType()){
           QMetaEnum me = metaProp.enumerator();
           QString str = strFromChars(me.key(metaProp.read(target).toInt()));
           qsets.setValue(strFromChars(metaProp.name()), str);
           continue;
       }
       qsets.setValue(strFromChars(metaProp.name()), QVariant::fromValue(metaProp.read(target)));
    }
    qsets.endGroup();
}

void SettingsSaver::loadFromPath(QObject *target, QString path, QString extraGroupKey)
{
    const QMetaObject* metaTarget = getMeta(target);
    propertiesList = collectPropsNames(target);
    if (debugSs) qDebug()<<Q_FUNC_INFO<<" ss load";
    QStringList propNames = collectPropsNames(target);
    QString setsName(path + "/" +metaTarget->className() + ".ini");
    QSettings qsets(setsName, QSettings::IniFormat);
    qsets.beginGroup(QString::fromLocal8Bit("Settings_")+ extraGroupKey);
    for (QString& propName: propNames){
        QMetaProperty metaProp = metaTarget->property(metaTarget->indexOfProperty(propName.toLocal8Bit().data()));
        if (debugSs) qDebug()<<Q_FUNC_INFO<<"isStored, isEnum"<<metaProp.isStored(target)<<metaProp.isEnumType();
        QVariant value = qsets.value(propName);
        if (debugSs) qDebug()<<Q_FUNC_INFO<<" what is loading now: "<<value;
        if (!value.isNull()){
            metaProp.write(target, value);
        }
        QMetaMethod signal = metaProp.notifySignal();
        if (debugSs) qDebug()<<Q_FUNC_INFO<<" check loading signal: type:"<<signal.typeName() << ", is valid: "<<signal.isValid()<<", signature: " <<signal.methodSignature();
        bool emitted = signal.invoke(target);
        if (debugSs) qDebug()<<Q_FUNC_INFO<<" signal emitted: "<<emitted;
    }
    qsets.endGroup();
}
