#ifndef DOWNCONNECT_H
#define DOWNCONNECT_H

#include "datahead.h"

#include <QObject>
#include <QWebSocket>

//专门用于文件传输的连接
class DownConnect :public QObject
{
    Q_OBJECT
public:
    explicit DownConnect(const QString& account, QObject *parent = nullptr);
    ~DownConnect();
    void sendBinay(QString& path, QJsonDocument jd, QByteArray& data);
    //图片聊天记录接收
    void reciverimg(QJsonDocument&,QByteArray&);
    void sendimg(QJsonDocument&,QByteArray&);
signals:
    void newchatmsg(QString& act,QJsonArray& data);

private:
    QString account;
    QWebSocket* socket=nullptr;
    QMap<QString, void(DownConnect::*)(QJsonDocument&,QByteArray&)> fmap;

    void funset();
    void connectToServer();
    void down();
    void BinayHandler(const QByteArray& data);

    //文本数据发送
    void sendText(DataHead& head, DataResult& result);
};

#endif // DOWNCONNECT_H
