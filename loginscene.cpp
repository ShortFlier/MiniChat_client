#include "loginscene.h"

#include <QMessageBox>
#include <QStatusBar>
#include <QFile>

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
    //
    connect(registWidget, &RegistWidget::torgtcfm, [this](const QString& email){
        registWidget->hide();
        rgtCfmWidget->email(email);
        rgtCfmWidget->show();
    });

    webstart();

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

void LoginScene::webstart()
{
    //服务器连接
    tempSocket=new TempConnect(this);
    webdistb=new WebDistb(tempSocket);
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

    //处理函数
    webdistb->addHandler("login", this);
    webdistb->addHandler("regist_code", registWidget);
    webdistb->addHandler("regist_confirm", rgtCfmWidget);
}

void LoginScene::reshow()
{
    show();
    webstart();
}

void LoginScene::handler(DataHead &head, DataResult &result)
{
    if(result.code==DataResult::code_success){
        QString account=result.jsdata.object().value("account").toString();
        qDebug()<<"登入成功"<<account;
        login(account);
    }else
        QMessageBox::critical(nullptr, "错误", result.jsdata.object().value("msg").toString());
}

void LoginScene::login(const QString &account)
{
    ValidConnect* vc=tempSocket->upgrade(account);

    tempSocket->disconnect();
    delete tempSocket;
    tempSocket=nullptr;
    delete webdistb;
    webdistb=nullptr;

    hide();
    emit logined(vc);

    //保存账号
    save(account);
}

void LoginScene::save(const QString &account)
{
    QFile file("./assets/account.txt");
    file.open(QIODeviceBase::ReadWrite);
    if(file.isOpen()){
        QString accounts=file.readAll();
        if(!accounts.contains(account)){
            accounts.append("\n"+account);
            file.write(accounts.toUtf8());
        }
    }else{
        qDebug()<<"./assets/account.txt 打开出错";
    }
}
