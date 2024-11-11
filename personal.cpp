#include "personal.h"
#include "filemanager.h"
#include "ui_personal.h"
#include "wapplication.h"
#include "webdistb.h"

#include <QFileDialog>

Personal::Personal(User user, int self, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Personal)
{
    ui->setupUi(this);

    ui->name->setText(user.name);
    ui->self->hide();

    name=user.name;

    img(user.imgPath);

    disSelf(user);

}

Personal::~Personal()
{
    disconnect();
    delete ui;
}

void Personal::disSelf(User user)
{
    ui->change->setIcon(QIcon(":/img/edit.png"));
    ui->account->setDisabled(true);
    ui->self->show();
    ui->account->setText(user.name);
    ui->account_2->setText(user.account);
    ui->email->setText(user.email);
    ui->cdate->setText(user.create_time.toString());
}

void Personal::img(const QString &name)
{
    //头像
    QString imgname=getImage(name);
    QImage image(imgname);
    // 计算缩放比例
    image = image.scaled(QSize(ui->img->width(), ui->img->height()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // 创建图标
    QIcon icon(QPixmap::fromImage(image));
    ui->img->setIcon(icon);
    ui->img->setIconSize(QSize(ui->img->width(), ui->img->height()));
}

void Personal::on_change_clicked()
{
    if(!avb){//改为可修改name
        avb=!avb;
        ui->account->setDisabled(false);
        ui->account->setStyleSheet("border-bottom:1px solid #666666;background-color: transparent;font-size:16px;font-weight:bold;color:rgb(0, 170, 255);");
        ui->change->setIcon(QIcon(":/img/check.png"));
    }else{//关闭可修改，上传修改后的name
        avb=!avb;
        ui->account->setDisabled(true);
        ui->account->setStyleSheet("border:none;background-color: transparent;font-size:16px;font-weight:bold;color:rgb(0, 170, 255);");
        ui->change->setIcon(QIcon(":/img/edit.png"));
        QString n=ui->account->text();
        if(name!=n){
            QJsonObject jo;
            jo.insert("account", ui->account_2->text());
            jo.insert("newname", n);
            DataHead h=DataHead::dataHead("rename");
            h.show();
            DataResult r=DataResult(0, QJsonDocument(jo));
            WebDistb::asyncWeb(WApplication::getSocket(), h, r,
            [=](DataHead& head, DataResult& result)->void{
                emit rename(n);
                name=n;
                ui->name->setText(n);
            });
        }
    }
}

//上传头像
void Personal::on_img_clicked()
{
    //打开文件
    QString path = QFileDialog::getOpenFileName(nullptr, "Open Image File", QString(), QString("*.jpg"));
    //文件数据
    QByteArray* data;
    data=FileManager::uimgload(path);
    if(data==nullptr){
        QMessageBox::critical(nullptr, "error", "选择文件不能大于1MB");
        return;
    }
    //head
    DataHead head=DataHead::dataHead("uimgload");
    QJsonObject jo;
    jo.insert("account", ui->account_2->text());
    QJsonDocument json(jo);
    //上传头像
    WebDistb::asyncBin(WApplication::getSocket(), head, json, *data, [=](int code, QByteArray& d) mutable->void{
        qDebug()<<code;
        if(code==DataResult::code_success){
            //保存头像
            FileManager::uimgsave(ui->account_2->text(), *data);
            QString name=ui->account_2->text()+USER_IMAGE_TAIL;
            img(name);
            emit reimg(name);
        }else
            QMessageBox::critical(nullptr,"error", "上传出错");
        delete data;
    });
}

