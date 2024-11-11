#include "wapplication.h"

WebSocketConnect* WApplication::sock=nullptr;
QString WApplication::account=QString();

WApplication::WApplication(QObject *parent)
    : QObject{parent}
{
    loginScene=new LoginScene();
    loginScene->show();

    //登入成功
    connect(loginScene, &LoginScene::logined, this, [=](ValidConnect* vc){
        sock=vc;
        account=vc->getAccount();

        mainScene=new MainScene(vc);
        mainScene->show();
        //退出登入
        connect(mainScene, &MainScene::quit,[=](){
            mainScene->hide();
            loginScene->reshow();
            delete mainScene;

            sock=nullptr;
            account=QString();
        });
    });
}

WApplication::~WApplication()
{
    delete loginScene;
    delete mainScene;
}

WApplication *WApplication::getInstance()
{
    static WApplication* app=new WApplication();
    return app;
}
