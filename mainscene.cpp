#include "entity.h"
#include "mainscene.h"
#include "personal.h"
#include "ui_mainscene.h"

#include <QMessageBox>
#include <qboxlayout.h>
#include <qpainter.h>

MainScene::MainScene(ValidConnect* vc, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->vc=vc;
    status(true);

    uiInit();

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

void MainScene::uiInit()
{
    //图标
    setWindowIcon(QIcon(":/img/app_icon.png"));
    setWindowTitle("MiniChat");

    setFixedSize(W,H);

    ui->search->setIcon(QIcon(":/img/searchi.png"));

    vc->getUserInfo();

    ifwd=new InformationWidget(this);
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
    ui->act->setText(result.getstr("account"));

    //头像
    QString imgname=result.getstr("imgPath");
    qDebug()<<"img: "<<imgname;
    imgname=getImage(imgname);
    QImage image(imgname);
    // 计算缩放比例
    qreal scale = qMin(ui->img->width() / static_cast<qreal>(image.width()), ui->img->height() / static_cast<qreal>(image.height()));
    image = image.scaled(image.size() * scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 创建图标
    QIcon icon(QPixmap::fromImage(image));
    ui->img->setIcon(icon);
    ui->img->setIconSize(QSize(ui->img->width(), ui->img->height()));
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
    });
}

//退出按钮
void MainScene::on_pushButton_2_clicked()
{
    auto v = QMessageBox::warning(nullptr,"退出登入","你确定退出登入？");
    if(v==QMessageBox::StandardButton::Ok){
        emit quit();
    }
}

