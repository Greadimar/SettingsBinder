#ifndef BINDEDSETTINGS_H
#define BINDEDSETTINGS_H
#include <QObject>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QButtonGroup>
#include <QComboBox>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QSettings>
#include <QDir>
#include <QDebug>
#include <functional>
constexpr bool debugBs{false};
class BindedSettings: public QObject
{
    Q_OBJECT
public:
    enum class IntType{
        decimal = 10,
        hex = 16,
        binar = 1,
        notInt = 10
    };
    Q_ENUM(IntType)
    BindedSettings(QObject* parent = nullptr);
    bool bindWtToProp(QLineEdit* targetWt, const char* propertyName);
    bool bindWtToProp(QSpinBox* targetWt, const char* propertyName);
    bool bindWtToProp(QDoubleSpinBox* targetWt, const char* propertyName);
    bool bindWtToProp(QCheckBox* targetWt, const char* propertyName);
    bool bindWtToProp(QComboBox* targetWt, const char* propertyName);
    template <typename Tenumclass> bool bindButtonGroupAsEnum(QButtonGroup* targetBtnGrp, const char* propertyName){
        // T ENUM CLASS SHOULD BE REGISTERED IN Q_DECLARE_METATYPE;
        // BUTTONS IN GROUP SHOULD HAVE SAME ID as casted ENUM CLASS VALUE
        QButtonGroup* btnGrp = targetBtnGrp;
        QMetaProperty mp = metaObject()->property(metaObject()->indexOfProperty(propertyName));

        if (!mp.isStored(this)){
            qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetBtnGrp->metaObject()->className()<<" to "<<propertyName << " - no property found";
            return false;
        }
        if (!checkSupportedTypes(btnGrp, propertyName)){
            qWarning()<<Q_FUNC_INFO<<": can't bind "<<targetBtnGrp->metaObject()->className()<<" to "<<propertyName << " - wrong type of property";
            return false;
        }
        auto reader = [=](QObject* obj)->bool{
            QButtonGroup* group = qobject_cast<QButtonGroup*>(obj);
            int id;
            if (mp.isEnumType()){
                id = static_cast<int>(mp.read(this).value<Tenumclass>());
            }
            else if (mp.type() == QVariant::Int){
                id = mp.read(this).toInt();
            }
            else {
                return false;
            }
            if (id < group->buttons().size()){
                group->button(id)->setChecked(true);
                return true;
            }
            return false;
        };
        reader(btnGrp);
        bindedMap.insert(QString::fromUtf8(propertyName), ReaderStruct(btnGrp,reader));
        QMetaMethod signal = mp.notifySignal();
        QMetaMethod slot = metaObject()->method(metaObject()->indexOfSlot("invokeReader()"));
        connect(this, signal, this, slot);
        if (mp.isWritable()){
            connect(btnGrp, qOverload<int>(&QButtonGroup::buttonClicked), this, [=](){
                if (debugBs) qDebug()<<Q_FUNC_INFO<<"on QBtnGroup changing property";
                QVariant var;
                if (mp.isEnumType()){
                    var = QVariant::fromValue<Tenumclass>(static_cast<Tenumclass>(btnGrp->checkedId()));
                    //var = QVariant(btnGrp->checkedId());
                }
                else if(mp.type() == QVariant::Type::Int){
                    var = QVariant(btnGrp->checkedId());
                }
                else{
                    return;
                }
                mp.write(this, var);
                if (debugBs) qDebug()<<Q_FUNC_INFO<<" written grp state"<<mp.read(this);

            });
        }
        else{
            qDebug()<<Q_FUNC_INFO<<": can't bind writing "<<targetBtnGrp->metaObject()->className()<<" to "<<propertyName << " - property is not writable";
        }
        return true;
    }
    template <class test> void lol(){}
    template <typename Tval>bool stringTo(const QString& val, Tval& result, IntType type = IntType::notInt){
        bool isOk{false};
        if (std::is_same<Tval, uint>::value){
            result = val.toUInt(&isOk, static_cast<int>(type));
            return isOk;
        }
        if (std::is_same<Tval, int>::value){
            result = val.toInt(&isOk, static_cast<int>(type));
            return isOk;
        }
        if (std::is_same<Tval, double>::value){
            result = val.toDouble(&isOk);
            return isOk;
        }
        if (std::is_same<Tval, long>::value){
            result = val.toLong(&isOk);
            return isOk;
        }
        if (std::is_same<Tval, short>::value){
            result = val.toShort(&isOk);
            return isOk;
        }
        if (std::is_same<Tval, ushort>::value){
            result = val.toUShort(&isOk);
            return isOk;
        }
        qWarning()<<Q_FUNC_INFO<<": can't convert string to "<<std::type_info(result);
        return isOk;
    }
    bool stringToVariant(const QString& val, QVariant& result, IntType type = IntType::notInt);
    bool stringFromVariant(const QVariant& val, QString& result, IntType type = IntType::notInt);
    static void setIntTypePropertyTo(QLineEdit* le, IntType t){
        le->setProperty("IntType", QVariant::fromValue<IntType>(t));
    }

    struct ReaderStruct{
        ReaderStruct(QObject* obj, std::function<bool(QObject* obj)> reader):
            obj(obj), reader(reader){}
        ReaderStruct(){isEmpty = true;}
        bool isEmpty = false;
        QObject* obj;
        std::function<bool(QObject* obj)> reader;
    };

    QMap<QString, ReaderStruct> bindedMap;
public slots:
    void invokeReader();
private:
    bool checkSupportedTypes(QLineEdit* obj, const char* propertyName);
    bool checkSupportedTypes(QCheckBox* obj, const char* propertyName);
    bool checkSupportedTypes(QSpinBox* obj, const char* propertyName);
    bool checkSupportedTypes(QDoubleSpinBox* obj, const char* propertyName);
    bool checkSupportedTypes(QButtonGroup* obj, const char* propertyName);
    bool checkSupportedTypes(QComboBox* obj, const char* propertyName);

    QList<QMetaType::Type> supportedLineEditTypes;
    QList<QMetaType::Type> supportedComboBoxTypes;
    QList<QMetaType::Type> supportedCheckBoxTypes;
    QList<QMetaType::Type> supportedGroupButtonsTypes;
    QList<QMetaType::Type> supportedSpinBoxTypes;
    QList<QMetaType::Type> supportedDoubleSpinBoxTypes;
public:
    void save();
    void load();
    const QMetaObject* getMeta(const QObject* obj){
        return obj->metaObject();
    }
    template<class T> QVariant getVariantEnumClass(int n){                  //TODO add check for registered T
          return QVariant::fromValue<T>(static_cast<T>(n));
    }
    const QStringList collectPropsNames(const QObject* obj){
        const QMetaObject* metaObject = obj->metaObject();
        QStringList properties;
        for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
            properties << strFromChars(metaObject->property(i).name());
        return properties;
    }
    static QString strFromChars(const char* array){
        return QString::fromUtf8(array);
    }
    static char* charsFromStr(const QString& str){
        return QByteArray(str.toLocal8Bit()).data();
    }

    const QStringList propertiesList;


};


#endif // BINDEDSETTINGS_H
