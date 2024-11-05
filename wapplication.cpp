#include "wapplication.h"

WebSocketConnect* WApplication::sock=nullptr;

WApplication::WApplication(QObject *parent)
    : QObject{parent}
{
    loginScene=new LoginScene();
    loginScene->show();

    //登入成功
    connect(loginScene, &LoginScene::logined, this, [=](ValidConnect* vc){
        sock=vc;

        mainScene=new MainScene(vc);
        mainScene->show();
        //退出登入
        connect(mainScene, &MainScene::quit,[=](){
            mainScene->hide();
            loginScene->reshow();
            delete mainScene;
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
