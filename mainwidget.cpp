#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
class testT
{
    testT(){}
    int x =0;
};

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    settings = new Settings(this);
  //  ss = new SettingsSaver(settings);             is possible also with any object with properties
    settings->load();
    settings->bindWtToProp(ui->leString, "stringForLe");
    settings->bindWtToProp(ui->leInt, "intForLe");
    settings->bindWtToProp(ui->leUint, "uintForLe");
    settings->bindWtToProp(ui->leShort, "shortForLe");

    //if int value is Hex, use method:
    settings->setIntTypePropertyTo(ui->leUintHex, Settings::IntType::hex);
    settings->bindWtToProp(ui->leUintHex, "hexedUintForLe");
    settings->bindWtToProp(ui->leLong, "longForLe");
    settings->bindWtToProp(ui->leDouble, "doubleForLe");    //TODO setDoublePrecisionProperty or not;
    settings->bindWtToProp(ui->sbInt, "intForSb");
    settings->bindWtToProp(ui->dsbDouble, "doubleForDsb");
    settings->bindWtToProp(ui->chb, "boolForChb");

    //unite radiobuttongs into QButtonGroup;
    btngrpStates = new QButtonGroup();
    btngrpStates->addButton(ui->radioButton, 0);            //index should be the same as interpreted enum class value
    btngrpStates->addButton(ui->radioButton_2, 1);          //or just add it in the proper consequence
    btngrpStates->addButton(ui->radioButton_3, 2);          //or instead is int use static_cast<int>(enum class value);
    settings->bindButtonGroupAsEnum<Settings::States>(btngrpStates, "stateForGrpb");
    ui->cbInt->addItem("intForLe", settings->intForLe());
    ui->cbInt->addItem("doubleForLe", settings->doubleForLe());
    settings->bindWtToProp(ui->cbInt, "intForCb");

}

MainWidget::~MainWidget()
{
    settings->save();
    delete ui;
}
