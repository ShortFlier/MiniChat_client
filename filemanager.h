#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "wapplication.h"

#include <QObject>
#include <QFile>

#define DEFAULT_IMAGE ":/img/camera.png"
#define HEADSHOT_PATH "./assets/headshot/"
#define CHATIMG_DIR "./assets/chatimgs/"

#define USER_IMAGE_TAIL ".jpg"

#define MB 1024*1024
#define USER_IMAGE_MAX 1*MB

#define NULL_FUN [](){}

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    //用户头像上传，打开文件，如果文件大小不合适，返回nullptr
    static QByteArray* uimgload(const QString& path);
    //保存用户头像
    static void uimgsave(const QString& account, QByteArray& data);
    //聊天图片发送小于1MB
    static QByteArray* sendimg(const QString& path){return uimgload(path);}
    //保存聊天图片
    static bool savechatimg(const QString&name, QByteArray& data);

    //下载一个用户头像，fun为头像下载成功后执行的回调函数类型为void()
    template <typename Fun>
    static void uimgdown(const QString& account, Fun fun)
    {
        ValidConnect* vc =dynamic_cast<ValidConnect*>(WApplication::getSocket());
        DataHead head=DataHead::dataHead("uimgdown");
        QJsonObject jo;
        jo.insert("account",account);
        QJsonDocument json(jo);
        QByteArray dt;
        WebDistb::asyncBin(vc, head, json, dt, [account,fun](int code, QByteArray& data){
            if(code==DataResult::code_success){
                FileManager::uimgsave(account, data);
                qDebug()<<"fun";
                fun();
            }
        });
    }

signals:
};

//返回用户头像路径,参数为图片名，返回图像的路径，如果没有，返回默认图像
QString getImage(const QString& path);


#endif // FILEMANAGER_H
