#include "notifywidget.h"
#include "ui_notifywidget.h"
#include "wapplication.h"

#include <QGroupBox>
#include <QJsonArray>

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

    QVBoxLayout* lay=new QVBoxLayout(ui->contents);
    ui->contents->setLayout(lay);
    lay->addWidget(box1);
    lay->addWidget(box2);
}

Friend::Friend(QJsonObject &jo)
{
    resize(560, 40);

}
