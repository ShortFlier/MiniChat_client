#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <QMainWindow>

#include "loginwidget.h"
#include "registwidget.h"
#include "rgtcfmwidget.h"
#include "statuswidget.h"

class LoginScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginScene(QWidget *parent = nullptr);

private:
    StatusWidget* statusWidget;

    LoginWidget* loginWidget;
    RegistWidget* registWidget;
    RgtCfmWidget* rgtCfmWidget;

signals:

};

#endif // LOGINSCENE_H
