#ifndef LIGHTBINDING_H
#define LIGHTBINDING_H
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMutex>
template <typename T> void NOTSUPPORTED(){
    static_assert (std::is_same_v<void, T>, "This types is not supported" );
}
namespace LightBinding {

//binding LineEdit
template <typename TVal>
inline QLineEdit* bindLeToVal(QObject* connector, TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    auto lambda = [&](QString txt){
        if constexpr (std::is_unsigned_v<TVal>){
            ulong proxy;
            txt.contains("0x")? proxy = txt.toULong(nullptr, 16): proxy = txt.toULong();
            val = static_cast<TVal>(proxy);
        }
        else if constexpr(std::is_integral_v<TVal>){
            long proxy;
            txt.contains("0x")? proxy = txt.toLong(nullptr, 16): proxy = txt.toLong();
            val = static_cast<TVal>(proxy);
        }
        else if constexpr(std::is_same_v<TVal, QString>){
            val = txt;
        }
        else if constexpr(std::is_floating_point_v<TVal>){
            double proxy;
            proxy = txt.toDouble();
            val = static_cast<TVal>(proxy);
        }
        else {
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(le, &QLineEdit::textEdited, lambda);
    lambda(le->text());
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeToVal(QObject* connector, TVal& val , QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    auto lambda = [&](QString txt){
        QMutexLocker ml(&m);
        if constexpr (std::is_unsigned_v<TVal>){
            ulong proxy;
            txt.contains("0x")? proxy = txt.toULong(nullptr, 16): proxy = txt.toULong();
            val = static_cast<TVal>(proxy);
        }
        else if constexpr(std::is_integral_v<TVal>){
            long proxy;
            txt.contains("0x")? proxy = txt.toLong(nullptr, 16): proxy = txt.toLong();
            val = static_cast<TVal>(proxy);
        }
        else if constexpr(std::is_same_v<TVal, QString>){
            val = txt;
        }
        else if constexpr(std::is_floating_point_v<TVal>){
            double proxy;
            proxy = txt.toDouble();
            val = static_cast<TVal>(proxy);
        }
        else {
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(le, &QLineEdit::textEdited, lambda);
    lambda(le->text());
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeFromVal(QObject* connector, TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    auto lambda = [&](QString txt){
        if constexpr (std::is_unsigned_v<TVal>){
            ulong proxy;
            txt.contains("0x")? proxy = txt.toULong(nullptr, 16): proxy = txt.toULong();
            val = static_cast<TVal>(proxy);
        }
        else if constexpr(std::is_integral_v<TVal>){
            long proxy;
            txt.contains("0x")? proxy = txt.toLong(nullptr, 16): proxy = txt.toLong();
            val = static_cast<TVal>(proxy);
        }
        else if constexpr(std::is_same_v<TVal, QString>){
            val = txt;
        }
        else if constexpr(std::is_floating_point_v<TVal>){
            double proxy;
            proxy = txt.toDouble();
            val = static_cast<TVal>(proxy);
        }
        else {
            NOTSUPPORTED<TVal>();
        }

    };
    connector->connect(le, &QLineEdit::textEdited, lambda);
    if constexpr (std::is_integral_v<TVal> || std::is_floating_point_v<TVal>){
        le->setText(QString::number(val));
    }
    if constexpr (std::is_same_v<TVal, QString>){
        le->setText(val);
    }
    return le;
}

template <typename TVal>
inline QLineEdit* bindLeFromVal(QObject* connector, TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    auto lambda = [&](QString txt){
        QMutexLocker ml(&m);
        if constexpr (std::is_unsigned_v<TVal>){
            ulong proxy;
            txt.contains("0x")? proxy = txt.toULong(nullptr, 16): proxy = txt.toULong();
            val = static_cast<TVal>(proxy);
        }
        else if constexpr(std::is_integral_v<TVal>){
            long proxy;
            txt.contains("0x")? proxy = txt.toLong(nullptr, 16): proxy = txt.toLong();
            val = static_cast<TVal>(proxy);
        }
        else if constexpr(std::is_same_v<TVal, QString>){
            val = txt;
        }
        else if constexpr(std::is_floating_point_v<TVal>){
            double proxy;
            proxy = txt.toDouble();
            val = static_cast<TVal>(proxy);
        }
        else {
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(le, &QLineEdit::textEdited, lambda);
    if constexpr (std::is_integral_v<TVal> || std::is_floating_point_v<TVal>){
        QMutexLocker ml(&m);
        le->setText(QString::number(val));
    }
    if constexpr (std::is_same_v<TVal, QString>){
        QMutexLocker ml(&m);
        le->setText(val);
    }
    return le;
};

//binding le to hex
template<typename TVal>
inline QLineEdit* bindLeToHex(QObject* connector, TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    auto lambda = [&](QString txt){
        if constexpr (std::is_unsigned_v<TVal>){
            val = static_cast<TVal>(txt.toUInt(nullptr, 16));
        }
        else{
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(le, &QLineEdit::textEdited, lambda);
    lambda(le->text());
    return le;
};
template<typename TVal>
inline QLineEdit* bindLeToHex(QObject* connector, TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    auto lambda = [&](QString txt){
        QMutexLocker ml(&m);
        if constexpr (std::is_unsigned_v<TVal>){
            val = static_cast<TVal>(txt.toUInt(nullptr, 16));
        }
        else{
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(le, &QLineEdit::textEdited, lambda);
    lambda(le->text());
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeFromHex(QObject* connector, TVal& val , QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    auto lambda = [&](QString txt){
        if constexpr (std::is_unsigned_v<TVal>){
            val = static_cast<TVal>(txt.toUInt(nullptr, 16));
        }
        else {
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(le, &QLineEdit::textEdited, lambda);
    le->setText(QString::number(val, 16));
    return le;
};
template <typename TVal>
inline QLineEdit* bindLeFromHex(QObject* connector, TVal& val, QMutex& m, QLineEdit* le = nullptr){
    if (!le) le = new QLineEdit();
    auto lambda = [&](QString txt){
         QMutexLocker ml(&m);
        if constexpr (std::is_unsigned_v<TVal>){
            val = static_cast<TVal>(txt.toUInt(nullptr, 16));
        }
        else {
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(le, &QLineEdit::textEdited, lambda);
     QMutexLocker ml(&m);
    le->setText(QString::number(val, 16));
    return le;
};

//binding spinbox
template <typename TVal>
inline QSpinBox* bindSbToVal(QObject* connector, TVal& val , QSpinBox* sb = nullptr){
    if (!sb) sb = new QSpinBox();
    if constexpr (std::is_integral_v<TVal>){
        connector->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
            val = static_cast<TVal>(changedVal);
        });
        val = static_cast<TVal>(sb->value());
    }
    else if constexpr (std::is_same_v<TVal, std::chrono::milliseconds>){
        connector->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
            val = std::chrono::milliseconds(changedVal);
        });
        val = std::chrono::milliseconds(sb->value());
    }
    else{
        NOTSUPPORTED<TVal>();
    }
    return sb;
}
template <typename TVal>
inline QSpinBox* bindSbToVal(QObject* connector, TVal& val, QMutex& m, QSpinBox* sb = nullptr){
    if (!sb) sb = new QSpinBox();
    if constexpr (std::is_integral_v<TVal>){
        connector->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
            QMutexLocker ml(&m);
            val = static_cast<TVal>(changedVal);
        });
        QMutexLocker ml(&m);
        val = static_cast<TVal>(sb->value());
    }
    else if constexpr (std::is_same_v<TVal, std::chrono::milliseconds>){
        connector->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
            QMutexLocker ml(&m);
            val = std::chrono::milliseconds(changedVal);
        });
        QMutexLocker ml(&m);
        val = std::chrono::milliseconds(sb->value());
    }
    else{
        NOTSUPPORTED<TVal>();
    }
    return sb;
}

template <typename TVal>
inline QSpinBox* bindSbFromVal(QObject* connector, TVal& val , QSpinBox* sb = nullptr){
    if (!sb) sb = new QSpinBox();
    if constexpr (std::is_integral_v<TVal>){
        connector->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
            val = static_cast<TVal>(changedVal);
        });
        sb->setValue(val);
    }
    else if constexpr (std::is_same_v<TVal, std::chrono::milliseconds>){
        connector->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
            val = std::chrono::milliseconds(changedVal);
        });
        sb->setValue(val.count());
    }
    else{
        NOTSUPPORTED<TVal>();
    }
    return sb;
}

template <typename TVal>
inline QSpinBox* bindSbFromVal(QObject* connector, TVal& val , QMutex& m, QSpinBox* sb = nullptr){
    if (!sb) sb = new QSpinBox();
    if constexpr (std::is_integral_v<TVal>){
        connector->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
            QMutexLocker ml(&m);
            val = static_cast<TVal>(changedVal);
        });
        QMutexLocker ml(&m);
        sb->setValue(val);
    }
    else if constexpr (std::is_same_v<TVal, std::chrono::milliseconds>){
        connector->connect(sb, qOverload<int>(&QSpinBox::valueChanged), [&](int changedVal){
            QMutexLocker ml(&m);
            val = std::chrono::milliseconds(changedVal);
        });
        QMutexLocker ml(&m);
        sb->setValue(val.count());
    }
    else{
        NOTSUPPORTED<TVal>();
    }
    return sb;
}

//binding double spin box
template <typename TVal>
inline QDoubleSpinBox* bindDsbToVal(QObject* connector, TVal& val, QDoubleSpinBox* sb = nullptr){
    if (!sb) sb = new QDoubleSpinBox();
    if constexpr (std::is_floating_point_v<TVal>){
        connector->connect(sb, qOverload<double>(&QDoubleSpinBox::valueChanged), [&](double changedVal){
            val = static_cast<TVal>(changedVal);
        });
        val = static_cast<TVal>(sb->value());
    }
    else{
        NOTSUPPORTED<TVal>();
    }
    return sb;
}
template <typename TVal>
inline QDoubleSpinBox* bindDsbToVal(QObject* connector, TVal& val, QMutex& m, QDoubleSpinBox* sb = nullptr){
    if (!sb) sb = new QDoubleSpinBox();
    if constexpr (std::is_floating_point_v<TVal>){
        connector->connect(sb, qOverload<double>(&QDoubleSpinBox::valueChanged), [&](double changedVal){
            QMutexLocker ml(&m);
            val = static_cast<TVal>(changedVal);
        });
        QMutexLocker ml(&m);
        val = static_cast<TVal>(sb->value());
    }
    else{
        NOTSUPPORTED<TVal>();
    }
    return sb;
}
template <typename TVal>
inline QDoubleSpinBox* bindDsbFromVal(QObject* connector, TVal& val, QDoubleSpinBox* sb = nullptr){
    if (!sb) sb = new QDoubleSpinBox();
    if constexpr (std::is_floating_point_v<TVal>){
        connector->connect(sb, qOverload<double>(&QDoubleSpinBox::valueChanged), [&](double changedVal){
            val = static_cast<TVal>(changedVal);
        });
        sb->setValue(val);
    }
    else{
        NOTSUPPORTED<TVal>();
    }
    return sb;
}
template <typename TVal>
inline QDoubleSpinBox* bindDsbFromVal(QObject* connector, TVal& val, QMutex& m, QDoubleSpinBox* sb = nullptr){
    if (!sb) sb = new QDoubleSpinBox();
    if constexpr (std::is_floating_point_v<TVal>){
        connector->connect(sb, qOverload<double>(&QDoubleSpinBox::valueChanged), [&](double changedVal){
            QMutexLocker ml(&m);
            val = static_cast<TVal>(changedVal);
        });
        QMutexLocker ml(&m);
        sb->setValue(val);
    }
    else{
        NOTSUPPORTED<TVal>();
    }
    return sb;
}


//binding checkbox
inline QCheckBox* bindChbToVal(QObject* connector, bool& val, QCheckBox* chb = nullptr){
    if (!chb) chb = new QCheckBox();
    connector->connect(chb, &QCheckBox::toggled, [&](bool checked){
        val = checked;
    });
    val = chb->isChecked();
    return chb;
}
inline QCheckBox* bindChbToVal(QObject* connector, bool& val, QMutex& m, QCheckBox* chb = nullptr){
    if (!chb) chb = new QCheckBox();
    connector->connect(chb, &QCheckBox::toggled, [&](bool checked){
        QMutexLocker ml(&m);
        val = checked;
    });
    QMutexLocker ml(&m);
    val = chb->isChecked();
    return chb;
}
inline QCheckBox* bindChbFromVal(QObject* connector, bool& val, QCheckBox* chb = nullptr){
    if (!chb) chb = new QCheckBox();
    connector->connect(chb, &QCheckBox::toggled, [&](bool checked){
        val = checked;
    });
    chb->setChecked(val);
    return chb;
}
inline QCheckBox* bindChbFromVal(QObject* connector, bool& val, QMutex& m, QCheckBox* chb = nullptr){
    if (!chb) chb = new QCheckBox();
    connector->connect(chb, &QCheckBox::toggled, [&](bool checked){
        QMutexLocker ml(&m);
        val = checked;
    });
    QMutexLocker ml(&m);
    chb->setChecked(val);
    return chb;
}


//binding radiobutton
inline QRadioButton* bindRbToVal(QObject* connector, bool& val, QRadioButton* chb = nullptr){
    if (!chb) chb = new QRadioButton();
    connector->connect(chb, &QRadioButton::toggled, [&](bool checked){
        val = checked;
    });
    val = chb->isChecked();
    return chb;
}
inline QRadioButton* bindRbToVal(QObject* connector, bool& val, QMutex&m, QRadioButton* chb = nullptr){
    if (!chb) chb = new QRadioButton();
    connector->connect(chb, &QRadioButton::toggled, [&](bool checked){
        QMutexLocker ml(&m);
        val = checked;
    });
    QMutexLocker ml(&m);
    val = chb->isChecked();
    return chb;
}
inline QRadioButton* bindRbFromVal(QObject* connector, bool& val, QRadioButton* chb = nullptr){
    if (!chb) chb = new QRadioButton();
    connector->connect(chb, &QRadioButton::toggled, [&](bool checked){
        val = checked;
    });
    chb->setChecked(val);
    return chb;
}
inline QRadioButton* bindRbFromVal(QObject* connector, bool& val, QMutex& m, QRadioButton* chb = nullptr){
    if (!chb) chb = new QRadioButton();
    connector->connect(chb, &QRadioButton::toggled, [&](bool checked){
                QMutexLocker ml(&m);
        val = checked;
    });
            QMutexLocker ml(&m);
    chb->setChecked(val);
    return chb;
}
//binding combobox
template <typename TVal>
inline QComboBox* bindCbToVal(QObject* connector, TVal& val, QComboBox* cb = nullptr){
    if (!cb) cb = new QComboBox();
    auto lambda = [&](int curIdx){
        if constexpr (std::is_enum_v<TVal> || std::is_integral_v<TVal>){
            val = static_cast<TVal>(curIdx);
        }
        else {
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), lambda);
    lambda(cb->currentIndex());
    return cb;
}
template <typename TVal>
inline QComboBox* bindCbToVal(QObject* connector, TVal& val, QMutex& m, QComboBox* cb = nullptr){
    if (!cb) cb = new QComboBox();
    auto lambda = [&](int curIdx){
        QMutexLocker ml(&m);
        if constexpr (std::is_enum_v<TVal> || std::is_integral_v<TVal>){
            val = static_cast<TVal>(curIdx);
        }
        else {
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), lambda);
    lambda(cb->currentIndex());
    return cb;
}
template <typename TVal>
inline QComboBox* bindCbFromVal(QObject* connector, TVal& val, QComboBox* cb = nullptr){
    if (!cb) cb = new QComboBox();
    auto lambda = [&](int curIdx){
        if constexpr (std::is_enum_v<TVal> || std::is_integral_v<TVal>){
            val = static_cast<TVal>(curIdx);
        }
        else {
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), lambda);
    if (cb->count() <= static_cast<int>(val)) return cb;
    cb->setCurrentIndex(static_cast<int>(val));
    return cb;
}
template <typename TVal>
inline QComboBox* bindCbFromVal(QObject* connector, TVal& val, QMutex& m, QComboBox* cb = nullptr){
    if (!cb) cb = new QComboBox();
    auto lambda = [&](int curIdx){
        QMutexLocker ml(&m);
        if constexpr (std::is_enum_v<TVal> || std::is_integral_v<TVal>){
            val = static_cast<TVal>(curIdx);
        }
        else {
            NOTSUPPORTED<TVal>();
        }
    };
    connector->connect(cb, qOverload<int>(&QComboBox::currentIndexChanged), lambda);
    QMutexLocker ml(&m);
    if (cb->count() <= static_cast<int>(val)) return cb;
    cb->setCurrentIndex(static_cast<int>(val));
    return cb;
}


template <typename TEnumVal>
inline QButtonGroup* bindBtnGrpToVal(QObject* connector, TEnumVal& val, QButtonGroup* bgrp){
    if (!bgrp) bgrp = new QButtonGroup(connector);
    static_assert (std::is_enum_v<TEnumVal>, "please, use enum or enum class to bind this button group");
    auto lambda = [&](){
        val = static_cast<TEnumVal>(bgrp->checkedId());
    };
    connector->connect(bgrp, &QButtonGroup::buttonToggled, lambda);
    if (bgrp->checkedId() >= 0)
        lambda(bgrp->checkedId());
    return bgrp;
}

//from val
template <typename TEnumVal>
inline QButtonGroup* bindBtnGrpFromVal(QObject* connector, TEnumVal& val, QButtonGroup* bgrp){
    if (!bgrp) bgrp = new QButtonGroup(connector);
    static_assert (std::is_enum_v<TEnumVal>, "please, use enum or enum class to bind this button group");
    auto lambda = [&](){
        val = static_cast<TEnumVal>(bgrp->checkedId());
    };
    connector->connect(bgrp, &QButtonGroup::buttonToggled, lambda);
    int idx = static_cast<int>(val);
    if (idx < bgrp->buttons().size() && idx > 0)
    bgrp->button(idx)->setChecked(true);
    return bgrp;
}

}
#endif // LIGHTBINDING_H
