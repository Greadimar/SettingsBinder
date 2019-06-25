#include "bindedsettings.h"



BindedSettings::BindedSettings(QObject *parent): QObject(parent)
{
    fillSupportedLits();
}



bool BindedSettings::bindWtToProp(QLineEdit *targetWt, const char *propertyName)
{
    QLineEdit* le = targetWt;
    //getting metaproperty
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (debugBs) qDebug() << metaObject()->indexOfProperty(propertyName);
    if (!mp.isStored(this)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - no property found";
        return false;
    }
    if (!checkSupportedTypes(le, propertyName)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - wrong type of property";
        return false;
    }
    //getting intType modifier
    IntType t = IntType::notInt;
    QVariant intTypeVar = le->property("IntType");
    if (!intTypeVar.isNull()){
        t = intTypeVar.value<IntType>();
    }
    //setting up readValue lamda
    auto reader = [=](QObject* obj) -> bool{
        if (debugBs) qDebug()<<Q_FUNC_INFO<<" reading val from settings " << mp.read(this);
        QString newText;
        QLineEdit* target = qobject_cast<QLineEdit*>(obj);
        if (stringFromVariant(mp.read(this), newText, t)){
            target->setText(newText);
            return true;
        }
        return false;
    };
    //setting up value for settings;
    reader(le);
    //memorizing reading lamda, object for reading, and property name in stored map
    bindedMap.insert(QString::fromUtf8(propertyName), ReaderStruct(le,reader));
    //connecting property notifiedSignal with reader lambda
    QMetaMethod signal = mp.notifySignal();
    QMetaMethod slot = metaObject()->method(metaObject()->indexOfSlot("invokeReader()"));
    connect(this, signal, this, slot, Qt::DirectConnection);
    //connecting textEdited and write method of property
    if (mp.isWritable()){
        connect(le, &QLineEdit::textChanged, this, [=](){
            if (debugBs) qDebug()<<Q_FUNC_INFO<<"on textEdit changing property";
            QVariant var(mp.type());
            if (stringToVariant(le->text(), var, t)){
                mp.write(this, var);
            }
        });
    }
    else{
        qDebug()<<Q_FUNC_INFO<<": can't bind writing "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - property is not writable";
    }
    return true;
}
bool BindedSettings::bindWtToProp(QLineEdit *targetWt, const char *propertyName, IntType type){
    setIntTypePropertyTo(targetWt, type);
    bindWtToProp(targetWt, propertyName);
    return true;
}
bool BindedSettings::bindWtToProp(QSpinBox *targetWt, const char *propertyName)
{
    QSpinBox* sb = targetWt;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (!mp.isStored(this)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - no property found";
        return false;
    }
    if (!checkSupportedTypes(sb, propertyName)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - wrong type of property";
        return false;
    }
    auto reader = [=](QObject* obj)->bool{
        QSpinBox* target = qobject_cast<QSpinBox*>(obj);
        if (target == nullptr) return false;
        target->setValue(mp.read(this).toInt());
        return true;
    };
    reader(sb);
    bindedMap.insert(QString::fromUtf8(propertyName), ReaderStruct(sb,reader));
    QMetaMethod signal = mp.notifySignal();
    QMetaMethod slot = metaObject()->method(metaObject()->indexOfSlot("invokeReader()"));
    connect(this, signal, this, slot);
    if (mp.isWritable()){
        connect(sb, qOverload<int>(&QSpinBox::valueChanged), this, [=](){
            if (debugBs) qDebug()<<Q_FUNC_INFO<<"on spinBox changing property";
            QVariant var(sb->value());
            mp.write(this, var);
        });
    }
    else{
        qDebug()<<Q_FUNC_INFO<<": can't bind writing "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - property is not writable";
    }
    return true;
}

bool BindedSettings::bindWtToProp(QDoubleSpinBox *targetWt, const char *propertyName)
{
    QDoubleSpinBox* dsb = targetWt;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));

    if (!mp.isStored(this)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - no property found";
        return false;
    }
    if (!checkSupportedTypes(dsb, propertyName)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - wrong type of property";
        return false;
    }
    auto reader = [=](QObject* obj)->bool{
        QDoubleSpinBox* target = qobject_cast<QDoubleSpinBox*>(obj);
        if (target == nullptr) return false;
        target->setValue(mp.read(this).toDouble());
        return true;
    };
    reader(dsb);
    bindedMap.insert(QString::fromUtf8(propertyName), ReaderStruct(dsb,reader));
    QMetaMethod signal = mp.notifySignal();
    QMetaMethod slot = metaObject()->method(metaObject()->indexOfSlot("invokeReader()"));
    connect(this, signal, this, slot);
    if (mp.isWritable()){
        connect(dsb, qOverload<double>(&QDoubleSpinBox::valueChanged), this, [=](){
            if (debugBs) qDebug()<<Q_FUNC_INFO<<"on double SpinBox changing property";
            QVariant var(dsb->value());
            mp.write(this, var);
        });
    }
    else{
        qDebug()<<Q_FUNC_INFO<<": can't bind writing "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - property is not writable";
    }
    return true;
}

bool BindedSettings::bindWtToProp(QCheckBox *targetWt, const char *propertyName)
{
    QCheckBox* chb = targetWt;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (!mp.isStored(this)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - no property found";
        return false;
    }
    if (!checkSupportedTypes(chb, propertyName)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - wrong type of property";
        return false;
    }
    auto reader = [=](QObject* obj)->bool{
        QCheckBox* target = qobject_cast<QCheckBox*>(obj);
        if (target == nullptr) return false;
        target->setChecked(mp.read(this).toBool());
        return true;
    };
    reader(chb);
    bindedMap.insert(QString::fromUtf8(propertyName), ReaderStruct(chb,reader));
    QMetaMethod signal = mp.notifySignal();
    QMetaMethod slot = metaObject()->method(metaObject()->indexOfSlot("invokeReader()"));
    connect(this, signal, this, slot);
    if (mp.isWritable()){
        connect(chb, &QCheckBox::toggled, this, [=](){
            if (debugBs) qDebug()<<Q_FUNC_INFO<<"on QCheckBox changing property";
            QVariant var(chb->isChecked());
            mp.write(this, var);
        });
    }
    else{
        qDebug()<<Q_FUNC_INFO<<": can't bind writing "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - property is not writable";
    }

    return true;
}

bool BindedSettings::bindWtToProp(QComboBox *targetWt, const char *propertyName)
{
    QComboBox* cb = targetWt;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (!mp.isStored(this)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - no property found";
        return false;
    }
    if (!checkSupportedTypes(cb, propertyName)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - wrong type of property";
        return false;
    }
    if (mp.isEnumType()){
        QMetaEnum me = mp.enumerator();
        for (int i = 0; i < me.keyCount(); i++){
            const char* s = me.key(i);
            QString name = strFromChars(s);
            cb->insertItem(i, name);
        }
    }
    auto reader = [=](QObject* obj)->bool{
        QComboBox* target = qobject_cast<QComboBox*>(obj);
        if (target == nullptr) return false;
        if (mp.isEnumType()){
            QMetaEnum me = mp.enumerator();
            QString str = strFromChars(me.key(mp.read(this).toInt()));
            target->setCurrentText(str);
            return true;
        }
        if (mp.type() == QVariant::Int){
            target->setCurrentIndex(mp.read(this).toInt());
            return true;
        }
        if (mp.type() == QVariant::UInt){
            target->setCurrentIndex(mp.read(this).toUInt());
            return true;
        }
        if (mp.type() == QVariant::String){
            target->setCurrentText(mp.read(this).toString());
        }

        return true;
    };
    reader(cb);
    bindedMap.insert(QString::fromUtf8(propertyName), ReaderStruct(cb,reader));
    QMetaMethod signal = mp.notifySignal();
    QMetaMethod slot = metaObject()->method(metaObject()->indexOfSlot("invokeReader()"));
    connect(this, signal, this, slot);
    if (mp.isWritable()){
        connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), this, [=](){
            if (debugBs) qDebug()<<Q_FUNC_INFO<<"on QComboBox changing property";
            QVariant var;
            if (mp.isEnumType()){
                var = QVariant(cb->currentText());
            }
            else if (mp.type() == QVariant::Int){
                var = QVariant(cb->currentIndex());
            }
            else if (mp.type() == QVariant::String){
                var = QVariant(cb->currentText());
            }
            else if (mp.type() == QVariant::UInt){
                var = QVariant(cb->currentText());
            }

            mp.write(this, var);
        });
    }
    else{
        qDebug()<<Q_FUNC_INFO<<": can't bind writing "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - property is not writable";
    }

    return true;
}

bool BindedSettings::bindWtToProp(QButtonGroup *targetWt, const char *propertyName)
{
    QButtonGroup* btnGrp = targetWt;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (!mp.isStored(this)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - no property found";
        return false;
    }
    if (!checkSupportedTypes(btnGrp, propertyName)){
        qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - wrong type of property";
        return false;
    }

    auto reader = [=](QObject* target)->bool{
        QButtonGroup* bg = qobject_cast<QButtonGroup*>(target);
        if (bg == nullptr) return false;
        if (mp.type() == QVariant::Int || mp.type() == QVariant::UInt) {
            int idx = mp.read(this).toInt();
            if (idx >= bg->buttons().size() || idx < 0){
                qWarning()<<Q_FUNC_INFO<<": can't read value, idx is bigger than count of buttons or < 0";
                return false;
            }
            bg->buttons()[idx]->setChecked(true);
            return true;
        }
        return true;
    };
    reader(btnGrp);
    bindedMap.insert(QString::fromUtf8(propertyName), ReaderStruct(btnGrp,reader));
    QMetaMethod signal = mp.notifySignal();
    QMetaMethod slot = metaObject()->method(metaObject()->indexOfSlot("invokeReader()"));
    connect(this, signal, this, slot);
    if (mp.isWritable()){
        connect(btnGrp, qOverload<int>(&QButtonGroup::buttonClicked), this, [=](){
            if (debugBs) qDebug()<<Q_FUNC_INFO<<"on QComboBox changing property";
            QVariant var;
            if (mp.isEnumType()){
                QMetaEnum me = mp.enumerator();
                QString str = strFromChars(me.key(btnGrp->checkedId()));
                var = QVariant(str);
            }
            else if (mp.type() == QVariant::Int){
                var = QVariant(btnGrp->checkedId());
            }

            else if (mp.type() == QVariant::UInt){
                var = QVariant(btnGrp->checkedId());
            }

            mp.write(this, var);
        });
    }
    else{
        qDebug()<<Q_FUNC_INFO<<": can't bind writing "<<targetWt->metaObject()->className()<<" to "<<propertyName << " - property is not writable";
    }

    return true;
}


bool BindedSettings::stringToVariant(const QString &val, QVariant &result, IntType type)
{
    QVariant::Type t = result.type();
    bool isOk{false};
    if (t == QVariant::Type::UInt){
        result = QVariant::fromValue<uint>(val.toUInt(&isOk, static_cast<int>(type)));
        return isOk;
    }
    if (t == QVariant::Type::Int){
        result = QVariant::fromValue<int>(val.toInt(&isOk, static_cast<int>(type)));
        return isOk;
    }
    if (t == QVariant::Type::Double){
        result = QVariant::fromValue<double>(val.toDouble(&isOk));
        return isOk;
    }
    if (static_cast<QMetaType::Type>(t) == QMetaType::Long){
        result = QVariant::fromValue<long>(val.toLong(&isOk));
        return isOk;
    }
    if (static_cast<QMetaType::Type>(t) == QMetaType::Short){
        result = QVariant::fromValue<short>(val.toShort(&isOk));
        return isOk;
    }
    if (static_cast<QMetaType::Type>(t) == QMetaType::UShort){
        result = QVariant::fromValue<ushort>(val.toUShort(&isOk));
        return isOk;
    }
    if (t == QVariant::Type::String){
        result = QVariant(val);
        isOk = true;
        return isOk;
    }
    return isOk;
}

bool BindedSettings::stringFromVariant(const QVariant &val, QString &result, BindedSettings::IntType type)
{
    QVariant::Type t = val.type();
    bool isOk{false};
    if (t == QVariant::Type::UInt){
        result = QString::number(val.toUInt(), static_cast<int>(type));
        if (type == IntType::hex){
            while (result.count() < 8) result.prepend("0");
            //result.prepend("0x");
        }
        return isOk = true;
    }
    if (t == QVariant::Type::Int){
        result = QString::number(val.toInt(), static_cast<int>(type));
        return isOk = true;
    }
    if (t == QVariant::Type::Double){
        result = QString::number(val.toDouble());
        return isOk = true;
    }
    if (static_cast<QMetaType::Type>(t) == QMetaType::Long){
        result = QString::number(val.toLongLong());
        return isOk = true;
    }
    if (static_cast<QMetaType::Type>(t) == QMetaType::Short){
        result = QString::number(val.toInt());
        return isOk = true;
    }
    if (static_cast<QMetaType::Type>(t) == QMetaType::UShort){
        result = QString::number(val.toUInt());
        return isOk = true;
    }
    if (t == QVariant::Type::String){
        result = val.toString();
        return isOk = true;
    }
    return isOk;
}

bool BindedSettings::checkSupportedTypes(QLineEdit *obj, const char *propertyName)
{
    if (obj == nullptr) return false;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (supportedLineEditTypes.contains(static_cast<QMetaType::Type>(mp.type()))) return true;
    return false;

}

bool BindedSettings::checkSupportedTypes(QCheckBox *obj, const char *propertyName)
{
    if (obj == nullptr) return false;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (supportedCheckBoxTypes.contains(static_cast<QMetaType::Type>(mp.type()))) return true;
    return false;
}

bool BindedSettings::checkSupportedTypes(QSpinBox *obj, const char *propertyName)
{
    if (obj == nullptr) return false;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (supportedSpinBoxTypes.contains(static_cast<QMetaType::Type>(mp.type()))) return true;
    return false;
}

bool BindedSettings::checkSupportedTypes(QDoubleSpinBox *obj, const char *propertyName)
{
    if (obj == nullptr) return false;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (supportedDoubleSpinBoxTypes.contains(static_cast<QMetaType::Type>(mp.type()))) return true;
    return false;
}

bool BindedSettings::checkSupportedTypes(QButtonGroup *obj, const char *propertyName)
{
    if (obj == nullptr) return false;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    QMetaType::Type t = static_cast<QMetaType::Type>(mp.type());
    if (QMetaType::isRegistered(t) && supportedGroupButtonsTypes.contains(t)) return true;
    return false;
}

bool BindedSettings::checkSupportedTypes(QComboBox *obj, const char *propertyName)
{
    if (obj == nullptr) return false;
    QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));
    if (supportedComboBoxTypes.contains(static_cast<QMetaType::Type>(mp.type()))) return true;
    return false;
}

void BindedSettings::fillSupportedLits()
{
    supportedLineEditTypes << QMetaType::Type(QMetaType::QString) << QMetaType::Type(QMetaType::Int) << QMetaType::Type(QMetaType::UInt) << QMetaType::Type(QMetaType::Double)<<
                              QMetaType::Type(QMetaType::Short) << QMetaType::Type(QMetaType::UShort) << QMetaType::Type(QMetaType::Long);
    supportedCheckBoxTypes << QMetaType::Type(QMetaType::Bool);
    supportedComboBoxTypes << QMetaType::Type(QMetaType::QString) << QMetaType::Type(QMetaType::Int) << QMetaType::Type(QMetaType::UInt);
    supportedSpinBoxTypes << QMetaType::Type(QMetaType::Int);
    supportedDoubleSpinBoxTypes << QMetaType::Type(QMetaType::Double);
    supportedGroupButtonsTypes << QMetaType::Type(QMetaType::Int);

}

void BindedSettings::invokeReader()
{
    int signalIdx = QObject::senderSignalIndex();
    if (signalIdx == -1){
        if (debugBs) qDebug()<<Q_FUNC_INFO<<" was called directly, not from slot";
    }
    QMetaMethod metaSignal = QObject::sender()->metaObject()->method(signalIdx);
    QString propName = QString::fromStdString(metaSignal.name().toStdString()).chopped(7);        //7 means "changed" of signal name;
    ReaderStruct rs = bindedMap.value(propName);
    if (rs.isEmpty){
        if (debugBs) qDebug()<<Q_FUNC_INFO<<" no binded value to such property";
        return;
    }
    if (!rs.reader(rs.obj))
        if (debugBs) qDebug()<<Q_FUNC_INFO << " reader returned false, can't read property to object";
}



void BindedSettings::save()
{
    if (debugBs) qDebug()<<Q_FUNC_INFO;
    SSaver::save(this);
    /*
    if (debugBs) qDebug()<< Q_FUNC_INFO << " saving properties";
    QString setsName(QDir::currentPath() + "/" + QString::fromUtf8(metaObject()->className()) + ".ini");
    QSettings qsets(setsName, QSettings::IniFormat);
    int offset = metaObject()->propertyOffset();
    int end = metaObject()->propertyCount();
    qsets.beginGroup("Settings");
    for (int i = offset; i < end; i++){
       QMetaProperty metaProp = metaObject()->property(i);
       if (metaProp.isEnumType()){
           qsets.setValue(strFromChars(metaProp.name()), QVariant(metaProp.read(this)).toInt());
           continue;
       }
       qsets.setValue(strFromChars(metaProp.name()), QVariant::fromValue(metaProp.read(this)));
    }
    qsets.endGroup();*/
}

void BindedSettings::load()
{
    if (debugBs) qDebug()<<Q_FUNC_INFO;
    SSaver::load(this);
    /*
    QStringList propNames = collectPropsNames(this);
    QString setsName(QDir::currentPath() + "/" + QString::fromUtf8(metaObject()->className()) + ".ini");
    QSettings qsets(setsName, QSettings::IniFormat);
    qsets.beginGroup("Settings");
    if (debugBs) qDebug()<<Q_FUNC_INFO<<((metaObject() == nullptr)? "not meta": "metaExists");
    if (debugBs) qDebug()<<Q_FUNC_INFO<<"propertyCount"<<metaObject()->propertyCount();
    for (QString& propName: propNames){
        qDebug() << propName.data() << propName.toLocal8Bit().data();
        if (debugBs) qDebug()<<Q_FUNC_INFO<<"propName, index of Prop" << propName << metaObject()->indexOfProperty(propName.toLocal8Bit().data());
        QMetaProperty metaProp = metaObject()->property(metaObject()->indexOfProperty(propName.toLocal8Bit().data()));
        if (debugBs) qDebug()<<Q_FUNC_INFO<<"isStored, isEnum"<<metaProp.isStored(this)<<metaProp.isEnumType();
        QVariant value = qsets.value(propName);
        if (debugBs) qDebug()<<Q_FUNC_INFO<<" what is loading now: "<<value<<propName;
        if (metaProp.isEnumType()){
            if (debugBs) qDebug()<<Q_FUNC_INFO<<" trying to load enumType property";
            if (debugBs){
                qDebug()<<Q_FUNC_INFO<<" here are all methods";
                for (int j = metaObject()->methodOffset(); j < metaObject()->methodCount(); j++){
                    qDebug()<<Q_FUNC_INFO<<"method: "<<QString::number(j)<<" with name: "<<metaObject()->method(j).name();
                }
            }
            QString methodName(propName + "Variant" + "(int)");
            if (debugBs) qDebug()<<Q_FUNC_INFO<<" what am i invoking:"<<methodName;
            int idxOfMethod = metaObject()->indexOfMethod(QMetaObject::normalizedSignature(methodName.toLocal8Bit().data()));
            if (debugBs) qDebug()<<Q_FUNC_INFO<<" idx of found method"<< idxOfMethod;
            QMetaMethod mm = metaObject()->method(idxOfMethod);
            QVariant enumClassVar;                                                                          //this is where we get result variant from invoking getVariant
            bool invoked{false};
            invoked = mm.invoke(this, Q_RETURN_ARG(QVariant, enumClassVar), Q_ARG(int, value.toInt()));
            bool written{false};
            metaProp.write(this, enumClassVar);
            if (debugBs) qDebug()<<Q_FUNC_INFO<<" method is valid, is invoked, property written"<<mm.isValid() << invoked << written;
        }
        else{
            if (!value.isNull()){
                metaProp.write(this, value);
            }
        }
        QMetaMethod signal = metaProp.notifySignal();
        if (debugBs) qDebug()<<Q_FUNC_INFO<<" check loading signal: type:"<<signal.typeName() << ", is valid: "<<signal.isValid()<<", signature: " <<signal.methodSignature();
        bool emitted = signal.invoke(this);
        if (debugBs) qDebug()<<Q_FUNC_INFO<<" signal emitted: "<<emitted;
    }
    qsets.endGroup();
    */
}



