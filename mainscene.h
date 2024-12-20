#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "downconnect.h"
#include "informationwidget.h"
#include "validconnect.h"
#include "webdistb.h"

#include <QMainWindow>
#include <QPoint>

#define W 900
#define H 650
#define X_Y 0,120
#define DIS_XY 320,0

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow,public Handler
{
    Q_OBJECT

public:
    explicit MainScene(ValidConnect* vc, QWidget *parent = nullptr);
    ~MainScene();
    //ui初始化
    void uiInit();
    void paintEvent(QPaintEvent*) override;
    //接收userinfo
    void handler(DataHead& head, DataResult& result) override;
    //设置子组件大小
    void sizeSet();
    void resizeEvent(QResizeEvent *event) override;
    void status(bool s);
    //头像设置
    void img(const QString& name);
    //槽函数连接
    void connectss();
    //display展示一个widget
    void display_(QWidget* w);
    //display移除widget
    void disclear();
    //消息接收处理
    void sendHandler(DataHead&,DataResult&);
    //登入后接收消息
    void loginedmsg(DataHead&,DataResult&);
    void onlogined();
    //新的用户聊天消息
    void newchatmsg(QString& act,QJsonArray& data);

private slots:
    void on_img_clicked();

    void on_pushButton_2_clicked();

    void on_search_clicked();

    void on_notify_clicked();

    void userchat(const QString& act, bool online, const QString& name);

signals:
    void quit();

private:
    Ui::MainScene *ui;
    ValidConnect* vc;
    WebDistb* wd;
    InformationWidget* ifwd;
    QWidget* display;
    QWidget* tempWidget=nullptr;
    DownConnect* dc=nullptr;
};

#endif // MAINSCENE_H
