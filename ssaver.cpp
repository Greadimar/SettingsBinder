#include "ssaver.h"


void SSaver::save(QObject *target, QString fileName)
{
    const QMetaObject* metaTarget = getMeta(target);
    if (debugSs) qDebug()<< Q_FUNC_INFO << " saving properties";
    QSettings qsets(fileName, QSettings::IniFormat);
    int offset = metaTarget->propertyOffset();
    int end = metaTarget->propertyCount();
    qsets.beginGroup(target->objectName());
    for (int i = offset; i < end; i++){
       QMetaProperty metaProp = metaTarget->property(i);
       if (metaProp.isEnumType()){
           QMetaEnum me = metaProp.enumerator();
           QVariant var = metaProp.read(target);
           int n = var.toInt();
           const char* ch = me.valueToKey(n);
           QString str = strFromChars(ch);
           qsets.setValue(strFromChars(metaProp.name()), str);
           continue;
       }
       qsets.setValue(strFromChars(metaProp.name()), QVariant::fromValue(metaProp.read(target)));
    }
    qsets.endGroup();
}

void SSaver::load(QObject *target, QString fileName)
{
    const QMetaObject* metaTarget = getMeta(target);
    if (debugSs) qDebug()<<Q_FUNC_INFO<<" ss load";
    QStringList propNames = collectPropsNames(target);
    QString setsName(fileName);
    QSettings qsets(setsName, QSettings::IniFormat);
    qsets.beginGroup(target->objectName());
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
void SSaver::saveVec(const QVector<QVariant> &vars, QString groupName, QString fileName)
{
    QSettings qsets(fileName, QSettings::IniFormat);
    qsets.beginGroup(groupName);
    qsets.beginWriteArray("vars");
    for (int i = 0; i < vars.size(); i++){
        qsets.setArrayIndex(i);
        qsets.setValue(QString("var: %1").arg(i), vars.at(i));
    }
    qsets.endArray();
    qsets.endGroup();
}

QVector<QVariant> SSaver::loadVec(QString groupName, QString fileName)
{
    QSettings qsets(fileName, QSettings::IniFormat);
    qsets.beginGroup(groupName);
    QVector<QVariant> vars;
    int size = qsets.beginReadArray("vars");
    for (int i = 0; i < size; i++){
        qsets.setArrayIndex(i);
        vars.append(qsets.value(QString("var: %1").arg(i)));
    }
    qsets.endArray();
    qsets.endGroup();
    return vars;
}

