#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

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

    QButtonGroup* btngrpStates;
};

#endif // MAINWIDGET_H
