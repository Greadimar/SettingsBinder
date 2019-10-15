#include "saveall.h"

#include "saveall.h"

SaveAll::SaveAll(QObject *obj, QString nameFile, QString addName, QSettings::Format format) : QSettings(nameFile, format), objPr(obj)
{
    m_addName = addName;
}
void SaveAll::load(QObject *obj){
    setObject(obj,TypeSaveAll::Load);
}
void SaveAll::save(QObject *obj){
    setObject(obj,TypeSaveAll::Save);
}
void SaveAll::load(){
    setObject(objPr,TypeSaveAll::Load);
}
void SaveAll::save(){
    setObject(objPr,TypeSaveAll::Save);
}
void SaveAll::setObject(QObject *obj, TypeSaveAll type){
    QObjectList children = obj->children();
    if (children.isEmpty()) return;
    foreach(QObject * child, children) {
        if (child->isWidgetType()) {
            QString typeClass = child->metaObject()->className();
            if (type == TypeSaveAll::Save) saveProper(child); else loadProper(child);
            if (typeClass != "QDoubleSpinBox"
                    && typeClass != "QSpinBox"
                    && typeClass != "QTimeEdit"
                    && typeClass != "SBHexEdit"
                    && !child->objectName().contains("SaveOff")) {
                if((qobject_cast<QWidget *>(child)) != nullptr) setObject((qobject_cast<QWidget *>(child)), type);
            }
        }
    }
}
void SaveAll::saveProper(QObject *obj){
    if (obj->objectName().contains("SaveOff") || obj->objectName() == "") return;
    QString typeClass = obj->metaObject()->className();
    beginGroup(m_addName + "/" + obj->parent()->objectName());
    if (typeClass == "QLineEdit" || typeClass == "HexEdit"){
        setValue(qobject_cast<QLineEdit *>(obj)->objectName(), qobject_cast<QLineEdit *>(obj)->text());
    }else  if (typeClass == "QPushButton"){
        setValue(qobject_cast<QPushButton *>(obj)->objectName(), qobject_cast<QPushButton *>(obj)->isChecked());
    }else  if (typeClass == "QDoubleSpinBox"){
        setValue(qobject_cast<QDoubleSpinBox *>(obj)->objectName(), qobject_cast<QDoubleSpinBox *>(obj)->value());
    }else  if (typeClass == "QSpinBox"){
        setValue(qobject_cast<QSpinBox *>(obj)->objectName(), qobject_cast<QSpinBox *>(obj)->value());
    }else  if (typeClass == "SBHexEdit"){
        setValue(qobject_cast<QSpinBox *>(obj)->objectName(), QString::number(u((qobject_cast<QSpinBox *>(obj))->value()),16));
    }else  if (typeClass == "QCheckBox"){
        setValue(qobject_cast<QCheckBox *>(obj)->objectName(), qobject_cast<QCheckBox *>(obj)->isChecked());
    }else  if (typeClass == "QRadioButton" || typeClass == "CheckRadioButton"){
        setValue(qobject_cast<QRadioButton *>(obj)->objectName(), qobject_cast<QRadioButton *>(obj)->isChecked());
    }else  if (typeClass == "QComboBox"){
        setValue(qobject_cast<QComboBox *>(obj)->objectName(), qobject_cast<QComboBox *>(obj)->currentIndex());
    }else  if (typeClass == "QGroupBox"){
        setValue(qobject_cast<QGroupBox *>(obj)->objectName(), qobject_cast<QGroupBox *>(obj)->isChecked());
    }else  if (typeClass == "QToolButton"){
        setValue(qobject_cast<QToolButton *>(obj)->objectName(), qobject_cast<QToolButton *>(obj)->isChecked());
    }else  if (typeClass == "QSlider"){
        setValue(qobject_cast<QSlider *>(obj)->objectName(), qobject_cast<QSlider *>(obj)->value());
    }

    endGroup();
}

void SaveAll::loadProper(QObject *obj){
    if (obj->objectName().contains("SaveOff")  || obj->objectName() == "") return;
    QString typeClass = obj->metaObject()->className();
    beginGroup(m_addName + "/" + obj->parent()->objectName());
    if(!contains(obj->objectName())){
        endGroup();
        return;
    }
    if (typeClass == "QLineEdit" || typeClass == "HexEdit"){
        (qobject_cast<QLineEdit *>(obj))->setText(value(qobject_cast<QLineEdit *>(obj)->objectName()).toString());
    }else if(typeClass == "PushButtonStartStop"){
        (qobject_cast<QPushButton *>(obj))->setChecked(value((qobject_cast<QPushButton *>(obj))->objectName()).toBool());
    }else  if (typeClass == "QDoubleSpinBox"){
        (qobject_cast<QDoubleSpinBox*>(obj))->setValue(value((qobject_cast<QDoubleSpinBox*>(obj))->objectName()).toDouble());
    } else  if (typeClass == "QSpinBox"){
        (qobject_cast<QSpinBox *>(obj))->setValue(value((qobject_cast<QSpinBox *>(obj))->objectName()).toInt());
    } else  if (typeClass == "QSlider"){
        (qobject_cast<QSlider *>(obj))->setValue(value(qobject_cast<QSlider *>(obj)->objectName()).toInt());
    }else  if (typeClass == "SBHexEdit"){
        (qobject_cast<QSpinBox *>(obj))->setValue(i(value(qobject_cast<QSpinBox *>(obj)->objectName()).toString().toUInt(nullptr,16)));
    }else  if (typeClass == "QCheckBox"){
        (qobject_cast<QCheckBox *>(obj))->setChecked(value((qobject_cast<QCheckBox *>(obj))->objectName()).toBool());
    }else  if (typeClass == "QRadioButton" || typeClass == "CheckRadioButton"){
        (qobject_cast<QRadioButton *>(obj))->setChecked(value((qobject_cast<QRadioButton *>(obj))->objectName()).toBool());
    }else  if (typeClass == "QComboBox"){
        (qobject_cast<QComboBox *>(obj))->setCurrentIndex(value((qobject_cast<QComboBox *>(obj))->objectName()).toInt());
    }else  if (typeClass == "QToolButton"){
        (qobject_cast<QToolButton *>(obj))->setChecked(value((qobject_cast<QToolButton *>(obj))->objectName()).toBool());
    }else  if (typeClass == "QGroupBox"){
        if(!(qobject_cast<QGroupBox *>(obj))->isCheckable()) {
            endGroup();
            return;
        }
        bool state = value((qobject_cast<QGroupBox *>(obj))->objectName()).toBool();
        (qobject_cast<QGroupBox *>(obj))->setChecked(state);
    }
    endGroup();
}
