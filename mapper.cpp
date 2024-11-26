#include "mapper.h"
#include "wapplication.h"

#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QMutexLocker>
#include <QJsonArray>
#include <vector>

#define DBNAME "./assets/database/db"+account+".db"
#define IMAGE_TAIL ".jpg"

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

Mapper::~Mapper(){
    delete pool;
}

void Mapper::setAct(const QString &act)
{
    delete pool;
    account=act;
    pool=new DataBasePool(account);
    init();
}

void Mapper::init()
{
    QSqlDatabase db=pool->getdb();
    QSqlQuery query(db);
    bool b=query.exec("CREATE TABLE informations ("
                   "id INT AUTO_INCREMENT PRIMARY KEY,\n"
                    "sender VARCHAR(11) NOT NULL,\n"
                    "reciver VARCHAR(11) NOT NULL,\n"
                    "time DATETIME NOT NULL,\n"
                    "type CHAR(1) NOT NULL,\n"
                    "msg TEXT\n"
                   ");");
    if(!b)
        qDebug() << "Error: query create informations:" << query.lastError().text();
    b=query.exec("create table friends( "
                   "account varchar(11) primary key, \n"
                   "name varchar(20) not null);");
    if(!b)
        qDebug() << "Error: query create friends:" << query.lastError().text();
    pool->append(db);
}



bool Mapper::newmsg(Information& info){
    QString sql="insert into informations(sender,reciver,time,type,msg)\n"
                  "values(:sender,:reciver,:time,:type,:msg)";
    QSqlDatabase db=pool->getdb();
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
    pool->append(db);
    return b;
}

bool Mapper::savemsg(QJsonArray &ja)
{
    //information数组
    std::vector<Information> ifs;
    for(int i=0; i<ja.size(); ++i){
        Information ifm=Information::enjson(ja.at(i).toObject());
        ifs.push_back(ifm);
    }
    QString sql="insert into informations(sender, reciver, time, type, msg) values";
    QStringList values;
    for(int i=0; i<ifs.size(); ++i){
        Information& ifm=ifs[i];
        QString str="(\'"+ifm.sender+"\',\'"+ifm.reciver+"\',\'"+ifm.time.toString("yyyy-MM-dd HH:mm:ss")+"\',\'"+ifm.type+"\',\'"+ifm.msg+"\')";
        values.append(str);
    }
    QString v=values.join(',');
    sql=sql+v;
    QSqlDatabase db=pool->getdb();
    QSqlQuery query(db);
    qDebug()<<sql;
    bool b=query.exec(sql);
    if(!b){
        qDebug()<< "Error savemsg:" << query.lastError().text();
    }
    pool->append(db);
    return b;
}

std::vector<Information> Mapper::getInfos(const QString &act)
{
    QString sql="select id, sender, reciver, time, type, msg "
                  "from informations "
                  "where sender=%1 or reciver=%2 "
                  "order by time";
    sql=sql.arg(act).arg(act);
    std::vector<Information> infos;
    QSqlDatabase db=pool->getdb();
    QSqlQuery query(db);
    if(query.exec(sql)){
        while(query.next()){
            Information info;
            info.id=query.value(0).toUInt();
            info.sender=query.value(1).toString();
            info.reciver=query.value(2).toString();
            info.time=query.value(3).toDateTime();
            info.type=query.value(4).toString().at(0).toLatin1();
            info.msg=query.value(5).toString();
            infos.push_back(info);
        }
    }else
        qDebug()<< "Error getInfos:" << query.lastError().text();
    pool->append(db);
    return infos;
}

bool Mapper::myfriends(QJsonArray &ja)
{
    if(ja.size()){
        QStringList frs;
        for(int i=0; i<ja.size(); ++i){
            QString act=ja.at(i).toObject().value("account").toString();
            QString nm=ja.at(i).toObject().value("name").toString();
            frs.append("(\'"+act+"\',\'"+nm+"\')");
        }
        QString sql="insert into friends(account,name) values "+frs.join(",");
        qDebug()<<sql;
        QSqlDatabase db=pool->getdb();
        if(!db.transaction()){
            qDebug()<<"Error: transaction "<<db.lastError().text();
            pool->append(db);
            return false;
        }
        QSqlQuery query(db);
        if(!query.exec("delete from friends")){
            db.rollback();
            qDebug()<<"Error: delete friends "<<query.lastError().text();
            pool->append(db);
            return false;
        }
        if(!query.exec(sql)){
            db.rollback();
            qDebug()<<"Error: myfriend "<<query.lastError().text();
            pool->append(db);
            return false;
        }
        if(!db.commit()){
            qDebug()<<"Error: commit "<<db.lastError().text();
            pool->append(db);
            return false;
        }
    }
    return true;
}

QJsonArray Mapper::lastmsg()
{
    QSqlDatabase db=pool->getdb();
    QSqlQuery query(db);
    QJsonArray ja;
    //查询好友
    QString sql="select account,name from friends";
    if(query.exec(sql)){
        while(query.next()){
            QJsonObject jo;
            jo.insert("account",query.value(0).toLongLong());
            jo.insert("name",query.value(1).toString());
            ja.append(jo);
        }
    }else
        qDebug()<<"Error: lastmsg friend "<<query.lastError().text();
    //查询最后一次聊天记录
    QString psql="select id, time, type, msg "
        "from informations "
        "where sender=%1 or reciver=%2 "
        " order by time desc";
    QJsonArray jas;
    for(int i=0; i<ja.size(); ++i){
        QString act=QString::number(ja.at(i).toObject().value("account").toInteger());
        sql=psql.arg(act).arg(act);
        if(query.exec(sql)&&query.next()){
            QJsonObject jo;
            jo.insert("account",ja.at(i).toObject().value("account"));
            jo.insert("name",ja.at(i).toObject().value("name").toString());
            jo.insert("id",query.value(0).toString());
            jo.insert("time", query.value(1).toString());
            jo.insert("type", query.value(2).toString());
            jo.insert("msg", query.value(3).toString());
            jas.append(jo);
        }else
            qDebug()<<"Error: lastmsg "<<query.lastError().text();
    }
    pool->append(db);
    return jas;
}

bool Mapper::reciverimg(Information &info)
{
    QString sql="insert into informations(sender, reciver, time, type, msg) values";
    QString str="(\'"+info.sender+"\',\'"+info.reciver+"\',\'"+info.time.toString("yyyy-MM-dd HH:mm:ss")+"\',\'"+info.type+"\',\'"+info.msg+"\')";
    sql=sql+str;
    qDebug()<<"reciverimg sql:";
    qDebug()<<sql;
    QSqlDatabase db=pool->getdb();
    QSqlQuery query(db);
    if(!query.exec(sql)){
        qDebug()<<"Error: reciverimg "<<query.lastError().text();
        return false;
    }
    pool->append(db);
    return true;
}

DataBasePool::DataBasePool(const QString &account, int size)
{
    this->size=size;
    for(int i=0; i<size; ++i){
        QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE", "db"+QString::number(i));
        db.setDatabaseName(DBNAME);
        if (!db.open()) {
            qDebug() << "Error: Unable to open database" << db.lastError().text();
            return ;
        }
        dbs.append(db);
    }
}

DataBasePool::~DataBasePool()
{
    // while(true){
    //     QMutexLocker<QMutex> locker(&mutex);
    //     if(dbs.size()==size){
    //         for(QSqlDatabase& db : dbs){
    //             db.close();
    //             QSqlDatabase::removeDatabase(db.databaseName());
    //         }
    //         qDebug()<<"database close!";
    //         return;
    //     }else
    //         cdtion.wait(&mutex);
    // }
    for(QSqlDatabase& db : dbs){
        db.close();
        QSqlDatabase::removeDatabase(db.databaseName());
    }
}

void DataBasePool::append(QSqlDatabase &db)
{
    {
        QMutexLocker<QMutex> locker(&mutex);
        dbs.append(db);
    }
    cdtion.notify_one();
}

QSqlDatabase DataBasePool::getdb()
{
    while(true){
        QMutexLocker<QMutex> locker(&mutex);
        if(!dbs.isEmpty()){
            return dbs.takeLast();
        }else{
            cdtion.wait(&mutex);
        }
    }
}

