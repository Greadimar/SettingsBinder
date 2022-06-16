#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include "settings.h"
struct Info{
    int i;
    QString s;
    double d;
    friend QDataStream & operator << (QDataStream &ds, const Info & i){
       ds << i.i << i.s << i.d;
        return ds;
    }

    friend QDataStream & operator >> (QDataStream &ds, Info & i){
        ds >> i.i >>i.s >> i.d ;
        return ds;
    }
};
namespace TestNs {
Q_NAMESPACE
enum Lol{
    lol1, lol2, lol3
};
Q_ENUM_NS(Lol)
}

struct Test{
    TestNs::Lol lol{TestNs::Lol::lol2};
    int field1{0};
    QString f2{"text"};
    bool field3{false};
    quint8 field4{2};
    Info info;

};

Q_DECLARE_METATYPE(Info)

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
   // Q_ENUM(Test::Lol)
private:
    Ui::MainWidget *ui;

    Settings* settings;
    LightSettings ls;

    QMenu *menu;
    QMenuBar *menuBar;
    QAction *action;
    bool yes = true;

    QButtonGroup* btngrpStates;
};

#endif // MAINWIDGET_H
