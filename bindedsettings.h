#ifndef BINDEDSETTINGS_H
#define BINDEDSETTINGS_H
#include <QObject>
#include <QTabWidget>
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
#include <QLabel>
#include <QDir>
#include <QDebug>
#include <functional>
#include "sbvariantsaver.h"


class BindedSettings: public QObject
{
    Q_OBJECT
public:
    static constexpr bool debugBs{false};
    enum class IntType{
        decimal = 10,
        hex = 16,
        binar = 1,
        notInt = 10
    };
    enum class WriteAlgorithm{
        noNotifyOnWrite,
        notifyOnWrite
    };

    Q_ENUM(IntType)
    explicit BindedSettings(QObject* parent = nullptr);
    virtual ~BindedSettings(){}
    void save();
    void load();
    template <class T> T* createBinded(const char* propertyName){
        T* wt = new T();
        bindWtToProp(wt, propertyName);
        return wt;
    }
    bool addEnumTranslation(std::function<QString(QVariant)> enumToStr, std::function<QVariant(QString)>strToEnum, const char* propertyName);
    bool bindWtToProp(QLineEdit* targetWt, const char* propertyName);
    bool bindWtToProp(QLineEdit* targetWt, const char* propertyName, IntType type);
    bool bindWtToProp(QSpinBox* targetWt, const char* propertyName);
    bool bindWtToProp(QDoubleSpinBox* targetWt, const char* propertyName);
    bool bindWtToProp(QCheckBox* targetWt, const char* propertyName);
    bool bindWtToProp(QComboBox* targetWt, const char* propertyName, WriteAlgorithm wa = WriteAlgorithm::noNotifyOnWrite);
    bool bindWtToProp(QTabWidget* targetWt, const char* propertyName, WriteAlgorithm wa = WriteAlgorithm::noNotifyOnWrite);
    bool bindWtToProp(QButtonGroup* targetWt, const char* propertyName, WriteAlgorithm wa = WriteAlgorithm::noNotifyOnWrite);
    bool bindWtToProp(QLabel* targetWt, const char* propertyName);

    template <typename Tval>bool stringTo(const QString& val, Tval& result, IntType type = IntType::notInt){
        bool isOk{false};
        if constexpr (std::is_same<Tval, uint>::value){
            result = val.toUInt(&isOk, static_cast<int>(type));
            return isOk;
        }
        if constexpr (std::is_same<Tval, int>::value){
            result = val.toInt(&isOk, static_cast<int>(type));
            return isOk;
        }
        if constexpr(std::is_same<Tval, double>::value){
            result = val.toDouble(&isOk);
            return isOk;
        }
        if constexpr(std::is_same<Tval, long>::value){
            result = val.toLong(&isOk);
            return isOk;
        }
        if constexpr(std::is_same<Tval, short>::value){
            result = val.toShort(&isOk);
            return isOk;
        }
        if constexpr(std::is_same<Tval, ushort>::value){
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
protected:




    bool checkSupportedTypes(QLineEdit* obj, const char* propertyName);
    bool checkSupportedTypes(QCheckBox* obj, const char* propertyName);
    bool checkSupportedTypes(QSpinBox* obj, const char* propertyName);
    bool checkSupportedTypes(QDoubleSpinBox* obj, const char* propertyName);
    bool checkSupportedTypes(QButtonGroup* obj, const char* propertyName);
    bool checkSupportedTypes(QComboBox* obj, const char* propertyName);
    bool checkSupportedTypes(QTabWidget* obj, const char* propertyName);
    bool checkSupportedTypes(QLabel* obj, const char* propertyName);

    QList<QMetaType::Type> supportedLineEditTypes;
    QList<QMetaType::Type> supportedComboBoxTypes;
    QList<QMetaType::Type> supportedTabWidgetTypes;
    QList<QMetaType::Type> supportedCheckBoxTypes;
    QList<QMetaType::Type> supportedGroupButtonsTypes;
    QList<QMetaType::Type> supportedSpinBoxTypes;
    QList<QMetaType::Type> supportedDoubleSpinBoxTypes;
    QList<QMetaType::Type> supportedLabelsTypes;

    template<class T> QVariant getVariantEnumClass(int n){                  //TODO add check for registered T
          return QVariant::fromValue<T>(static_cast<T>(n));
    }

private:
    struct Translation{
        QMetaProperty mp;
        std::function<QString(QVariant)> enumToStr;
        std::function<QVariant(QString)> strToEnum;
    };
    QVector<Translation> enumTranslations;
    bool mpHasTranslation(QMetaProperty mp);
    Translation *getEnumTranslation(QMetaProperty mp);
    void fillSupportedLits();
    const QMetaObject* getMeta(const QObject* obj){
        return obj->metaObject();
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

    const QStringList propertiesList;


};


#endif // BINDEDSETTINGS_H
