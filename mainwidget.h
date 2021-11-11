#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

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
    LightSettings ls;

    QMenu *menu;
    QMenuBar *menuBar;
    QAction *action;
    bool yes = true;

    QButtonGroup* btngrpStates;
    template <class T>
    void saveEveryField(T& t);
        template <class T>
    void loadEveryField(T& t);
};

#endif // MAINWIDGET_H
