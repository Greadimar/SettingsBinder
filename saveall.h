#ifndef SAVEWT_H
#define SAVEWT_H
#include <QObject>
#include <QString>
#include <QObject>
#include <QSettings>
#include <QLineEdit>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QDir>
#include <QToolButton>
#include <QSlider>

enum TypeSaveAll{Save = 0, Load = 1};
class SaveAll : public QSettings
{
public:
    SaveAll(QObject *obj, QString nameFile, QString groupName = "", QSettings::Format format = QSettings::Format::IniFormat);
    void save(QObject *obj);
    void load(QObject *obj);
    void save();
    void load();
private:
    QObject *objPr;
    QSettings *s;
    QString m_addName;
    void setObject(QObject *obj, TypeSaveAll type);
    void saveProper(QObject *obj);
    void loadProper(QObject *obj);
    inline unsigned int u(int i) const
    {
        return *reinterpret_cast<unsigned int *>(&i);
    }
    inline int i(unsigned int u) const
    {
        return *reinterpret_cast<int *>(&u);
    }
public slots:

};




#endif // SAVEWT_H
