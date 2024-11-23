#include "datahead.h"
#include "informationwidget.h"
#include "filemanager.h"
#include "mapper.h"
#include "ui_informationwidget.h"
#include "wapplication.h"

#include <QJsonArray>
#include <QMouseEvent>
#include <QPushButton>

InformationWidget::InformationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InformationWidget)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);

    setFixedWidth(320);


    info = ui->infoctn;
    grp=new QVBoxLayout(ui->grpctn);
    ui->grpctn->setLayout(grp);
    frd=new QVBoxLayout(ui->frdctn);
    ui->frdctn->setLayout(frd);

    frdinit();
    infoinit();
}

InformationWidget::~InformationWidget()
{
    delete ui;
}

void InformationWidget::sizeSet()
{
    int w=ui->infosr->width();
//    int h=ui->tabWidget->height()-30;
    int h=500;
    ui->infosr->resize(w,h);
    ui->friendssr->resize(w,h);
    ui->groupsr->resize(w,h);
}

void InformationWidget::frdinit()
{
    DataHead head=DataHead::dataHead("friendlist");
    QJsonObject jo;
    jo.insert("account",WApplication::getAccount());
    DataResult result(0, QJsonDocument(jo));
    WebDistb::asyncWeb(WApplication::getSocket(), head, result, [this](DataHead& head,DataResult& result)->void{
        QJsonArray ja=result.jsdata.array();
        for(int i=0; i<ja.size(); ++i){
            QJsonObject jo=ja[i].toObject();
            IFriend* f=new IFriend(jo,this);
            frd->addWidget(f);
            connect(f, &IFriend::chat,[this](const QString& act, bool online, const QString& name){
                emit userchat(act,online,name);
            });
        }
    });
}

void InformationWidget::grpinit()
{

}

void InformationWidget::infoinit()
{
    QJsonArray data=minstanse->lastmsg();
    for(int i=0; i<data.size(); ++i){
        QJsonObject jo=data.at(i).toObject();
        addinfo(jo);
    }
}

void InformationWidget::addinfo(QJsonObject &jo)
{
    IInfo* i=new IInfo(jo,info);
    QPoint p=info->pos();
    i->move(p+QPoint(infosize*30,0));
    ++infosize;
    info->resize(300,infosize*30);
    connect(i, &IInfo::chat,[this](const QString& act, bool online, const QString& name){
        emit userchat(act,online,name);
    });
}

IFriend::IFriend(const QJsonObject& jo, QWidget *parent ):QWidget(parent)
{
    resize(300,30);
    QPoint p=pos();
    int id=jo.value("id").toInt();
    act=jo.value("account").toString();
    name=jo.value("name").toString();
    online=jo.value("online").toBool();
    QPushButton* _img=new QPushButton(this);
    _img->resize(30,30);
    _img->setStyleSheet("QPushButton{border-radius:15px;}");
    img(_img, act);
    QLabel* lname=new QLabel(name, this);
    lname->move(p+QPoint(35,0));
    lname->setStyleSheet("QLabel{font-size:14px;color:rgb(0, 170, 255);font-weight:bold;}");
    QLabel* status=new QLabel(this);
    status->move(p+QPoint(40,20));
    if(online){
        status->setText("在线");
        status->setStyleSheet("QLabel{color:green;}");
    }else{
        status->setText("离线");
        status->setStyleSheet("QLabel{color:red;font-size:9px}");
    }
}

void IFriend::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit chat(act, online, name);
    }
}

void img(QPushButton *img, const QString &act)
{
    QString iname=act+USER_IMAGE_TAIL;
    //头像
    QString imgname=getImage(iname);
    QImage image(imgname);
    // 计算缩放比例
    image = image.scaled(QSize(img->width(), img->height()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // 创建图标
    QIcon icon(QPixmap::fromImage(image));
    img->setIcon(icon);
    img->setIconSize(QSize(img->width(), img->height()));
}

IInfo::IInfo(QJsonObject &jo, QWidget *parent):QWidget(parent)
{
    act=QString::number(jo.value("account").toInteger());
    name=jo.value("name").toString();
    resize(300,30);
    QPushButton* btn=new QPushButton(this);
    btn->resize(30,30);
    img(btn, jo.value("account").toString());
    QLabel* lname=new QLabel(name, this);
    lname->move(pos()+QPoint(35,0));
    lname->setStyleSheet("QLabel{font-size:14px;color:rgb(0, 170, 255);font-weight:bold;}");
    QString msg=jo.value("msg").toString();
    QLabel* lmsg=new QLabel(msg,this);
    lmsg->setFixedWidth(200);
    lmsg->move(pos()+QPoint(35, 18));
    lmsg->setStyleSheet("QLabel{font-size:10px;}");
    QString time=jo.value("time").toString();
    QLabel* ltime=new QLabel(time,this);
    ltime->move(pos()+QPoint(170,0));
}

void IInfo::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit chat(act, false, name);
    }
}
