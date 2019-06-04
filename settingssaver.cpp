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
    this->target = target;
    const QMetaObject* metaTarget = getMeta(target);
    propertiesList = collectPropsNames(target);

    if (debugSs) qDebug()<< Q_FUNC_INFO << " saving properties";
    QString setsName(path + "/autosettings.ini");
    QSettings qsets(setsName, QSettings::IniFormat);
    int offset = metaTarget->propertyOffset();
    int end = metaTarget->propertyCount();
    qsets.beginGroup(QString::fromLocal8Bit("Settings_")+QString::fromLocal8Bit(metaTarget->className()) + extraGroupKey);
    for (int i = offset; i < end; i++){
       QMetaProperty metaProp = metaTarget->property(i);
       if (metaProp.isEnumType()){
           qsets.setValue(strFromChars(metaProp.name()), QVariant(metaProp.read(target)).toInt());
           continue;
       }
       qsets.setValue(strFromChars(metaProp.name()), QVariant::fromValue(metaProp.read(target)));
    }
    qsets.endGroup();
}

void SettingsSaver::loadFromPath(QObject *target, QString path, QString extraGroupKey)
{
    this->target = target;
    const QMetaObject* metaTarget = getMeta(target);
    propertiesList = collectPropsNames(target);
    if (debugSs) qDebug()<<Q_FUNC_INFO<<" ss load";
    QStringList propNames = collectPropsNames(target);
    QString setsName(path + "/autosettings.ini");
    QSettings qsets(setsName, QSettings::IniFormat);
    qsets.beginGroup(QString::fromLocal8Bit("Settings_")+QString::fromLocal8Bit(metaTarget->className()) + extraGroupKey);
    qDebug()<<propNames.size();
    for (QString& propName: propNames){
        QMetaProperty metaProp = metaTarget->property(metaTarget->indexOfProperty(charsFromStr(propName)));
        if (debugSs) qDebug()<<Q_FUNC_INFO<<"isStored, isEnum"<<metaProp.isStored(target)<<metaProp.isEnumType();
        QVariant value = qsets.value(propName);
        if (debugSs) qDebug()<<Q_FUNC_INFO<<" what is loading now: "<<value;
        if (metaProp.isEnumType()){
            if (debugSs) qDebug()<<Q_FUNC_INFO<<" trying to load enumType property";
            if (debugSs){
                qDebug()<<Q_FUNC_INFO<<" here are all methods";
                for (int j = metaTarget->methodOffset(); j < metaTarget->methodCount(); j++){
                    qDebug()<<Q_FUNC_INFO<<"method: "<<QString::number(j)<<" with name: "<<metaTarget->method(j).name();
                }
            }
            QString methodName(propName + "Variant");
            if (debugSs) qDebug()<<Q_FUNC_INFO<<" what am i invoking:"<<methodName;
            int idxOfMethod = metaTarget->indexOfMethod(QMetaObject::normalizedSignature(
                                                              charsFromStr(methodName + "(int)")));
            if (debugSs) qDebug()<<Q_FUNC_INFO<<" idx of found method"<< idxOfMethod;
            QMetaMethod mm = metaTarget->method(idxOfMethod);
            QVariant enumClassVar;                                                                          //this is where we get result variant from invoking getVariant
            bool invoked{false};
            invoked = mm.invoke(target, Q_RETURN_ARG(QVariant, enumClassVar), Q_ARG(int, value.toInt()));
            bool written{false};
            metaProp.write(target, enumClassVar);
            if (debugSs) qDebug()<<Q_FUNC_INFO<<" method is valid, is invoked, property written"<<mm.isValid() << invoked << written;
        }
        else{
            if (!value.isNull()){
                metaProp.write(target, value);
            }
        }
        QMetaMethod signal = metaProp.notifySignal();
        if (debugSs) qDebug()<<Q_FUNC_INFO<<" check loading signal: type:"<<signal.typeName() << ", is valid: "<<signal.isValid()<<", signature: " <<signal.methodSignature();
        bool emitted = signal.invoke(target);
        if (debugSs) qDebug()<<Q_FUNC_INFO<<" signal emitted: "<<emitted;
    }
    qsets.endGroup();
}
