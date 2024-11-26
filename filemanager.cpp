#include "filemanager.h"



#include <QDebug>
#include <QJsonObject>

FileManager::FileManager(QObject *parent)
    : QObject{parent}
{}

QByteArray *FileManager::uimgload(const QString &path)
{
    QByteArray* data=nullptr;
    QFile file(path);
    file.open(QIODeviceBase::ReadOnly);
    if(file.isOpen()){
        int size = file.size();
        if(size<USER_IMAGE_MAX){
            data=new QByteArray(file.readAll());
        }
    }else
        qDebug()<<"uimglaod 文件无法打开: "<<path;
    file.close();
    return data;
}

void FileManager::uimgsave(const QString &account, QByteArray &data)
{
    QString name=account+USER_IMAGE_TAIL;
    QString path=HEADSHOT_PATH+name;
    QFile file(path);
    file.open(QIODeviceBase::WriteOnly);
    if(file.isOpen()){
        file.write(data);
    }else
        qDebug()<<"uimgsave 文件写入错误:"<<path;
}

bool FileManager::savechatimg(const QString&name, QByteArray &data)
{
    QString path=CHATIMG_DIR+name;
    QFile file(path);
    file.open(QIODeviceBase::WriteOnly);
    if(file.isOpen()){
        file.write(data);
        return true;
    }else
        qDebug()<<"savechatimg 文件写入错误:"<<path;
    return false;
}


QString getImage(const QString &path)
{
    QString p=HEADSHOT_PATH+path;
    if(!path.isEmpty()&&QFile::exists(p))
        return p;
    return QString(DEFAULT_IMAGE);
}

