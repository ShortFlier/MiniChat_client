#ifndef MAPPER_H
#define MAPPER_H

#include "entity.h"
#include <QSqlDatabase>
#include <QObject>

class Mapper : public QObject
{
    Q_OBJECT
public:
    static Mapper* getInstance(const QString& act);
    static Mapper* instance();
    bool newmsg(Information& info);

signals:

private:
    explicit Mapper(QObject *parent = nullptr);
    ~Mapper(){db.close();};
    //设置当前登入账号，连接对应数据库
    void setAct(const QString& act);
    //初始化
    void init();
    QString account;
    static Mapper* m;
    QSqlDatabase db;
};

#endif // MAPPER_H
