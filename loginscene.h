#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <QMainWindow>
#include <QLabel>

#include "loginwidget.h"
#include "registwidget.h"
#include "rgtcfmwidget.h"
#include "tempconnect.h"

class LoginScene : public QMainWindow
{
    Q_OBJECT
public:
    enum status{online, disonline};
    explicit LoginScene(QWidget *parent = nullptr);
    void setStatus(status s);

private:
    LoginWidget* loginWidget;
    RegistWidget* registWidget;
    RgtCfmWidget* rgtCfmWidget;

    QLabel* statusLabel;

    TempConnect* tempSocket;

signals:

};

#endif // LOGINSCENE_H
