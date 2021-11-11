#ifndef SETTINGS_H
#define SETTINGS_H
#include "bindedsettings.h"

//Q_ENUM(States)
namespace SomeNamespace {
Q_NAMESPACE
enum class NsEnumState
{
    nsState0,
    nsState1,
    nsState2
};
Q_ENUM_NS(NsEnumState)
};
class Settings: public BindedSettings
{
    Q_OBJECT
public:
    Settings(QObject* parent);
    enum class States{
        state0 = 0,
        state1 = 1,
        state2 = 2
    };
    Q_ENUM(States)
    //  qDebug()<<"enum"
    Q_PROPERTY(QString stringForLe READ stringForLe WRITE setStringForLe NOTIFY stringForLeChanged)
    Q_PROPERTY(int intForLe READ intForLe WRITE setIntForLe NOTIFY intForLeChanged)
    Q_PROPERTY(uint uintForLe READ uintForLe WRITE setUintForLe NOTIFY uintForLeChanged)
    Q_PROPERTY(uint hexedUintForLe READ hexedUintForLe WRITE setHexedUintForLe NOTIFY hexedUintForLeChanged)
    Q_PROPERTY(short shortForLe READ shortForLe WRITE setShortForLe NOTIFY shortForLeChanged)
    Q_PROPERTY(long longForLe READ longForLe WRITE setLongForLe NOTIFY longForLeChanged)
    Q_PROPERTY(double doubleForLe READ doubleForLe WRITE setDoubleForLe NOTIFY doubleForLeChanged)
    Q_PROPERTY(int intForSb READ intForSb WRITE setIntForSb NOTIFY intForSbChanged)
    Q_PROPERTY(double doubleForDsb READ doubleForDsb WRITE setDoubleForDsb NOTIFY doubleForDsbChanged)
    Q_PROPERTY(bool boolForChb READ boolForChb WRITE setBoolForChb NOTIFY boolForChbChanged)
    Q_PROPERTY(int intForCb READ intForCb WRITE setIntForCb NOTIFY intForCbChanged)
    Q_PROPERTY(States stateForGrpb READ stateForGrpb WRITE setStateForGrpb NOTIFY stateForGrpbChanged)
    Q_PROPERTY(SomeNamespace::NsEnumState stateForCb READ stateForCb WRITE setStateForCb NOTIFY stateForCbChanged)

    QString stringForLe() const;
    void setStringForLe(const QString &stringForLe);

    int intForLe() const;
    void setIntForLe(int intForLe);

    uint uintForLe() const;
    void setUintForLe(const uint &uintForLe);

    uint hexedUintForLe() const;
    void setHexedUintForLe(const uint &hexedUintForLe);

    short shortForLe() const;
    void setShortForLe(short shortForLe);

    long longForLe() const;
    void setLongForLe(long longForLe);

    double doubleForLe() const;
    void setDoubleForLe(double doubleForLe);

    int intForSb() const;
    void setIntForSb(int intForSb);

    double doubleForDsb() const;
    void setDoubleForDsb(double doubleForDsb);

    bool boolForChb() const;
    void setBoolForChb(bool boolForChb);

    int intForCb() const;
    void setIntForCb(int intForCb);

    Settings::States stateForGrpb() const;
    void setStateForGrpb(const States &stateForGrpb);
    Q_INVOKABLE QVariant stateForGrpbVariant(int val){
        return getVariantEnumClass<States>(val);
    }
    SomeNamespace::NsEnumState stateForCb() const;
    void setStateForCb(const SomeNamespace::NsEnumState &stateForCb);

signals:
    void stringForLeChanged();
    void intForLeChanged();
    void uintForLeChanged();
    void hexedUintForLeChanged();
    void shortForLeChanged();
    void longForLeChanged();
    void doubleForLeChanged();
    void intForSbChanged();
    void doubleForDsbChanged();
    void boolForChbChanged();
    void intForCbChanged();
    void stateForGrpbChanged();
    void stateForCbChanged();

private:
    QString m_stringForLe{"defaultText"};
    int m_intForLe{0};
    uint m_uintForLe{0};
    uint m_hexedUintForLe{0};
    short m_shortForLe{0};
    long m_longForLe{0};
    double m_doubleForLe{0.0};

    int m_intForSb{0};
    double m_doubleForDsb{0.0};
    bool m_boolForChb{true};
    int m_intForCb{0};
    States m_stateForGrpb{States::state0};
    SomeNamespace::NsEnumState m_stateForCb{SomeNamespace::NsEnumState::nsState1};
};


class LightSettings{
public:
    uint uintForLe;
    uint uintHexForLe;
    int intForLe;
    short shortForLe;
    QString strForLe;
    double dblForLe;
    bool boolForChb;
    bool boolForAct;
    enum class s {
        s1,
        s2,
        s3
    };
    int intForSb;
    double dblForDsb;
    QVector<QVariant> getVar(){
        return QVector<QVariant>{uintHexForLe, shortForLe, dblForLe, boolForChb, intForSb, dblForDsb, boolForAct};
    }
    void setVars(const QVector<QVariant>& v){
        if (v.size() < 7) return;
        uintHexForLe = v.at(0).toUInt();
        shortForLe = static_cast<short>(v.at(1).toInt());
        dblForLe = v.at(2).toDouble();
        boolForChb = v.at(3).toBool();
        intForSb = v.at(4).toInt();
        dblForDsb = v.at(5).toDouble();
        boolForAct = v.at(6).toBool();
    }
};

#endif // SETTINGS_H
