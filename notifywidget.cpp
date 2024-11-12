#include "notifywidget.h"
#include "filemanager.h"
#include "ui_notifywidget.h"
#include "wapplication.h"

#include <QGroupBox>
#include <QInputDialog>
#include <QJsonArray>
#include <QPushButton>

NotifyWidget::NotifyWidget(const QString& act, ValidConnect* vc, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NotifyWidget)
{
    ui->setupUi(this);

    DataHead head=DataHead::dataHead("myinvite");
    QJsonObject jo;
    jo.insert("account", WApplication::getAccount());
    DataResult result(0,QJsonDocument(jo));
    vc->sendText(head, result);
}

NotifyWidget::~NotifyWidget()
{
    delete ui;
}

void NotifyWidget::handler(DataHead &head, DataResult &result)
{
    QGroupBox* box1=new QGroupBox("好友消息");
    QVBoxLayout* lay1=new QVBoxLayout(box1);
    QGroupBox* box2=new QGroupBox("群聊消息");
    QVBoxLayout* lay2=new QVBoxLayout(box2);

    QJsonArray ja=result.jsdata.array();
    for(int i=0;i<ja.size();++i){
        QJsonObject jo=ja[i].toObject();
        QString group=jo.value("group").toString();
        Friend* f=new Friend(jo);
        if(group.isEmpty()){    //好友申请
            lay1->addWidget(f);
        }else{  //群申请
            lay2->addWidget(f);
        }
        connect(f, &Friend::del, [lay1, lay2](Friend* f, int s){
            if(s){//好友申请
                lay1->removeWidget(f);
            }else{
                lay2->removeWidget(f);
            }
            delete f;
        });
    }

    QVBoxLayout* lay=new QVBoxLayout(ui->contents);
    ui->contents->setLayout(lay);
    lay->addWidget(box1);
    lay->addWidget(box2);
}

Friend::Friend(QJsonObject &jo)
{
    resize(560, 40);
    id=jo.value("id").toInt();
    QString account=jo.value("account").toString();
    QString name=jo.value("name").toString();
    QString group=jo.value("group").toString();
    QString note=jo.value("note").toString();

    QPoint p=this->pos();
    QPushButton* img=new QPushButton(this);
    img->resize(40,40);
    img->setStyleSheet("#img{border:none;border-radius:20px;}");
    if(group.isEmpty()){    //好友申请
        this->img(img, account+USER_IMAGE_TAIL);
        QLabel* lname=new QLabel(this);
        lname->setText(name+" 请求添加您为好友");
        lname->move(p+QPoint(50,10));
        lname->setStyleSheet("QLabel{font-size:14px;color:rgb(0, 170, 255);font-weight:bold;}");
        QLabel* lact=new QLabel(this);
        lact->setText(account);
        lact->move(p+QPoint(55,30));
        lact->setStyleSheet("QLabel{font-size:9px;}");
        QLabel* lnote=new QLabel(note,this);
        lnote->setMaximumWidth(200);
        lnote->move(p+QPoint(130,30));
    }else{  //群邀请

    }
    QPushButton* ac=new QPushButton("同意",this);
    ac->move(p+QPoint(450,10));
    ac->resize(40,20);
    ac->setCursor(Qt::PointingHandCursor);
    ac->setStyleSheet("QPushButton{color:green;}");
    connect(ac, &QPushButton::clicked, [=]()mutable{
        access(jo, true);
    });
    QPushButton* rj=new QPushButton("拒绝",this);
    rj->move(p+QPoint(390,10));
    rj->resize(40,20);
    rj->setCursor(Qt::PointingHandCursor);
    rj->setStyleSheet("QPushButton{color:red;}");
    connect(rj, &QPushButton::clicked, [=]()mutable{
        access(jo, false);
    });
}

void Friend::img(QPushButton *img, const QString &iname)
{
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

void Friend::access(QJsonObject &jo, bool status)
{
    QString group=jo.value("group").toString();
    QString invitees=WApplication::getAccount();
    QString account=jo.value("account").toString();
    QString name;
    QJsonObject json;
    json.insert("id",(int)id);
    json.insert("invitees",invitees);
    json.insert("status",status);
    json.insert("self", WApplication::name);
    qDebug()<<"self"<<WApplication::name;
    int s=0;
    if(group.isEmpty()){    //好友申请
        json.insert("account", account);
        name=jo.value("name").toString();
        s=1;
    }else{  //群申请
        json.insert("group", group);
        name=jo.value("groupname").toString();
    }
    if(status){
        QString str=QInputDialog::getText(nullptr, "备注", "备注", QLineEdit::Normal, jo.value("note").toString());
        if(!str.isEmpty())
            name=str;
    }
    json.insert("name", name);
    DataHead head=DataHead::dataHead("reinvite");
    DataResult result(0, QJsonDocument(json));
    qDebug()<<json;
    WApplication::getSocket()->sendText(head, result);
    emit del(this, s);
}


