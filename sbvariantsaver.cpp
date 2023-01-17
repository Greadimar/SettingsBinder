#include "sbvariantsaver.h"
//#include "../CommonTools/debugtools.h"

void SbVariantSaver::saveAllProperties(QObject *target, QString fileName)
{
    const QMetaObject* metaTarget = getMeta(target);
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

void SbVariantSaver::loadAllProperties(QObject *target, QString fileName)
{
    const QMetaObject* metaTarget = getMeta(target);
    QStringList propNames = collectPropsNames(target);
    QString setsName(fileName);
    QSettings qsets(setsName, QSettings::IniFormat);
    qsets.beginGroup(target->objectName());
    for (QString& propName: propNames){
        QMetaProperty metaProp = metaTarget->property(metaTarget->indexOfProperty(propName.toLocal8Bit().data()));
        QVariant value = qsets.value(propName, metaProp.read(target));
        if (!value.isNull()){
            metaProp.write(target, value);
        }
        QMetaMethod signal = metaProp.notifySignal();
    }
    qsets.endGroup();
}
void SbVariantSaver::saveVarVec(const QVector<QVariant> &vars, QString groupName, QString fileName)
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
    qsets.sync();
}

QVector<QVariant> SbVariantSaver::loadVarVec(QString groupName, QString fileName)
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

