#include "loginscene.h"


#include <QStatusBar>

LoginScene::LoginScene(QWidget *parent)
    : QMainWindow{parent}
{
    //图标
    setWindowIcon(QIcon(":/img/app_icon.png"));
    setWindowTitle("MiniChat");
    setFixedWidth(320);
    setFixedHeight(500);

    loginWidget=new LoginWidget(this);
    registWidget=new RegistWidget(this);
    rgtCfmWidget=new RgtCfmWidget(this);
    registWidget->hide();
    rgtCfmWidget->hide();

    //状态栏
    QStatusBar* sbar = statusBar();
    statusLabel=new QLabel(sbar);
    setStatus(disonline);

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

    //服务器连接
    tempSocket=new TempConnect(this);
    connect(tempSocket, &TempConnect::connected, [this](){
        setStatus(online);
    });
    connect(tempSocket, &TempConnect::closed, [this](){
        setStatus(disonline);
    });

    //槽函数连接
    connect(loginWidget, &LoginWidget::login, tempSocket, &TempConnect::login); //登入
    connect(registWidget, &RegistWidget::submit, tempSocket, &TempConnect::register_email);//注册——邮箱提交
    connect(rgtCfmWidget, &RgtCfmWidget::again_code, tempSocket, &TempConnect::register_code);//请求重新发送验证码
    connect(rgtCfmWidget, &RgtCfmWidget::submit, tempSocket, &TempConnect::register_submit);//提交验证码
}

void LoginScene::setStatus(status s)
{
    QString msg;
    QString color;
    switch(s){
    case online:
        msg="已连接"; color="#005500"; break;
    case disonline:
        msg="未连接"; color="red"; break;
    default:
        msg="未连接"; color="red";
    }
    statusLabel->setText(msg);
    QString style("color: %1;font-size:16px;font-weight:bold;");
    statusLabel->setStyleSheet(style.arg(color));
}
