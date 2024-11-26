#ifndef MAPPER_H
#define MAPPER_H

#include "entity.h"
#include <QSqlDatabase>
#include <QObject>
#include <QMutex>
#include <QVector>
#include <QWaitCondition>

#define minstanse Mapper::instance()

class DataBasePool{
public:
    DataBasePool(const QString &account, int size=5);
    ~DataBasePool();
    void append(QSqlDatabase& db);
    QSqlDatabase getdb();
private:
    QVector<QSqlDatabase> dbs;
    QMutex mutex;
    QWaitCondition cdtion;

    int size;
};


class Mapper : public QObject
{
    Q_OBJECT
public:
    static Mapper* getInstance(const QString& act);
    static Mapper* instance();

    void close(){delete pool; pool=nullptr;}

    //新发送的消息
    bool newmsg(Information& info);
    //接收的消息
    bool savemsg(QJsonArray& ja);
    //获取消息
    std::vector<Information> getInfos(const QString& act);
    //好友表
    bool myfriends(QJsonArray& ja);
    QJsonArray lastmsg();
    //接收的图片
    bool reciverimg(Information& info);

signals:

private:
    explicit Mapper(QObject *parent = nullptr);
    ~Mapper();
    //设置当前登入账号，连接对应数据库
    void setAct(const QString& act);
    //初始化
    void init();
    QString account;
    DataBasePool* pool=nullptr;


    static Mapper* m;
};

#endif // MAPPER_H
