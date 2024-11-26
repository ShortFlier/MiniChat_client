#include "chatdisplayer.h"
#include "filemanager.h"
#include "ui_chatdisplayer.h"

#include <QTextEdit>
#include <QTimer>

ChatDisplayer::ChatDisplayer(Information &info, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatDisplayer)
{
    ui->setupUi(this);

    img(info.sender);
    content(info);
}

ChatDisplayer::~ChatDisplayer()
{
    delete ui;
}

void ChatDisplayer::img(const QString &sender)
{
    QString name=sender+USER_IMAGE_TAIL;
    QString imgname=getImage(name);
    QImage image(imgname);
    // 计算缩放比例
    image = image.scaled(QSize(ui->img->width(), ui->img->height()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // 创建图标
    QIcon icon(QPixmap::fromImage(image));
    ui->img->setIcon(icon);
    ui->img->setIconSize(QSize(ui->img->width(), ui->img->height()));

    if(sender==WApplication::getAccount()){//右边显示
        ui->img->move(pos()+QPoint(width()-ui->img->width()-5,0));
    }
}

void ChatDisplayer::content(Information &info)
{
    if(info.type==INFO_TEXT){
        QTextEdit* text=ui->text;
        text->setText(info.msg);
        // 强制更新文档的文本宽度和大小
        text->document()->setTextWidth(text->width());
        text->document()->adjustSize(); // 更新文档的大小
        text->setFixedHeight(text->document()->size().width());
        if(info.sender==WApplication::getAccount()){//右边显示
            text->move(pos()+QPoint(width(),0)-QPoint(45,0)-QPoint(text->width(),0));
        }
        text->setReadOnly(true);
    }else{//显示图片
        QString path=info.msg;
        if(!info.msg.contains('/'))
            path=CHATIMG_DIR+path;
        QImage img(path);
        ui->text->hide();
        QPushButton* disimg=new QPushButton(this);
        disimg->move(pos()+QPoint(45,0));
        if(img.width()>1.3*img.height()){
            disimg->resize(150,100);
        }else if(img.height()>1.3*img.width()){
            disimg->resize(100,150);
        }else{
            disimg->resize(150,150);
        }
        resize(width(), disimg->height());
        img = img.scaled(disimg->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QIcon icon(QPixmap::fromImage(img));
        disimg->setIcon(icon);
        disimg->setIconSize(disimg->size());
        if(info.sender==WApplication::getAccount()){//右边显示
            disimg->move(pos()+QPoint(width(),0)-QPoint(45,0)-QPoint(disimg->width(),0));
        }
    }
}
