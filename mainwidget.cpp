#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include "lightbinding.h"
#include "sbvariantsaver.h"
#include "sbautosaver.h"
struct Test{
    enum Lol{
        lol1, lol2, lol3
    };
    Lol lol{lol2};
    int field1{0};
    QString f2{"text"};
    bool field3{false};
    quint8 field4{2};

};



Q_DECLARE_METATYPE(Test::Lol);

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    settings = new Settings(this);

    settings->load();
    settings->bindWtToProp(ui->leString, "stringForLe");
    settings->bindWtToProp(ui->leInt, "intForLe");
    settings->bindWtToProp(ui->leUint, "uintForLe");
    settings->bindWtToProp(ui->leShort, "shortForLe");

    //if int value is Hex, use method:
    settings->bindWtToProp(ui->leUintHex, "hexedUintForLe", Settings::IntType::hex);
    settings->bindWtToProp(ui->leLong, "longForLe");
    settings->bindWtToProp(ui->leDouble, "doubleForLe");    //TODO setDoublePrecisionProperty or not;
    settings->bindWtToProp(ui->sbInt, "intForSb");
    settings->bindWtToProp(ui->dsbDouble, "doubleForDsb");
    settings->bindWtToProp(ui->chb, "boolForChb");
    ui->cbInt->addItems({"first", "second", "third"});
    settings->bindWtToProp(ui->cbInt, "intForCb");

    //unite radiobuttongs into QButtonGroup;
    btngrpStates = new QButtonGroup();
    btngrpStates->addButton(ui->radioButton, 0);            //index should be the same as interpreted enum class value
    btngrpStates->addButton(ui->radioButton_2, 1);          //or just add it in the proper consequence
    btngrpStates->addButton(ui->radioButton_3, 2);          //or instead is int use static_cast<int>(enum class value);

    settings->bindWtToProp(btngrpStates, "stateForGrpb");
    settings->bindWtToProp(ui->cbEnum, "stateForCb", BindedSettings::WriteAlgorithm::notifyOnWrite);
    settings->bindWtToProp(ui->lblEnum, "stateForCb");

    //lightBinding
    ui->cbIntL->addItems({"1","2", "3"});
    ui->leUintL->setText("15");
    ui->leStringL->setText("Some");
    ui->leIntL->setText("15");
    LightBinding::bindLeToVal(ls.intForLe, ui->leIntL);
    LightBinding::bindLeToVal(ls.uintForLe, ui->leUintL);
    LightBinding::bindLeToVal(ls.strForLe, ui->leStringL);

    ls.setVars(SbVariantSaver::loadVarVec("LightSettings"));
    LightBinding::bindLeFromVal(ls.shortForLe, ui->leShortL);
    LightBinding::bindLeFromHex(ls.uintHexForLe, ui->leUintHexL);
    LightBinding::bindSbFromVal(ls.intForSb, ui->sbIntL);
    LightBinding::bindLeFromVal(ls.dblForLe, ui->leDoubleL);
    LightBinding::bindDsbFromVal(ls.dblForDsb, ui->dsbDoubleL);
    LightBinding::bindChbFromVal(ls.boolForChb, ui->chbL);

    // testing saving core
    Test t;
    SbAutoSaver::saveEveryField(t);
    SbAutoSaver::loadEveryField(t);

}

MainWidget::~MainWidget()
{
    settings->save();
    SbVariantSaver::saveVarVec(ls.getVar(), "LightSettings");
    delete ui;
}


