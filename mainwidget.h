#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "settingssaver.h"
#include "settings.h"
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    Settings* settings;
    SettingsSaver* ss;
    QButtonGroup* btngrpStates;
};

#endif // MAINWIDGET_H
