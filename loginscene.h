#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <QMainWindow>
#include <QLabel>

#include "loginwidget.h"
#include "registwidget.h"
#include "rgtcfmwidget.h"
#include "tempconnect.h"
#include "webdistb.h"

class LoginScene : public QMainWindow, public Handler
{
    Q_OBJECT
public:
    enum status{online, disonline};
    explicit LoginScene(QWidget *parent = nullptr);
    void setStatus(status s);
    //登入成功
    void handler(DataHead& head, DataResult& result) override;

private:
    LoginWidget* loginWidget;
    RegistWidget* registWidget;
    RgtCfmWidget* rgtCfmWidget;

    QLabel* statusLabel;

    TempConnect* tempSocket;
    WebDistb* webdistb;

signals:

};

#endif // LOGINSCENE_H
