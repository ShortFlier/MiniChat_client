#include "entity.h"
#include "mainscene.h"
#include "mapper.h"
#include "personal.h"
#include "ui_mainscene.h"
#include "filemanager.h"
#include "chatwidget.h"
#include "notifywidget.h"

#include <QMessageBox>
#include <qboxlayout.h>
#include <qpainter.h>
#include <functional>

MainScene::MainScene(ValidConnect* vc, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->vc=vc;
    status(true);

    dc=new DownConnect(vc->getAccount());
    connect(dc, &DownConnect::newchatmsg, this, &MainScene::newchatmsg);

    uiInit();

    //处理函数
    wd=new WebDistb(vc);
    wd->addHandler("userinfo",this);
    wd->addwsHandler("send", std::bind(&MainScene::sendHandler,this, std::placeholders::_1, std::placeholders::_2));
    wd->addwsHandler("loginedmsg", std::bind(&MainScene::loginedmsg, this, std::placeholders::_1, std::placeholders::_2));

    connectss();

    onlogined();
}

MainScene::~MainScene()
{
    delete ui;
    vc->disconnect();
    delete vc;
    delete dc;
}

void MainScene::uiInit()
{
    qDebug()<<"uiInit";
    //图标
    setWindowIcon(QIcon(":/img/app_icon.png"));
    setWindowTitle("MiniChat");

    setFixedSize(W,H);

    ui->search->setIcon(QIcon(":/img/searchi.png"));
    ui->notify->setIcon(QIcon(":/img/ring.png"));

    vc->getUserInfo();

    ifwd=new InformationWidget(this);
    connect(ifwd, &InformationWidget::userchat, this, &MainScene::userchat);
    ifwd->move(X_Y);

    display=new QWidget(this);
    display->move(DIS_XY);
    display->setLayout(new QVBoxLayout(display));
    display->setObjectName("display");
    display->setStyleSheet("#display{border-left:1px solid rgb(200,200,200);}");


    sizeSet();
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPixmap pix(":/img/back.png");
    paint.drawPixmap(0,0,width(),height(),pix);
}

void MainScene::handler(DataHead &head, DataResult &result)
{
    result.show();
    ui->name->setText(result.getstr("name"));
    WApplication::name=result.getstr("name");
    ui->act->setText(result.getstr("account"));

    // //头像
    QString imgname=result.getstr("imgPath");
    img(imgname);

    //下载自己头像
    FileManager::uimgdown(vc->getAccount(),[this]()->void{
        img(vc->getAccount()+USER_IMAGE_TAIL);
    });
}

void MainScene::sizeSet()
{
    int w = width();
    int h = height();
    //设置ifwd
    ifwd->resize(320, h-120);
    ifwd->sizeSet();
    //设置display
    display->resize(w-320,h);
}

void MainScene::resizeEvent(QResizeEvent *event)
{
    sizeSet();
    QMainWindow::resizeEvent(event);
}

void MainScene::status(bool s)
{
    if(s){
        ui->sts->setText("在线");
        ui->sts->setStyleSheet("#sts{color:green;}");
    }else{
        ui->sts->setText("离线");
        ui->sts->setStyleSheet("#sts{color:red;}");
    }
}

void MainScene::img(const QString &name)
{
    QString _name=getImage(name);
    qDebug()<<"img: "<<_name;
    QImage image(_name);
    // 计算缩放比例
    image = image.scaled(QSize(ui->img->width(), ui->img->height()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // 创建图标
    QIcon icon(QPixmap::fromImage(image));
    ui->img->setIcon(icon);
    ui->img->setIconSize(QSize(ui->img->width(), ui->img->height()));
}

void MainScene::connectss()
{
    connect(vc->getSocket(), &QWebSocket::disconnected, [this](){
        status(false);
    });
}

void MainScene::display_(QWidget *w)
{
    disclear();
    tempWidget=w;
    display->layout()->addWidget(tempWidget);
}

void MainScene::disclear()
{
    if(tempWidget){
        display->layout()->removeWidget(tempWidget);
        tempWidget->deleteLater();
        tempWidget=nullptr;
    }
}

void MainScene::sendHandler(DataHead &head, DataResult &result)
{
    QJsonArray data=result.jsdata.array();
    QString act=data.at(0).toObject().value("sender").toString();
    //保存
    minstanse->savemsg(data);
    //如果当前展示页面为聊天界面，推送至聊天界面
    newchatmsg(act, data);
    //更新消息列表
}

void MainScene::loginedmsg(DataHead &head, DataResult &result)
{
    QJsonArray ja=result.jsdata.array();
    if(minstanse->savemsg(ja)){
        QJsonArray ids;
        for(int i=0; i<ja.size(); ++i){
            ids.append(ja.at(i).toObject().value("id"));
        }
        //返回id
        DataResult r(DataResult::code_success, QJsonDocument(ids));
        WApplication::getSocket()->sendText(head, r);
    }
}

void MainScene::onlogined()
{
    DataHead head=DataHead::dataHead("friendlist");
    QJsonObject jo;
    jo.insert("account",WApplication::getAccount());
    DataResult result(0, QJsonDocument(jo));
    WebDistb::asyncWeb(WApplication::getSocket(), head, result, [this](DataHead& head,DataResult& result)->void{
        QJsonArray ja=result.jsdata.array();
        minstanse->myfriends(ja);
    });
}

void MainScene::newchatmsg(QString &act, QJsonArray &data)
{
    if(tempWidget)
        qDebug()<<"tw: "<<typeid(*tempWidget).name();
    ChatWidget* cw=dynamic_cast<ChatWidget*>(tempWidget);
    if(cw){
        cw->reciver(act, data);
    }
}

//点击头像展示个人资料
void MainScene::on_img_clicked()
{
    DataHead head=DataHead(DataHead::http, DataHead::request, "userinfo", QString::number(11));
    QJsonObject jo;
    jo.insert("account", vc->getAccount());
    DataResult result(0, QJsonDocument(jo));
    WebDistb::asyncWeb(vc, head, result, [this](DataHead& head, DataResult& result)->void{
        User user;
        user.enjson(result.jsdata.object());
        qDebug()<<result.jsdata.object();
        Personal* pers=new Personal(user, SELF);
        display_(pers);
        connect(pers, &Personal::rename, [this](QString name){
            ui->name->setText(name);
        });
        connect(pers, &Personal::reimg, [this](QString name){
            qDebug()<<"reimg";
            img(name);
        });
    });
}

//退出按钮
void MainScene::on_pushButton_2_clicked()
{
    auto v = QMessageBox::question(nullptr, "退出", "您确定要退出吗?",
                                   QMessageBox::Yes | QMessageBox::No);
    if(v==QMessageBox::Yes){
        emit quit();
    }
}

//用户，群查询
void MainScene::on_search_clicked()
{
    QString frd=ui->lineEdit->text();
    frd=frd.trimmed();
    if(frd.isEmpty()||(frd==WApplication::getAccount()))
        return;
    DataHead head=DataHead::dataHead("search");
    QJsonObject jo;
    jo.insert("friend", frd);
    jo.insert("account",WApplication::getAccount());
    DataResult result=DataResult(0, QJsonDocument(jo));
    WebDistb::asyncWeb(WApplication::getSocket(), head, result, [=](DataHead& head, DataResult& result)->void{
        if(frd.length()>8){//显示用户
            User user;
            user.enjson(result.jsdata.object());
            bool isfriend=result.jsdata.object().value("isfriend").toBool();
            ChatWidget* cw=new ChatWidget(user,isfriend);
            display_(cw);
        }else{//显示群聊

        }
    });
}


void MainScene::on_notify_clicked()
{
    NotifyWidget* ntf=new NotifyWidget(vc->getAccount(), vc);
    wd->addHandler("myinvite", ntf);
    display_(ntf);
}

void MainScene::userchat(const QString& act, bool online, const QString& name)
{
    DataHead head=DataHead::dataHead("search");
    QJsonObject jo;
    jo.insert("friend", act);
    jo.insert("account",WApplication::getAccount());
    DataResult result=DataResult(0, QJsonDocument(jo));
    WebDistb::asyncWeb(WApplication::getSocket(), head, result, [=](DataHead& head, DataResult& result)->void{
        User user;
        user.enjson(result.jsdata.object());
        bool isfriend=result.jsdata.object().value("isfriend").toBool();
        ChatWidget* cw=new ChatWidget(user,isfriend, name, online);
        display_(cw);
    });
}

