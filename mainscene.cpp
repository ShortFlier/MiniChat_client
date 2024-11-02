#include "mainscene.h"
#include "ui_mainscene.h"

#include <qboxlayout.h>
#include <qpainter.h>

MainScene::MainScene(ValidConnect* vc, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->vc=vc;
    status(true);
    //图标
    setWindowIcon(QIcon(":/img/app_icon.png"));
    setWindowTitle("MiniChat");

    setFixedSize(900,650);

    ui->search->setIcon(QIcon(":/img/search.png"));

    vc->getUserInfo();

    ifwd=new InformationWidget(this);
    ifwd->move(X_Y);

    display=new QWidget(this);
    display->move(DIS_XY);
    display->setLayout(new QVBoxLayout(display));
    display->setObjectName("display");
    display->setStyleSheet("#display{border-left:1px solid rgb(200,200,200)}");

    sizeSet();

    //处理函数
    wd=new WebDistb(vc);
    wd->addHandler("userinfo",this);

    connectss();
}

MainScene::~MainScene()
{
    delete ui;
    vc->disconnect();
    delete vc;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPixmap pix(":/img/backs.jpg");
    paint.drawPixmap(0,0,width(),height(),pix);
}

void MainScene::handler(DataHead &head, DataResult &result)
{
    result.show();
    ui->name->setText(result.getstr("name"));
    ui->act->setText(result.getstr("account"));
}

void MainScene::sizeSet()
{
    int w = width();
    int h = height();
    //设置ifwd
    ifwd->resize(320, h-120);
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

void MainScene::connectss()
{
    connect(vc->getSocket(), &QWebSocket::disconnected, [this](){
        status(false);
    });
}
