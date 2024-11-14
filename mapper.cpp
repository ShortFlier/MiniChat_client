#include "mapper.h"

#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>

#define DBNAME "./assets/database/db"+account+".db"

Mapper* Mapper::m=new Mapper();

Mapper *Mapper::getInstance(const QString &act)
{
    m->setAct(act);
    return m;
}

Mapper *Mapper::instance()
{
    return m;
}

Mapper::Mapper(QObject *parent)
    : QObject{parent}
{

}



void Mapper::setAct(const QString &act)
{
    db.close();
    account=act;
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DBNAME);
    qDebug()<<"database: "<<DBNAME;
    if (!db.open()) {
        qDebug() << "Error: Unable to open database" << db.lastError().text();
        return ;
    }
    init();
}

void Mapper::init()
{
    QSqlQuery query(db);
    bool b=query.exec("CREATE TABLE informations ("
                   "id INT AUTO_INCREMENT PRIMARY KEY,\n"
                    "sender VARCHAR(11) NOT NULL,\n"
                    "reciver VARCHAR(11) NOT NULL,\n"
                    "time DATETIME NOT NULL,\n"
                    "type CHAR(1) NOT NULL,\n"
                    "msg TEXT,\n"
                    "FOREIGN KEY (sender,reciver) REFERENCES user(account)\n"
                   ");");
    if(!b)
        qDebug() << "Error: query create informations:" << query.lastError().text();
}


bool Mapper::newmsg(Information& info){
    QString sql="insert into informations(sender,time,type,msg)\n"
                  "values(:sender,:time,:type,:msg)";
    QSqlQuery query(db);
    query.prepare(sql);
    query.bindValue(":sender",info.sender);
    query.bindValue(":reciver",info.reciver);
    query.bindValue(":type",QString(info.type));
    query.bindValue(":time",QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":msg",info.msg);
    bool b=query.exec();
    if(!b){
        qDebug()<< "Error newmsg:" << query.lastError().text();
    }
    return b;
}
