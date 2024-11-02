#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "informationwidget.h"
#include "validconnect.h"
#include "webdistb.h"

#include <QMainWindow>
#include <QPoint>

#define X_Y 0,120
#define DIS_XY 320,0

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow,public Handler
{
    Q_OBJECT

public:
    explicit MainScene(ValidConnect* vc, QWidget *parent = nullptr);
    ~MainScene();
    void paintEvent(QPaintEvent*) override;
    //接收userinfo
    void handler(DataHead& head, DataResult& result) override;
    //设置子组件大小
    void sizeSet();
    void resizeEvent(QResizeEvent *event) override;
    void status(bool s);
    void connectss();

private:
    Ui::MainScene *ui;
    ValidConnect* vc;
    WebDistb* wd;
    InformationWidget* ifwd;
    QWidget* display;
};

#endif // MAINSCENE_H
