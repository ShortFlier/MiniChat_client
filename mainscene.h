#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "validconnect.h"
#include "webdistb.h"

#include <QWidget>

namespace Ui {
class MainScene;
}

class MainScene : public QWidget,public Handler
{
    Q_OBJECT

public:
    explicit MainScene(ValidConnect* vc, QWidget *parent = nullptr);
    ~MainScene();
    //接收userinfo
    void handler(DataHead& head, DataResult& result);

private:
    Ui::MainScene *ui;
    ValidConnect* vc;
    WebDistb* wd;
};

#endif // MAINSCENE_H
