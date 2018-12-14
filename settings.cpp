#include "settings.h"

Settings::Settings(QObject *parent): BindedSettings(parent)
{

}

QString Settings::stringForLe() const
{
    return m_stringForLe;
}

void Settings::setStringForLe(const QString &stringForLe)
{
    m_stringForLe = stringForLe;
}

int Settings::intForLe() const
{
    return m_intForLe;
}

void Settings::setIntForLe(int intForLe)
{
    m_intForLe = intForLe;
}

uint Settings::uintForLe() const
{
    return m_uintForLe;
}

void Settings::setUintForLe(const uint &uintForLe)
{
    m_uintForLe = uintForLe;
}

uint Settings::hexedUintForLe() const
{
    return m_hexedUintForLe;
}

void Settings::setHexedUintForLe(const uint &hexedUintForLe)
{
    m_hexedUintForLe = hexedUintForLe;
}

short Settings::shortForLe() const
{
    return m_shortForLe;
}

void Settings::setShortForLe(short shortForLe)
{
    m_shortForLe = shortForLe;
}

long Settings::longForLe() const
{
    return m_longForLe;
}

void Settings::setLongForLe(long longForLe)
{
    m_longForLe = longForLe;
}

double Settings::doubleForLe() const
{
    return m_doubleForLe;
}

void Settings::setDoubleForLe(double doubleForLe)
{
    m_doubleForLe = doubleForLe;
}

int Settings::intForSb() const
{
    return m_intForSb;
}

void Settings::setIntForSb(int intForSb)
{
    m_intForSb = intForSb;
}

double Settings::doubleForDsb() const
{
    return m_doubleForDsb;
}

void Settings::setDoubleForDsb(double doubleForDsb)
{
    m_doubleForDsb = doubleForDsb;
}

bool Settings::boolForChb() const
{
    return m_boolForChb;
}

void Settings::setBoolForChb(bool boolForChb)
{
    m_boolForChb = boolForChb;
}

int Settings::intForCb() const
{
    return m_intForCb;
}

void Settings::setIntForCb(int intForCb)
{
    m_intForCb = intForCb;
}

Settings::States Settings::stateForGrpb() const
{
    return m_stateForGrpb;
}

void Settings::setStateForGrpb(const States &stateForGrpb)
{
    m_stateForGrpb = stateForGrpb;
}



//void Settings::setStateForGrpb(int stateInt)
//{
//    qDebug()<<"statein";
//    m_stateForGrpb = static_cast<States>(stateInt);
//}
