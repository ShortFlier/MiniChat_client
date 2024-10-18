#include "loginscene.h"

LoginScene::LoginScene(QWidget *parent)
    : QMainWindow{parent}
{
    //图标
    setWindowIcon(QIcon(":/img/app_icon.png"));
    setWindowTitle("MiniChat");
    setFixedWidth(320);
    setFixedHeight(530);

    statusWidget=new StatusWidget(this);

    loginWidget=new LoginWidget(this);
    loginWidget->move(loginWidget->pos()+QPoint(0,30));
    registWidget=new RegistWidget(this);
    registWidget->move(registWidget->pos()+QPoint(0,30));
    rgtCfmWidget=new RgtCfmWidget(this);
    rgtCfmWidget->move(rgtCfmWidget->pos()+QPoint(0,30));
    registWidget->hide();
    rgtCfmWidget->hide();

    //页面切换
    connect(loginWidget, &LoginWidget::swap, [this](){
        loginWidget->hide();
        registWidget->show();
    });
    connect(registWidget, &RegistWidget::swap, [this](){
        registWidget->hide();
        loginWidget->show();
    });
    connect(rgtCfmWidget, &RgtCfmWidget::back, [this](){
        rgtCfmWidget->hide();
        registWidget->show();
    });
    connect(rgtCfmWidget, &RgtCfmWidget::home, [this](){
        rgtCfmWidget->hide();
        loginWidget->show();
    });
    //邮箱验证合法
    connect(registWidget, &RegistWidget::submit, [this](const QString& email){
        registWidget->hide();
        rgtCfmWidget->email(email);
        rgtCfmWidget->show();
    });
}
