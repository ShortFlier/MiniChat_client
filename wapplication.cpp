#include "wapplication.h"


WApplication::WApplication(QObject *parent)
    : QObject{parent}
{
    loginScene=new LoginScene();
    loginScene->show();

    //登入成功
    connect(loginScene, &LoginScene::logined, this, [=](ValidConnect* vc){
        mainScene=new MainScene(vc);
        mainScene->show();
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
